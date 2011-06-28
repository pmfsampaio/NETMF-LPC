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


#ifndef _CORLIB_NATIVE_SYSTEM_EXCEPTION_H_
#define _CORLIB_NATIVE_SYSTEM_EXCEPTION_H_

namespace System
{
    struct Exception
    {
        // Helper Functions to access fields of managed object
        static LPCSTR& Get__message( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_LPCSTR( pMngObj, Library_corlib_native_System_Exception::FIELD___message ); }

        static UNSUPPORTED_TYPE& Get_m_innerException( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_corlib_native_System_Exception::FIELD__m_innerException ); }

        static UNSUPPORTED_TYPE& Get_m_stackTrace( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_corlib_native_System_Exception::FIELD__m_stackTrace ); }

        static INT32& Get_m_HResult( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT32( pMngObj, Library_corlib_native_System_Exception::FIELD__m_HResult ); }

        // Declaration of stubs. These functions are implemented by Interop code developers
        static LPCSTR get_StackTrace( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
    };
}
#endif  //_CORLIB_NATIVE_SYSTEM_EXCEPTION_H_
