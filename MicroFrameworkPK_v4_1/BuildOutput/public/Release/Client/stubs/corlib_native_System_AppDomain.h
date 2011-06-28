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


#ifndef _CORLIB_NATIVE_SYSTEM_APPDOMAIN_H_
#define _CORLIB_NATIVE_SYSTEM_APPDOMAIN_H_

namespace System
{
    struct AppDomain
    {
        // Helper Functions to access fields of managed object
        static UNSUPPORTED_TYPE& Get_m_appDomain( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_corlib_native_System_AppDomain::FIELD__m_appDomain ); }

        static LPCSTR& Get_m_friendlyName( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_LPCSTR( pMngObj, Library_corlib_native_System_AppDomain::FIELD__m_friendlyName ); }

        // Declaration of stubs. These functions are implemented by Interop code developers
        static UNSUPPORTED_TYPE GetAssemblies( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
        static UNSUPPORTED_TYPE LoadInternal( CLR_RT_HeapBlock* pMngObj, UNSUPPORTED_TYPE param0, UNSUPPORTED_TYPE param1, LPCSTR param2, INT8 param3, INT32 param4, INT32 param5, HRESULT &hr );
        static UNSUPPORTED_TYPE CreateDomain( UNSUPPORTED_TYPE param0, HRESULT &hr );
        static void Unload( UNSUPPORTED_TYPE param0, HRESULT &hr );
    };
}
#endif  //_CORLIB_NATIVE_SYSTEM_APPDOMAIN_H_
