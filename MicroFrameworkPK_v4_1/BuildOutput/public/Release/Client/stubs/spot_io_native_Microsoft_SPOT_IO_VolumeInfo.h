//-----------------------------------------------------------------------------
//
//                   ** WARNING! ** 
//    This file was generated automatically by a tool.
//    Re-running the tool will overwrite this file.
//    You should copy this file to a custom location
//    before adding any customization in the copy to
//    prevent loss of your changes when the tool is
//    re-run.
//
//-----------------------------------------------------------------------------


#ifndef _SPOT_IO_NATIVE_MICROSOFT_SPOT_IO_VOLUMEINFO_H_
#define _SPOT_IO_NATIVE_MICROSOFT_SPOT_IO_VOLUMEINFO_H_

namespace Microsoft
{
    namespace SPOT
    {
        namespace IO
        {
            struct VolumeInfo
            {
                // Helper Functions to access fields of managed object
                static LPCSTR& Get_Name( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_LPCSTR( pMngObj, Library_spot_io_native_Microsoft_SPOT_IO_VolumeInfo::FIELD__Name ); }

                static LPCSTR& Get_VolumeLabel( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_LPCSTR( pMngObj, Library_spot_io_native_Microsoft_SPOT_IO_VolumeInfo::FIELD__VolumeLabel ); }

                static UINT32& Get_VolumeID( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UINT32( pMngObj, Library_spot_io_native_Microsoft_SPOT_IO_VolumeInfo::FIELD__VolumeID ); }

                static LPCSTR& Get_FileSystem( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_LPCSTR( pMngObj, Library_spot_io_native_Microsoft_SPOT_IO_VolumeInfo::FIELD__FileSystem ); }

                static UINT32& Get_FileSystemFlags( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UINT32( pMngObj, Library_spot_io_native_Microsoft_SPOT_IO_VolumeInfo::FIELD__FileSystemFlags ); }

                static UINT32& Get_DeviceFlags( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UINT32( pMngObj, Library_spot_io_native_Microsoft_SPOT_IO_VolumeInfo::FIELD__DeviceFlags ); }

                static UINT32& Get_SerialNumber( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UINT32( pMngObj, Library_spot_io_native_Microsoft_SPOT_IO_VolumeInfo::FIELD__SerialNumber ); }

                static INT64& Get_TotalFreeSpace( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT64( pMngObj, Library_spot_io_native_Microsoft_SPOT_IO_VolumeInfo::FIELD__TotalFreeSpace ); }

                static INT64& Get_TotalSize( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT64( pMngObj, Library_spot_io_native_Microsoft_SPOT_IO_VolumeInfo::FIELD__TotalSize ); }

                static UINT32& Get_VolumePtr( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UINT32( pMngObj, Library_spot_io_native_Microsoft_SPOT_IO_VolumeInfo::FIELD__VolumePtr ); }

                // Declaration of stubs. These functions are implemented by Interop code developers
                static void _ctor( CLR_RT_HeapBlock* pMngObj, LPCSTR param0, HRESULT &hr );
                static void _ctor( CLR_RT_HeapBlock* pMngObj, UINT32 param0, HRESULT &hr );
                static void Refresh( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
                static void FlushAll( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
                static UNSUPPORTED_TYPE GetVolumes( HRESULT &hr );
                static LPCSTR GetFileSystems( HRESULT &hr );
            };
        }
    }
}
#endif  //_SPOT_IO_NATIVE_MICROSOFT_SPOT_IO_VOLUMEINFO_H_
