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


#ifndef _CORLIB_NATIVE_SYSTEM_RUNTIMETYPE_H_
#define _CORLIB_NATIVE_SYSTEM_RUNTIMETYPE_H_

namespace System
{
    struct RuntimeType
    {
        // Helper Functions to access fields of managed object
        // Declaration of stubs. These functions are implemented by Interop code developers
        static UNSUPPORTED_TYPE get_Assembly( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
        static LPCSTR get_Name( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
        static LPCSTR get_FullName( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
        static UNSUPPORTED_TYPE get_BaseType( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
        static UNSUPPORTED_TYPE GetMethods( CLR_RT_HeapBlock* pMngObj, UNSUPPORTED_TYPE param0, HRESULT &hr );
        static UNSUPPORTED_TYPE GetField( CLR_RT_HeapBlock* pMngObj, UNSUPPORTED_TYPE param0, UNSUPPORTED_TYPE param1, HRESULT &hr );
        static UNSUPPORTED_TYPE GetFields( CLR_RT_HeapBlock* pMngObj, UNSUPPORTED_TYPE param0, HRESULT &hr );
        static UNSUPPORTED_TYPE GetInterfaces( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
        static UNSUPPORTED_TYPE GetElementType( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
    };
}
#endif  //_CORLIB_NATIVE_SYSTEM_RUNTIMETYPE_H_
