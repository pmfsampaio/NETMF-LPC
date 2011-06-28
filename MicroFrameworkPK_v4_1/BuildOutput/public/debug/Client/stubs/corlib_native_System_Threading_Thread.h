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


#ifndef _CORLIB_NATIVE_SYSTEM_THREADING_THREAD_H_
#define _CORLIB_NATIVE_SYSTEM_THREADING_THREAD_H_

namespace System
{
    namespace Threading
    {
        struct Thread
        {
            // Helper Functions to access fields of managed object
            static UNSUPPORTED_TYPE& Get_m_Delegate( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_corlib_native_System_Threading_Thread::FIELD__m_Delegate ); }

            static INT32& Get_m_Priority( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT32( pMngObj, Library_corlib_native_System_Threading_Thread::FIELD__m_Priority ); }

            static UNSUPPORTED_TYPE& Get_m_Thread( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_corlib_native_System_Threading_Thread::FIELD__m_Thread ); }

            static UNSUPPORTED_TYPE& Get_m_AppDomain( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_corlib_native_System_Threading_Thread::FIELD__m_AppDomain ); }

            // Declaration of stubs. These functions are implemented by Interop code developers
            static void _ctor( CLR_RT_HeapBlock* pMngObj, UNSUPPORTED_TYPE param0, HRESULT &hr );
            static void Start( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
            static void Abort( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
            static void Suspend( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
            static void Resume( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
            static INT32 get_Priority( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
            static void set_Priority( CLR_RT_HeapBlock* pMngObj, INT32 param0, HRESULT &hr );
            static INT8 get_IsAlive( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
            static void Join( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
            static INT8 Join( CLR_RT_HeapBlock* pMngObj, INT32 param0, HRESULT &hr );
            static INT8 Join( CLR_RT_HeapBlock* pMngObj, UNSUPPORTED_TYPE param0, HRESULT &hr );
            static INT32 get_ThreadState( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
            static void Sleep( INT32 param0, HRESULT &hr );
            static UNSUPPORTED_TYPE get_CurrentThread( HRESULT &hr );
            static UNSUPPORTED_TYPE GetDomain( HRESULT &hr );
        };
    }
}
#endif  //_CORLIB_NATIVE_SYSTEM_THREADING_THREAD_H_
