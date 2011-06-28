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


#ifndef _SPOT_NATIVE_MICROSOFT_SPOT_EXTENDEDTIMER_H_
#define _SPOT_NATIVE_MICROSOFT_SPOT_EXTENDEDTIMER_H_

namespace Microsoft
{
    namespace SPOT
    {
        struct ExtendedTimer
        {
            // Helper Functions to access fields of managed object
            static UNSUPPORTED_TYPE& Get_m_timer( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_spot_native_Microsoft_SPOT_ExtendedTimer::FIELD__m_timer ); }

            static UNSUPPORTED_TYPE& Get_m_state( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_spot_native_Microsoft_SPOT_ExtendedTimer::FIELD__m_state ); }

            static UNSUPPORTED_TYPE& Get_m_callback( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_spot_native_Microsoft_SPOT_ExtendedTimer::FIELD__m_callback ); }

            // Declaration of stubs. These functions are implemented by Interop code developers
            static void Dispose( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
            static void _ctor( CLR_RT_HeapBlock* pMngObj, UNSUPPORTED_TYPE param0, UNSUPPORTED_TYPE param1, UNSUPPORTED_TYPE param2, INT32 param3, HRESULT &hr );
            static void _ctor( CLR_RT_HeapBlock* pMngObj, UNSUPPORTED_TYPE param0, UNSUPPORTED_TYPE param1, UNSUPPORTED_TYPE param2, INT32 param3, HRESULT &hr );
            static void _ctor( CLR_RT_HeapBlock* pMngObj, UNSUPPORTED_TYPE param0, UNSUPPORTED_TYPE param1, UNSUPPORTED_TYPE param2, UNSUPPORTED_TYPE param3, HRESULT &hr );
            static void _ctor( CLR_RT_HeapBlock* pMngObj, UNSUPPORTED_TYPE param0, UNSUPPORTED_TYPE param1, UNSUPPORTED_TYPE param2, HRESULT &hr );
            static void Change( CLR_RT_HeapBlock* pMngObj, INT32 param0, INT32 param1, HRESULT &hr );
            static void Change( CLR_RT_HeapBlock* pMngObj, INT32 param0, INT32 param1, HRESULT &hr );
            static void Change( CLR_RT_HeapBlock* pMngObj, UNSUPPORTED_TYPE param0, INT32 param1, HRESULT &hr );
            static INT32 get_LastExpiration( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
        };
    }
}
#endif  //_SPOT_NATIVE_MICROSOFT_SPOT_EXTENDEDTIMER_H_
