////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
// Portions Copyright (c) David Dunscombe
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>
#include "..\K60.h"

#pragma arm section code = "SectionForFlashOperations"

//--//

BOOL __section(SectionForFlashOperations) K60_BS_Driver::ChipInitialize(void* context)
{
    return TRUE;
}

BOOL __section(SectionForFlashOperations) K60_BS_Driver::ChipUnInitialize(void* context)
{
    // UnInitialize EFC
    return TRUE;
}

BOOL __section(SectionForFlashOperations) K60_BS_Driver::ChipReadOnly(void * context, BOOL On, UINT32 ProtectionKey)
{
    return TRUE;
}

const BlockDeviceInfo* __section(SectionForFlashOperations) K60_BS_Driver::GetDeviceInfo(void* context)
{
    BLOCK_CONFIG* config = (BLOCK_CONFIG *) context;
    return config->BlockDeviceInformation;
}

BOOL __section(SectionForFlashOperations) K60_BS_Driver::Read(void* context, ByteAddress Address, UINT32 NumBytes,
        BYTE * pSectorBuff)
{
    Address = CPU_GetUncachableAddress(Address);

    UINT32* chipAddress = (UINT32 *) Address;
    UINT32* endAddress = (UINT32 *) (Address + NumBytes);
    UINT32 *pBuf = (UINT32 *) pSectorBuff;

    {
        GLOBAL_LOCK( irq);

        while (chipAddress < endAddress)
        {
            *pBuf++ = *chipAddress++;
        }
    }

    return TRUE;
}

BOOL __section(SectionForFlashOperations) K60_BS_Driver::Write(void* context, ByteAddress address, UINT32 numBytes,
        BYTE * pSectorBuff, BOOL ReadModifyWrite)
{
    BYTE * pData;
    BYTE * pBuf = NULL;
    MEMORY_MAPPED_NOR_BLOCK_CONFIG* config = (MEMORY_MAPPED_NOR_BLOCK_CONFIG*) context;
    const BlockDeviceInfo * deviceInfo = config->BlockConfig.BlockDeviceInformation;

    UINT32 region, range;

    if (ReadModifyWrite)
    {
        BOOL fRet = TRUE;

        if (!deviceInfo->FindRegionFromAddress(address, region, range))
            return FALSE;

        UINT32 bytesPerBlock = deviceInfo->Regions[region].BytesPerBlock;
        UINT32 regionEnd = deviceInfo->Regions[region].Start + deviceInfo->Regions[region].Size();
        UINT32 offset = address % bytesPerBlock;
        ByteAddress addr = address;
        ByteAddress addrEnd = address + numBytes;
        UINT32 index = 0;

        pBuf = (BYTE*) private_malloc(bytesPerBlock);

        if (pBuf == NULL)
        {

            return FALSE;
        }

        while (fRet && addr < addrEnd)
        {
            ByteAddress sectAddr = (addr - offset);

            if (offset == 0 && numBytes >= bytesPerBlock)
            {
                pData = &pSectorBuff[index];
            }
            else
            {
                int bytes = __min(bytesPerBlock - offset, numBytes);

                memcpy(&pBuf[0], (void*) sectAddr, bytesPerBlock);
                memcpy(&pBuf[offset], &pSectorBuff[index], bytes);

                pData = pBuf;
            }

            if (!EraseBlock(context, sectAddr))
            {
                fRet = FALSE;
                break;
            }

            fRet = WriteX(context, sectAddr, bytesPerBlock, pData, ReadModifyWrite, TRUE);

            numBytes -= bytesPerBlock - offset;
            addr += bytesPerBlock - offset;
            index += bytesPerBlock - offset;
            offset = 0;

            if (numBytes > 0 && addr >= regionEnd)
            {
                region++;

                if (region >= deviceInfo->NumRegions)
                {
                    fRet = FALSE;
                }
                else
                {
                    regionEnd = deviceInfo->Regions[region].Start + deviceInfo->Regions[region].Size();
                    bytesPerBlock = deviceInfo->Regions[region].BytesPerBlock;

                    private_free(pBuf);

                    pBuf = (BYTE*) private_malloc(bytesPerBlock);

                    if (pBuf == NULL)
                    {
                        fRet = FALSE;
                    }
                }
            }

        }

        if (pBuf != NULL)
        {
            private_free(pBuf);
        }

        return fRet;
    }
    else
    {
        return WriteX(context, address, numBytes, pSectorBuff, ReadModifyWrite, TRUE);
    }
}

BOOL __section(SectionForFlashOperations) K60_BS_Driver::WriteX(void* context, ByteAddress address, UINT32 numBytes,
        BYTE * pSectorBuff, BOOL ReadModifyWrite, BOOL fIncrementDataPtr)
{
    MEMORY_MAPPED_NOR_BLOCK_CONFIG* config = (MEMORY_MAPPED_NOR_BLOCK_CONFIG*) context;
    const BlockDeviceInfo * deviceInfo = config->BlockConfig.BlockDeviceInformation;

    // lot to put on the stack...
    UINT8 pageBuffer[c_FLASH_PAGE_SIZE];
    BYTE* localpData = pSectorBuff;

    UINT32 baseAddress;
    UINT32 endAddress;
    UINT32 pageNumber;
    UINT32 offset;
    UINT32 writeSize;
    UINT32 pageAddress;
    UINT32 iRegion, iRange;
    INT32 NumOfBytes = (INT32) numBytes;

    UINT32 *chipAddress;

    if (deviceInfo->Attribute.WriteProtected)
        return FALSE;

    if (!deviceInfo->FindRegionFromAddress(address, iRegion, iRange))
        return FALSE;

    address = CPU_GetUncachableAddress(address);
    baseAddress = CPU_GetUncachableAddress(deviceInfo->Regions[iRegion].Start);
    endAddress = (baseAddress + deviceInfo->Regions[iRegion].Size());
    chipAddress = (UINT32 *) address;

    if ((address < baseAddress) || (address >= endAddress))
        return FALSE;

    pageNumber = ((address - baseAddress) / c_FLASH_PAGE_SIZE);
    offset = ((address - baseAddress) % c_FLASH_PAGE_SIZE);
    pageAddress = pageNumber * c_FLASH_PAGE_SIZE + baseAddress;

    GLOBAL_LOCK( irq);

    while (NumOfBytes > 0)
    {
        writeSize = __min(c_FLASH_PAGE_SIZE - offset, NumOfBytes);

        UINT32 * tmpWrData = (UINT32*) localpData;
        for (UINT32 i = 0; i < writeSize; i += sizeof(UINT32))
        {
            UINT32 Data;
            Data = *tmpWrData;

            // bits we are going to swap not set ?
            if (0 != (Data & ~(*chipAddress)))
            {
                debug_printf("Erase failure: 0x%08x=0x%08x, writeTo(0x%08x)\r\n", (size_t) chipAddress, *chipAddress,
                        Data);
                ASSERT(0);

                return FALSE;
            }
            chipAddress++;
            tmpWrData++;
        }

        // get the whole page first
        memcpy(pageBuffer, (void *) pageAddress, c_FLASH_PAGE_SIZE);
        memcpy(pageBuffer + offset, localpData, writeSize);

        // --//
        {
            for (UINT32 i = 0; i < c_FLASH_PAGE_SIZE; i += sizeof(UINT32))
            {
                // make sure we are ok to write data
                while (!(FTFL->FSTAT & FTFL_FSTAT_CCIF_MASK))
                {
                }

                // write long word
                FTFL->FSTAT = (FTFL_FSTAT_ACCERR_MASK | FTFL_FSTAT_FPVIOL_MASK);
                FTFL->FCCOB0 = c_COMMAND_PROGRAM_LONGWORD;

                // address
                FTFL->FCCOB1 = (UINT8) (((UINT32) (pageAddress + i)) >> 16);
                FTFL->FCCOB2 = (UINT8) (((UINT32) (pageAddress + i)) >> 8);
                FTFL->FCCOB3 = (UINT8) ((UINT32) (pageAddress + i));

                // data
                FTFL->FCCOB4 = (UINT8) (pageBuffer[i + 3]);
                FTFL->FCCOB5 = (UINT8) (pageBuffer[i + 2]);
                FTFL->FCCOB6 = (UINT8) (pageBuffer[i + 1]);
                FTFL->FCCOB7 = (UINT8) (pageBuffer[i]);

                // do the write
                FTFL->FSTAT = FTFL_FSTAT_CCIF_MASK;

                // wait for finish
                while (!(FTFL->FSTAT & FTFL_FSTAT_CCIF_MASK))
                {
                }

                // invalidate cache
                FMC->PFB0CR |= FMC_PFB0CR_CINV_WAY_MASK;
            }

        }

        NumOfBytes -= writeSize;
        if (fIncrementDataPtr)
            localpData += writeSize;
        pageAddress += c_FLASH_PAGE_SIZE;
        pageNumber++;
        offset = 0;
    }

    return TRUE;
}

BOOL __section(SectionForFlashOperations) K60_BS_Driver::Memset(void* context, ByteAddress Address, UINT8 Data,
        UINT32 NumBytes)
{
    UINT32 chipData;

    memset(&chipData, Data, sizeof(UINT32));

    return WriteX(context, Address, NumBytes, (BYTE*) &chipData, TRUE, FALSE);
}

BOOL __section(SectionForFlashOperations) K60_BS_Driver::GetSectorMetadata(void* context, ByteAddress SectorStart,
        SectorMetadata* pSectorMetadata)
{
    return FALSE;
}

BOOL __section(SectionForFlashOperations) K60_BS_Driver::SetSectorMetadata(void* context, ByteAddress SectorStart,
        SectorMetadata* pSectorMetadata)
{
    return FALSE;
}

BOOL __section(SectionForFlashOperations) K60_BS_Driver::IsBlockErased(void* context, ByteAddress Address,
        UINT32 BlockLength)
{
    MEMORY_MAPPED_NOR_BLOCK_CONFIG* config = (MEMORY_MAPPED_NOR_BLOCK_CONFIG*) context;
    const BlockDeviceInfo * deviceInfo = config->BlockConfig.BlockDeviceInformation;

    UINT32 iRegion, iRange;
    UINT32 *chipAddress, *endAddress;

    // 1st or 2nd FLASH controller
    if (!deviceInfo->FindRegionFromAddress(Address, iRegion, iRange))
        return FALSE;

    Address = CPU_GetCachableAddress(Address);

    chipAddress = (UINT32 *) Address;
    endAddress = (UINT32 *) (Address + BlockLength);

    {
        GLOBAL_LOCK( irq);

        // copy data
        while (chipAddress < endAddress)
        {
            if (*chipAddress++ != 0xFFFFFFFF)
            {
                return FALSE;
            }
        }
    }

    return TRUE;
}

// erase one  page
BOOL __section(SectionForFlashOperations) K60_BS_Driver::EraseBlock(void* context, ByteAddress address)
{
    MEMORY_MAPPED_NOR_BLOCK_CONFIG* config = (MEMORY_MAPPED_NOR_BLOCK_CONFIG*) context;
    const BlockDeviceInfo * deviceInfo = config->BlockConfig.BlockDeviceInformation;

    UINT32 iRegion, iRange;
    UINT32 pageNumber = 0, baseAddress, pageAddress;

    // 1st or 2nd FLASH controller
    if (!deviceInfo->FindRegionFromAddress(address, iRegion, iRange))
        return FALSE;

    address = CPU_GetUncachableAddress(address);
    baseAddress = CPU_GetCachableAddress(deviceInfo->Regions[iRegion].Start);

    // the pageNumber is the start of page of "Sector", even Sector is not the start sectoraddres of the block
    pageNumber = ((address - baseAddress) / c_FLASH_PAGE_SIZE);
    pageAddress = pageNumber * c_FLASH_PAGE_SIZE + baseAddress;

    {
        GLOBAL_LOCK( irq);

        // make sure we are ok to write data
        while (!(FTFL->FSTAT & FTFL_FSTAT_CCIF_MASK))
        {
        }

        // setup for erase
        FTFL->FSTAT = (FTFL_FSTAT_ACCERR_MASK | FTFL_FSTAT_FPVIOL_MASK);
        FTFL->FCCOB0 = c_COMMAND_ERASE_SECTOR;

        // address
        FTFL->FCCOB1 = (UINT8) (((UINT32) pageAddress) >> 16);
        FTFL->FCCOB2 = (UINT8) (((UINT32) pageAddress) >> 8);
        FTFL->FCCOB3 = (UINT8) ((UINT32) pageAddress);
        FTFL->FCCOB4 = 0;
        FTFL->FCCOB5 = 0;
        FTFL->FCCOB6 = 0;
        FTFL->FCCOB7 = 0;

        // do the erase
        FTFL->FSTAT = FTFL_FSTAT_CCIF_MASK;

        // wait for success
        while (!(FTFL->FSTAT & FTFL_FSTAT_CCIF_MASK))
        {
        }

        // check result
        if (FTFL->FSTAT & FTFL_FSTAT_ACCERR_MASK)
        {
            debug_printf("Erase failure (ACCERR): 0x%08x\r\n", pageAddress);
            ASSERT(0);

            return FALSE;
        }

        if (FTFL->FSTAT & FTFL_FSTAT_MGSTAT0_MASK)
        {
            debug_printf("Erase failure (MGSTAT0): 0x%08x\r\n", pageAddress);
            ASSERT(0);

            return FALSE;
        }

        if (FTFL->FSTAT & FTFL_FSTAT_FPVIOL_MASK)
        {
            debug_printf("Erase failure (FPVIOL): 0x%08x\r\n", pageAddress);
            ASSERT(0);

            return FALSE;
        }

        // invalidate cache
        FMC->PFB0CR |= FMC_PFB0CR_CINV_WAY_MASK;
    }

    return TRUE;
}

void __section(SectionForFlashOperations) K60_BS_Driver::SetPowerState(void* context, UINT32 State)
{
    return;
}

UINT32 __section(SectionForFlashOperations) K60_BS_Driver::MaxSectorWrite_uSec(void* context)
{
    NATIVE_PROFILE_PAL_FLASH();
    MEMORY_MAPPED_NOR_BLOCK_CONFIG* config = (MEMORY_MAPPED_NOR_BLOCK_CONFIG*) context;
    return config->BlockConfig.BlockDeviceInformation->MaxSectorWrite_uSec;
}

UINT32 __section(SectionForFlashOperations) K60_BS_Driver::MaxBlockErase_uSec(void* context)
{
    NATIVE_PROFILE_PAL_FLASH();
    MEMORY_MAPPED_NOR_BLOCK_CONFIG* config = (MEMORY_MAPPED_NOR_BLOCK_CONFIG*) context;
    return config->BlockConfig.BlockDeviceInformation->MaxBlockErase_uSec;
}

#pragma arm section code
struct IBlockStorageDevice g_K60_BS_DeviceTable =
{ &K60_BS_Driver::ChipInitialize, &K60_BS_Driver::ChipUnInitialize, &K60_BS_Driver::GetDeviceInfo,
        &K60_BS_Driver::Read, &K60_BS_Driver::Write, &K60_BS_Driver::Memset, &K60_BS_Driver::GetSectorMetadata,
        &K60_BS_Driver::SetSectorMetadata, &K60_BS_Driver::IsBlockErased, &K60_BS_Driver::EraseBlock,
        &K60_BS_Driver::SetPowerState, &K60_BS_Driver::MaxSectorWrite_uSec, &K60_BS_Driver::MaxBlockErase_uSec, };

