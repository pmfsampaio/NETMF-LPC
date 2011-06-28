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


#ifndef _CORLIB_NATIVE_SYSTEM_THREADING_TIMER_H_
#define _CORLIB_NATIVE_SYSTEM_THREADING_TIMER_H_

namespace System
{
    namespace Threading
    {
        struct Timer
        {
            // Helper Functions to access fields of managed object
            static UNSUPPORTED_TYPE& Get_m_timer( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_corlib_native_System_Threading_Timer::FIELD__m_timer ); }

            static UNSUPPORTED_TYPE& Get_m_state( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_corlib_native_System_Threading_Timer::FIELD__m_state ); }

            static UNSUPPORTED_TYPE& Get_m_callback( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_corlib_native_System_Threading_Timer::FIELD__m_callback ); }

            // Declaration of stubs. These functions are implemented by Interop code developers
            static void Dispose( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
            static void _ctor( CLR_RT_HeapBlock* pMngObj, UNSUPPORTED_TYPE param0, UNSUPPORTED_TYPE param1, CHAR param2, UNSUPPORTED_TYPE param3, HRESULT &hr );
            static void _ctor( CLR_RT_HeapBlock* pMngObj, UNSUPPORTED_TYPE param0, UNSUPPORTED_TYPE param1, CHAR param2, UNSUPPORTED_TYPE param3, HRESULT &hr );
            static INT8 Change( CLR_RT_HeapBlock* pMngObj, INT32 param0, INT32 param1, HRESULT &hr );
            static INT8 Change( CLR_RT_HeapBlock* pMngObj, UNSUPPORTED_TYPE param0, UNSUPPORTED_TYPE param1, HRESULT &hr );
        };
    }
}
#endif  //_CORLIB_NATIVE_SYSTEM_THREADING_TIMER_H_
