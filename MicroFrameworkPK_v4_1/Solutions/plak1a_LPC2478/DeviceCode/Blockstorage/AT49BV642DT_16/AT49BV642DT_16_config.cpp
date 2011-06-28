//-----------------------------------------------------------------------------
// Software that is described herein is for illustrative purposes only  
// which provides customers with programming information regarding the  
// products. This software is supplied "AS IS" without any warranties.  
// NXP Semiconductors assumes no responsibility or liability for the 
// use of the software, conveys no license or title under any patent, 
// copyright, or mask work right to the product. NXP Semiconductors 
// reserves the right to make changes in the software without 
// notification. NXP Semiconductors also make no representation or 
// warranty that such application will be suitable for the specified 
// use without further testing or modification. 
//-----------------------------------------------------------------------------

#include <tinyhal.h>
#include <Drivers\BlockStorage\Flash\AT49BV_16\AT49BV_16.h>

//--//

#define FLASH_MANUFACTURER_CODE              0x001F001F
#define FLASH_DEVICE_CODE                    0x01D201D2

#define FLASH_BLOCK_COUNT                    127
#define FLASH_BYTES_PER_SECTOR               2
#define FLASH_BYTES_PER_BLOCK                (64*1024)

#define FLASH_BLOCK_ERASE_TYPICAL_TIME_USEC  500000
#define FLASH_SECTOR_WRITE_TYPICAL_TIME_USEC 10
#define FLASH_BLOCK_ERASE_MAX_TIME_USEC      6000000
#define FLASH_SECTOR_WRITE_MAX_TIME_USEC     120

//--//

#define AT49BV642DT_16__CHIP_SELECT      0
#define AT49BV642DT_16__WAIT_STATES      0
#define AT49BV642DT_16__RELEASE_COUNTS   0
#define AT49BV642DT_16__BIT_WIDTH        16
#define AT49BV642DT_16__BASE_ADDRESS     FLASH_MEMORY_Base
#define AT49BV642DT_16__SIZE_IN_BYTES    FLASH_MEMORY_Size
#define AT49BV642DT_16__WP_GPIO_PIN      GPIO_PIN_NONE
#define AT49BV642DT_16__WP_ACTIVE        FALSE


#if defined(MEMORY_BLOCKTYPE_GCC_SPECIAL_BOOTSTRAP)
#undef MEMORY_BLOCKTYPE_GCC_SPECIAL_BOOTSTRAP
#endif

#if defined(MEMORY_BLOCKTYPE_GCC_SPECIAL_CODE)
#undef MEMORY_BLOCKTYPE_GCC_SPECIAL_CODE
#endif

#ifdef __GNUC__
#define MEMORY_BLOCKTYPE_GCC_SPECIAL_BOOTSTRAP BlockRange::BLOCKTYPE_BOOTSTRAP
#define MEMORY_BLOCKTYPE_GCC_SPECIAL_CODE      BlockRange::BLOCKTYPE_CODE
#else
#define MEMORY_BLOCKTYPE_GCC_SPECIAL_BOOTSTRAP BlockRange::BLOCKTYPE_CODE
#define MEMORY_BLOCKTYPE_GCC_SPECIAL_CODE      BlockRange::BLOCKTYPE_DEPLOYMENT
#endif


// -- // device information

// BlockDeviceInformation

#define AT49BV642DT_16__IS_REMOVABLE        FALSE
#define AT49BV642DT_16__SUPPORTS_XIP        TRUE
#define AT49BV642DT_16__WRITE_PROTECTED     FALSE

#define AT49BV642DT_16__NUM_REGIONS         1


// BlockDeviceInformation

const BlockRange g_AT49BV642DT_16_BlockRange[] =
{
    { BlockRange::BLOCKTYPE_CODE       ,   0,   2 },   	// TinyBooter
    { BlockRange::BLOCKTYPE_CODE       ,   3,  13 },   	// TinyCLR

    { BlockRange::BLOCKTYPE_CODE       ,  14,  20 },   	// TinyCLR runtime
    { BlockRange::BLOCKTYPE_CODE       ,  21,  30 },   	// TinyCLR runtime

    { BlockRange::BLOCKTYPE_DEPLOYMENT ,  31,  61 },   	// TinyCLR runtime
    { BlockRange::BLOCKTYPE_DEPLOYMENT ,  62,  81 },   	// TinyCLR runtime
    { BlockRange::BLOCKTYPE_DEPLOYMENT ,  82, 100 },   	// TinyCLR runtime

    { BlockRange::BLOCKTYPE_FILESYSTEM , 101, 120 },   	// File System

    { BlockRange::BLOCKTYPE_STORAGE_A  , 121, 122 },
    { BlockRange::BLOCKTYPE_STORAGE_B  , 123, 124 },
    { BlockRange::BLOCKTYPE_CONFIG     , 125, 125 },		// g_ConfigurationSector
    { BlockRange::BLOCKTYPE_DEPLOYMENT , 126 ,126 },    //

};

//--//

const BlockRegionInfo  g_AT49BV642DT_16_BlkRegion[AT49BV642DT_16__NUM_REGIONS] =
{
	AT49BV642DT_16__BASE_ADDRESS,   // ByteAddress   Start;              // Starting Sector address
    FLASH_BLOCK_COUNT,                 		 // UINT32          NumBlocks;          // total number of blocks in this region
    FLASH_BYTES_PER_BLOCK,              // UINT32        BytesPerBlock;      // Total number of bytes per block (MUST be SectorsPerBlock * DataBytesPerSector)

    ARRAYSIZE_CONST_EXPR(g_AT49BV642DT_16_BlockRange),
    g_AT49BV642DT_16_BlockRange,
};

//--//


BlockDeviceInfo g_AT49BV642DT_16_DeviceInfo=
{
    {
        AT49BV642DT_16__IS_REMOVABLE,           // BOOL Removable;
        AT49BV642DT_16__SUPPORTS_XIP,           // BOOL SupportsXIP;
        AT49BV642DT_16__WRITE_PROTECTED         // BOOL WRiteProtected
    },
    FLASH_SECTOR_WRITE_MAX_TIME_USEC,           // UINT32 Duration_Max_WordWrite_uSec;
    FLASH_BLOCK_ERASE_MAX_TIME_USEC,            // UINT32 Duration_Max_SectorErase_uSec;
    FLASH_BYTES_PER_SECTOR,                           // UINT32 BytesPerSector; // Bytes Per Sector

    FLASH_MEMORY_Size,                          // UINT32 Size;

    AT49BV642DT_16__NUM_REGIONS,                // UINT32 NumRegions;
    g_AT49BV642DT_16_BlkRegion,                 // const BlockRegionInfo* pRegions;
};


struct MEMORY_MAPPED_NOR_BLOCK_CONFIG g_AT49BV642DT_16_BS_Config =
{
    { // BLOCK_CONFIG
        {
            AT49BV642DT_16__WP_GPIO_PIN,    // GPIO_PIN             Pin;
            AT49BV642DT_16__WP_ACTIVE,      // BOOL                 ActiveState;
        },

        &g_AT49BV642DT_16_DeviceInfo,       // BlockDeviceinfo
    },

    { // CPU_MEMORY_CONFIG
        AT49BV642DT_16__CHIP_SELECT,        // UINT8                CPU_MEMORY_CONFIG::ChipSelect;
        TRUE,                               // UINT8                CPU_MEMORY_CONFIG::ReadOnly;
        AT49BV642DT_16__WAIT_STATES,        // UINT32               CPU_MEMORY_CONFIG::WaitStates;
        AT49BV642DT_16__RELEASE_COUNTS,     // UINT32               CPU_MEMORY_CONFIG::ReleaseCounts;
        AT49BV642DT_16__BIT_WIDTH,          // UINT32               CPU_MEMORY_CONFIG::BitWidth;
        AT49BV642DT_16__BASE_ADDRESS,       // UINT32               CPU_MEMORY_CONFIG::BaseAddress;
        AT49BV642DT_16__SIZE_IN_BYTES,      // UINT32               CPU_MEMORY_CONFIG::SizeInBytes;
        0,                                  // UINT8                CPU_MEMORY_CONFIG::XREADYEnable 
        0,                                  // UINT8                CPU_MEMORY_CONFIG::ByteSignalsForRead 
        0,                                  // UINT8                CPU_MEMORY_CONFIG::ExternalBufferEnable
    },

    0,                                      // UINT32               ChipProtection;
    FLASH_MANUFACTURER_CODE,                // FLASH_WORD           ManufacturerCode;
    FLASH_DEVICE_CODE,                      // FLASH_WORD           DeviceCode;
};

//--//

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section rodata = "g_AT49BV642DT_16_BS"
#endif

struct BlockStorageDevice g_AT49BV642DT_16_BS;

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section rodata 
#endif 

//--//

