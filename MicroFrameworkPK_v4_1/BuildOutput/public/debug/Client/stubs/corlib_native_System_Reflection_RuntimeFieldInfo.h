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


#ifndef _CORLIB_NATIVE_SYSTEM_REFLECTION_RUNTIMEFIELDINFO_H_
#define _CORLIB_NATIVE_SYSTEM_REFLECTION_RUNTIMEFIELDINFO_H_

namespace System
{
    namespace Reflection
    {
        struct RuntimeFieldInfo
        {
            // Helper Functions to access fields of managed object
            // Declaration of stubs. These functions are implemented by Interop code developers
            static LPCSTR get_Name( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
            static UNSUPPORTED_TYPE get_DeclaringType( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
            static UNSUPPORTED_TYPE get_FieldType( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
            static UNSUPPORTED_TYPE GetValue( CLR_RT_HeapBlock* pMngObj, UNSUPPORTED_TYPE param0, HRESULT &hr );
        };
    }
}
#endif  //_CORLIB_NATIVE_SYSTEM_REFLECTION_RUNTIMEFIELDINFO_H_
