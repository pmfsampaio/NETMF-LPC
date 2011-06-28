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


#ifndef _CORLIB_NATIVE_SYSTEM_TIMESPAN_H_
#define _CORLIB_NATIVE_SYSTEM_TIMESPAN_H_

namespace System
{
    struct TimeSpan
    {
        // Helper Functions to access fields of managed object
        static INT64& Get_m_ticks( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT64( pMngObj, Library_corlib_native_System_TimeSpan::FIELD__m_ticks ); }

        // Declaration of stubs. These functions are implemented by Interop code developers
        static INT8 Equals( CLR_RT_HeapBlock* pMngObj, UNSUPPORTED_TYPE param0, HRESULT &hr );
        static LPCSTR ToString( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
        static void _ctor( CLR_RT_HeapBlock* pMngObj, INT32 param0, INT32 param1, INT32 param2, HRESULT &hr );
        static void _ctor( CLR_RT_HeapBlock* pMngObj, INT32 param0, INT32 param1, INT32 param2, INT32 param3, HRESULT &hr );
        static void _ctor( CLR_RT_HeapBlock* pMngObj, INT32 param0, INT32 param1, INT32 param2, INT32 param3, INT32 param4, HRESULT &hr );
        static INT32 CompareTo( CLR_RT_HeapBlock* pMngObj, UNSUPPORTED_TYPE param0, HRESULT &hr );
        static INT32 Compare( UNSUPPORTED_TYPE param0, UNSUPPORTED_TYPE param1, HRESULT &hr );
        static INT8 Equals( UNSUPPORTED_TYPE param0, UNSUPPORTED_TYPE param1, HRESULT &hr );
    };
}
#endif  //_CORLIB_NATIVE_SYSTEM_TIMESPAN_H_
