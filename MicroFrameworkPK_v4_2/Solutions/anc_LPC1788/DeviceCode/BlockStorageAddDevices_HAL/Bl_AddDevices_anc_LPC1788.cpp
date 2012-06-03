////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>

extern struct BlockStorageDevice  g_SST39VF640_16_BS;
extern struct IBlockStorageDevice g_SST39WF_16_BS_DeviceTable;
extern struct BLOCK_CONFIG        g_SST39VF640_16_BS_Config;

//--//

void BlockStorage_AddDevices() //tinyhal.cpp calls this
{
   BlockStorageList::AddDevice( &g_SST39VF640_16_BS, &g_SST39WF_16_BS_DeviceTable, &g_SST39VF640_16_BS_Config, FALSE );
}