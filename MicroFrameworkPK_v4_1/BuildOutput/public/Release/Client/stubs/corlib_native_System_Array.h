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


#ifndef _CORLIB_NATIVE_SYSTEM_ARRAY_H_
#define _CORLIB_NATIVE_SYSTEM_ARRAY_H_

namespace System
{
    struct Array
    {
        // Helper Functions to access fields of managed object
        // Declaration of stubs. These functions are implemented by Interop code developers
        static UNSUPPORTED_TYPE System_Collections_IList_get_Item( CLR_RT_HeapBlock* pMngObj, INT32 param0, HRESULT &hr );
        static void System_Collections_IList_set_Item( CLR_RT_HeapBlock* pMngObj, INT32 param0, UNSUPPORTED_TYPE param1, HRESULT &hr );
        static INT32 get_Length( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
        static UNSUPPORTED_TYPE CreateInstance( UNSUPPORTED_TYPE param0, UNSUPPORTED_TYPE param1, HRESULT &hr );
        static void Copy( UNSUPPORTED_TYPE param0, UNSUPPORTED_TYPE param1, INT32 param2, UNSUPPORTED_TYPE param3, UNSUPPORTED_TYPE param4, HRESULT &hr );
        static void Clear( UNSUPPORTED_TYPE param0, UNSUPPORTED_TYPE param1, INT32 param2, HRESULT &hr );
        static INT8 TrySZIndexOf( UNSUPPORTED_TYPE param0, UNSUPPORTED_TYPE param1, INT32 param2, INT32 param3, UNSUPPORTED_TYPE param4, HRESULT &hr );
    };
}
#endif  //_CORLIB_NATIVE_SYSTEM_ARRAY_H_
