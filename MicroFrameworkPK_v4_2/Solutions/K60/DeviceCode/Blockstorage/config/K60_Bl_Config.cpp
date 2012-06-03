////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
// Portions Copyright (c) David Dunscombe
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>

#include <Targets\Native\K60\DeviceCode\K60.h>




// ****** TO BE MODIFIED *****************************
// BlockDeviceInformation


#define FLASH_MANUFACTURER_CODE                 0xffff
#define FLASH_DEVICE_CODE                       0xffff
#define FLASH_BLOCK_COUNT                       256

#define K60_BS_BASE_ADDRESS                  FLASH_MEMORY_Base
#define K60_BS_SIZE_IN_BYTES                 0x80000

#define K60_BLOCK_ERASE_TYPICAL_TIME_USEC     96000
#define K60_SECTOR_WRITE_TYPICAL_TIME_USEC    48000
#define K60_BLOCK_ERASE_MAX_TIME_USEC         50000
#define K60_SECTOR_WRITE_MAX_TIME_USEC        48000

//dummy
#define K60_BS_CHIP_SELECT                   0
#define K60_BS_WAIT_STATES                   0
#define K60_BS_RELEASE_COUNTS                0
#define K60_BS_BIT_WIDTH                     16
#define K60_BS_WP_GPIO_PIN                   GPIO_PIN_NONE
#define K60_BS_WP_ACTIVE                     FALSE

#define K60_BS_IS_REMOVABLE                  FALSE
#define K60_BS_SUPPORTS_XIP                  TRUE
#define K60_BS_WRITE_PROTECTED               FALSE

#define K60_BS_NUM_REGIONS                   1

#define BYTES_PER_SECTOR                     4
    
#define REGION1_XIP_ADDRESS                  K60_BS_BASE_ADDRESS
#define REGION1_BYTES_PER_BLK                0x800
#define REGION1_NUM_OF_BLOCKS                FLASH_BLOCK_COUNT

//*******************************************************//



//--//


#if defined(MEMORY_BLOCKTYPE_GCC_SPECIAL_BOOTSTRAP)
#undef MEMORY_BLOCKTYPE_GCC_SPECIAL_BOOTSTRAP 
#endif

#if defined(MEMORY_BLOCKTYPE_GCC_SPECIAL_CODE)
#undef MEMORY_BLOCKTYPE_GCC_SPECIAL_CODE
#endif

#ifdef __GNUC__
#define MEMORY_BLOCKTYPE_GCC_SPECIAL_BOOTSTRAP  BlockRange::BLOCKTYPE_BOOTSTRAP
#define MEMORY_BLOCKTYPE_GCC_SPECIAL_CODE       BlockRange::BLOCKTYPE_CODE
#else
#define MEMORY_BLOCKTYPE_GCC_SPECIAL_BOOTSTRAP  BlockRange::BLOCKTYPE_CODE
#define MEMORY_BLOCKTYPE_GCC_SPECIAL_CODE       BlockRange::BLOCKTYPE_DEPLOYMENT
#endif

//--//

#if defined(__GNUC__)
const BlockRange g_K60_BS_BlockRange[] =
{
    //
    { BlockRange::BLOCKTYPE_BOOTSTRAP       ,   0,  30 },
    { BlockRange::BLOCKTYPE_CODE            ,  31, 176 },
    { BlockRange::BLOCKTYPE_DEPLOYMENT      , 177, 248 },
    //{ BlockRange::BLOCKTYPE_STORAGE_A       , 241, 244 },
    //{ BlockRange::BLOCKTYPE_STORAGE_B       , 245, 248 },
    { BlockRange::BLOCKTYPE_CONFIG          , 249, 255 }
};
#else
const BlockRange g_K60_BS_BlockRange[] =
{
    //
    { BlockRange::BLOCKTYPE_BOOTSTRAP       ,   0,  30 },
    { BlockRange::BLOCKTYPE_CODE            ,  31, 176 },
    { BlockRange::BLOCKTYPE_DEPLOYMENT      , 177, 248 },
    //{ BlockRange::BLOCKTYPE_STORAGE_A       , 241, 244 },
    //{ BlockRange::BLOCKTYPE_STORAGE_B       , 245, 248 },
    { BlockRange::BLOCKTYPE_CONFIG          , 249, 255 }
};
#endif

//--//

#undef MEMORY_BLOCKTYPE_GCC_SPECIAL_BOOTSTRAP 
#undef MEMORY_BLOCKTYPE_GCC_SPECIAL_CODE    

//--//

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section rwdata = "g_K60_BS_Config"
#endif




const BlockRegionInfo  g_K60_BS_BlkRegion[K60_BS_NUM_REGIONS] = 
{  
    REGION1_XIP_ADDRESS,                // ByteAddress     Address;            // Start address
    REGION1_NUM_OF_BLOCKS,              // UINT32          NumBlocks;          // total number of blocks in this region
    REGION1_BYTES_PER_BLK,              // UINT32          BytesPerBlock;      // Total number of bytes per block (MUST be SectorsPerBlock * DataBytesPerSector)

    ARRAYSIZE_CONST_EXPR(g_K60_BS_BlockRange),
    g_K60_BS_BlockRange,
};

//--//

BlockDeviceInfo g_K60_BS_DeviceInfo=
{
    {
        K60_BS_IS_REMOVABLE,                      // BOOL Removable;
        K60_BS_SUPPORTS_XIP,                      // BOOL SupportsXIP;
        K60_BS_WRITE_PROTECTED,                   // BOOL WriteProtected
		
    },
    
    K60_SECTOR_WRITE_MAX_TIME_USEC,               // UINT32 Duration_Max_WordWrite_uSec;
    K60_BLOCK_ERASE_MAX_TIME_USEC,                // UINT32 Duration_Max_SectorErase_uSec;
    BYTES_PER_SECTOR,                             // BytesPerSector; // Bytes Per Sector

    FLASH_MEMORY_Size,                            // UINT32 Size;

    K60_BS_NUM_REGIONS,                           // UINT32 NumRegions;
    g_K60_BS_BlkRegion,                           // const BlockRegionInfo* pRegions;
};



struct MEMORY_MAPPED_NOR_BLOCK_CONFIG g_K60_BS_Config =
{
    { // BLOCK_CONFIG
        {
            K60_BS_WP_GPIO_PIN,                    // GPIO_PIN             Pin;
            K60_BS_WP_ACTIVE,                      // BOOL                 ActiveState;
        },

        &g_K60_BS_DeviceInfo,                      // BlockDeviceinfo
    },  
    
    { // CPU_MEMORY_CONFIG
        K60_BS_CHIP_SELECT,                        // UINT8                CPU_MEMORY_CONFIG::ChipSelect;
        TRUE,                                      // UINT8                CPU_MEMORY_CONFIG::ReadOnly;
        K60_BS_WAIT_STATES,                        // UINT32               CPU_MEMORY_CONFIG::WaitStates;
        K60_BS_RELEASE_COUNTS,                     // UINT32               CPU_MEMORY_CONFIG::ReleaseCounts;
        K60_BS_BIT_WIDTH,                          // UINT32               CPU_MEMORY_CONFIG::BitWidth;
        K60_BS_BASE_ADDRESS,                       // UINT32               CPU_MEMORY_CONFIG::BaseAddress;
        K60_BS_SIZE_IN_BYTES,                      // UINT32               CPU_MEMORY_CONFIG::SizeInBytes;
        0,                                         // UINT8                CPU_MEMORY_CONFIG::XREADYEnable 
        0,                                         // UINT8                CPU_MEMORY_CONFIG::ByteSignalsForRead 
        0,                                         // UINT8                CPU_MEMORY_CONFIG::ExternalBufferEnable
    },

    0,                                             // UINT32               ChipProtection;
    FLASH_MANUFACTURER_CODE,                       // FLASH_WORD           ManufacturerCode;
    FLASH_DEVICE_CODE,                             // FLASH_WORD           DeviceCode;
};


//--//

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section rodata = "g_K60_BS"
#endif

struct BlockStorageDevice g_K60_BS;

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section rodata 
#endif 

//--//

