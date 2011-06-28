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


#ifndef _CORLIB_NATIVE_SYSTEM_REFLECTION_PROPERTYINFO_H_
#define _CORLIB_NATIVE_SYSTEM_REFLECTION_PROPERTYINFO_H_

namespace System
{
    namespace Reflection
    {
        struct PropertyInfo
        {
            // Helper Functions to access fields of managed object
            // Declaration of stubs. These functions are implemented by Interop code developers
            static UNSUPPORTED_TYPE GetValue( CLR_RT_HeapBlock* pMngObj, UNSUPPORTED_TYPE param0, CLR_RT_TypedArray_UNSUPPORTED_TYPE param1, HRESULT &hr );
            static void SetValue( CLR_RT_HeapBlock* pMngObj, UNSUPPORTED_TYPE param0, UNSUPPORTED_TYPE param1, CLR_RT_TypedArray_UNSUPPORTED_TYPE param2, HRESULT &hr );
        };
    }
}
#endif  //_CORLIB_NATIVE_SYSTEM_REFLECTION_PROPERTYINFO_H_
