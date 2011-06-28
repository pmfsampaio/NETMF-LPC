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


#ifndef _CORLIB_NATIVE_SYSTEM_DATETIME_H_
#define _CORLIB_NATIVE_SYSTEM_DATETIME_H_

namespace System
{
    struct DateTime
    {
        // Helper Functions to access fields of managed object
        static UINT64& Get_m_ticks( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UINT64( pMngObj, Library_corlib_native_System_DateTime::FIELD__m_ticks ); }

        // Declaration of stubs. These functions are implemented by Interop code developers
        static void _ctor( CLR_RT_HeapBlock* pMngObj, INT32 param0, INT32 param1, INT32 param2, INT32 param3, INT32 param4, INT32 param5, INT32 param6, HRESULT &hr );
        static INT32 get_Day( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
        static INT32 get_DayOfWeek( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
        static INT32 get_DayOfYear( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
        static INT32 get_Hour( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
        static INT32 get_Millisecond( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
        static INT32 get_Minute( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
        static INT32 get_Month( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
        static INT32 get_Second( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
        static INT32 get_Year( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
        static UNSUPPORTED_TYPE ToLocalTime( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
        static UNSUPPORTED_TYPE ToUniversalTime( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
        static INT32 DaysInMonth( INT32 param0, INT32 param1, HRESULT &hr );
        static UNSUPPORTED_TYPE get_Now( HRESULT &hr );
        static UNSUPPORTED_TYPE get_UtcNow( HRESULT &hr );
        static UNSUPPORTED_TYPE get_Today( HRESULT &hr );
    };
}
#endif  //_CORLIB_NATIVE_SYSTEM_DATETIME_H_
