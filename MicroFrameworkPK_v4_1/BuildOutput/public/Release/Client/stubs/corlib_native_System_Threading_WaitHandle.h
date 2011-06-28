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


#ifndef _CORLIB_NATIVE_SYSTEM_THREADING_WAITHANDLE_H_
#define _CORLIB_NATIVE_SYSTEM_THREADING_WAITHANDLE_H_

namespace System
{
    namespace Threading
    {
        struct WaitHandle
        {
            // Helper Functions to access fields of managed object
            // Declaration of stubs. These functions are implemented by Interop code developers
            static INT8 WaitOne( CLR_RT_HeapBlock* pMngObj, INT32 param0, INT8 param1, HRESULT &hr );
            static INT32 WaitMultiple( CLR_RT_TypedArray_UNSUPPORTED_TYPE param0, UNSUPPORTED_TYPE param1, UNSUPPORTED_TYPE param2, INT32 param3, HRESULT &hr );
        };
    }
}
#endif  //_CORLIB_NATIVE_SYSTEM_THREADING_WAITHANDLE_H_
