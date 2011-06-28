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


#ifndef _SPOT_HARDWARE_NATIVE_MICROSOFT_SPOT_HARDWARE_LARGEBUFFER_H_
#define _SPOT_HARDWARE_NATIVE_MICROSOFT_SPOT_HARDWARE_LARGEBUFFER_H_

namespace Microsoft
{
    namespace SPOT
    {
        namespace Hardware
        {
            struct LargeBuffer
            {
                // Helper Functions to access fields of managed object
                static UNSUPPORTED_TYPE& Get_m_bytes( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_spot_hardware_native_Microsoft_SPOT_Hardware_LargeBuffer::FIELD__m_bytes ); }

                static INT8& Get_m_fDisposed( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT8( pMngObj, Library_spot_hardware_native_Microsoft_SPOT_Hardware_LargeBuffer::FIELD__m_fDisposed ); }

                // Declaration of stubs. These functions are implemented by Interop code developers
                static void InternalCreateBuffer( CLR_RT_HeapBlock* pMngObj, INT32 param0, HRESULT &hr );
                static void InternalDestroyBuffer( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
            };
        }
    }
}
#endif  //_SPOT_HARDWARE_NATIVE_MICROSOFT_SPOT_HARDWARE_LARGEBUFFER_H_
