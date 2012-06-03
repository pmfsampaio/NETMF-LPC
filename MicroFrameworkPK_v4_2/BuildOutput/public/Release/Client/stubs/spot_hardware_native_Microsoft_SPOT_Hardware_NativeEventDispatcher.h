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


#ifndef _SPOT_HARDWARE_NATIVE_MICROSOFT_SPOT_HARDWARE_NATIVEEVENTDISPATCHER_H_
#define _SPOT_HARDWARE_NATIVE_MICROSOFT_SPOT_HARDWARE_NATIVEEVENTDISPATCHER_H_

namespace Microsoft
{
    namespace SPOT
    {
        namespace Hardware
        {
            struct NativeEventDispatcher
            {
                // Helper Functions to access fields of managed object
                static UNSUPPORTED_TYPE& Get_m_threadSpawn( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_spot_hardware_native_Microsoft_SPOT_Hardware_NativeEventDispatcher::FIELD__m_threadSpawn ); }

                static UNSUPPORTED_TYPE& Get_m_callbacks( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_spot_hardware_native_Microsoft_SPOT_Hardware_NativeEventDispatcher::FIELD__m_callbacks ); }

                static INT8& Get_m_disposed( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT8( pMngObj, Library_spot_hardware_native_Microsoft_SPOT_Hardware_NativeEventDispatcher::FIELD__m_disposed ); }

                static UNSUPPORTED_TYPE& Get_m_NativeEventDispatcher( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_spot_hardware_native_Microsoft_SPOT_Hardware_NativeEventDispatcher::FIELD__m_NativeEventDispatcher ); }

                // Declaration of stubs. These functions are implemented by Interop code developers
                static void EnableInterrupt( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
                static void DisableInterrupt( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
                static void Dispose( CLR_RT_HeapBlock* pMngObj, INT8 param0, HRESULT &hr );
                static void _ctor( CLR_RT_HeapBlock* pMngObj, LPCSTR param0, UINT64 param1, HRESULT &hr );
            };
        }
    }
}
#endif  //_SPOT_HARDWARE_NATIVE_MICROSOFT_SPOT_HARDWARE_NATIVEEVENTDISPATCHER_H_
