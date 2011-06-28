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


#ifndef _CORLIB_NATIVE_SYSTEM_REFLECTION_ASSEMBLY_H_
#define _CORLIB_NATIVE_SYSTEM_REFLECTION_ASSEMBLY_H_

namespace System
{
    namespace Reflection
    {
        struct Assembly
        {
            // Helper Functions to access fields of managed object
            // Declaration of stubs. These functions are implemented by Interop code developers
            static LPCSTR get_FullName( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
            static UNSUPPORTED_TYPE GetType( CLR_RT_HeapBlock* pMngObj, UNSUPPORTED_TYPE param0, HRESULT &hr );
            static UNSUPPORTED_TYPE GetTypes( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
            static void GetVersion( CLR_RT_HeapBlock* pMngObj, INT32 * param0, INT32 * param1, INT32 * param2, INT32 * param3, HRESULT &hr );
            static LPCSTR GetManifestResourceNames( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
            static UNSUPPORTED_TYPE GetExecutingAssembly( HRESULT &hr );
            static UNSUPPORTED_TYPE LoadInternal( UNSUPPORTED_TYPE param0, UNSUPPORTED_TYPE param1, LPCSTR param2, INT8 param3, INT32 param4, INT32 param5, HRESULT &hr );
            static UNSUPPORTED_TYPE Load( UNSUPPORTED_TYPE param0, HRESULT &hr );
        };
    }
}
#endif  //_CORLIB_NATIVE_SYSTEM_REFLECTION_ASSEMBLY_H_
