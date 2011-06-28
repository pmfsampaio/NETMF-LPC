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


#ifndef _SPOT_IO_NATIVE_MICROSOFT_SPOT_IO_NATIVEFILESTREAM_H_
#define _SPOT_IO_NATIVE_MICROSOFT_SPOT_IO_NATIVEFILESTREAM_H_

namespace Microsoft
{
    namespace SPOT
    {
        namespace IO
        {
            struct NativeFileStream
            {
                // Helper Functions to access fields of managed object
                static UNSUPPORTED_TYPE& Get_m_fs( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_spot_io_native_Microsoft_SPOT_IO_NativeFileStream::FIELD__m_fs ); }

                // Declaration of stubs. These functions are implemented by Interop code developers
                static void _ctor( CLR_RT_HeapBlock* pMngObj, LPCSTR param0, INT32 param1, HRESULT &hr );
                static INT32 Read( CLR_RT_HeapBlock* pMngObj, CLR_RT_TypedArray_UINT8 param0, INT32 param1, INT32 param2, INT32 param3, HRESULT &hr );
                static INT32 Write( CLR_RT_HeapBlock* pMngObj, CLR_RT_TypedArray_UINT8 param0, INT32 param1, INT32 param2, INT32 param3, HRESULT &hr );
                static INT64 Seek( CLR_RT_HeapBlock* pMngObj, INT64 param0, UINT32 param1, HRESULT &hr );
                static void Flush( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
                static INT64 GetLength( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
                static void SetLength( CLR_RT_HeapBlock* pMngObj, INT64 param0, HRESULT &hr );
                static void GetStreamProperties( CLR_RT_HeapBlock* pMngObj, INT8 * param0, INT8 * param1, INT8 * param2, HRESULT &hr );
                static void Close( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
            };
        }
    }
}
#endif  //_SPOT_IO_NATIVE_MICROSOFT_SPOT_IO_NATIVEFILESTREAM_H_
