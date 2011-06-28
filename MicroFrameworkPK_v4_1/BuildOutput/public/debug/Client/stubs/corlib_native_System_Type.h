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


#ifndef _CORLIB_NATIVE_SYSTEM_TYPE_H_
#define _CORLIB_NATIVE_SYSTEM_TYPE_H_

namespace System
{
    struct Type
    {
        // Helper Functions to access fields of managed object
        // Declaration of stubs. These functions are implemented by Interop code developers
        static UNSUPPORTED_TYPE get_DeclaringType( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
        static UNSUPPORTED_TYPE GetMethod( CLR_RT_HeapBlock* pMngObj, UNSUPPORTED_TYPE param0, UNSUPPORTED_TYPE param1, HRESULT &hr );
        static INT8 IsInstanceOfType( CLR_RT_HeapBlock* pMngObj, UNSUPPORTED_TYPE param0, HRESULT &hr );
        static UNSUPPORTED_TYPE InvokeMember( CLR_RT_HeapBlock* pMngObj, LPCSTR param0, INT32 param1, UNSUPPORTED_TYPE param2, UNSUPPORTED_TYPE param3, UNSUPPORTED_TYPE param4, HRESULT &hr );
        static UNSUPPORTED_TYPE GetConstructor( CLR_RT_HeapBlock* pMngObj, UNSUPPORTED_TYPE param0, HRESULT &hr );
        static UNSUPPORTED_TYPE GetMethod( CLR_RT_HeapBlock* pMngObj, UNSUPPORTED_TYPE param0, UNSUPPORTED_TYPE param1, HRESULT &hr );
        static UNSUPPORTED_TYPE GetMethod( CLR_RT_HeapBlock* pMngObj, UNSUPPORTED_TYPE param0, HRESULT &hr );
        static INT8 get_IsNotPublic( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
        static INT8 get_IsPublic( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
        static INT8 get_IsClass( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
        static INT8 get_IsInterface( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
        static INT8 get_IsValueType( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
        static INT8 get_IsAbstract( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
        static INT8 get_IsEnum( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
        static INT8 get_IsSerializable( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
        static INT8 get_IsArray( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
        static UNSUPPORTED_TYPE GetTypeInternal( UNSUPPORTED_TYPE param0, UNSUPPORTED_TYPE param1, LPCSTR param2, LPCSTR param3, HRESULT &hr );
        static UNSUPPORTED_TYPE GetTypeFromHandle( UNSUPPORTED_TYPE param0, HRESULT &hr );
    };
}
#endif  //_CORLIB_NATIVE_SYSTEM_TYPE_H_
