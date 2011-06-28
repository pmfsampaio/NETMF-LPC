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


#ifndef _CORLIB_NATIVE_SYSTEM_THREADING_INTERLOCKED_H_
#define _CORLIB_NATIVE_SYSTEM_THREADING_INTERLOCKED_H_

namespace System
{
    namespace Threading
    {
        struct Interlocked
        {
            // Helper Functions to access fields of managed object
            // Declaration of stubs. These functions are implemented by Interop code developers
            static INT32 Increment( INT32 * param0, HRESULT &hr );
            static INT32 Decrement( INT32 * param0, HRESULT &hr );
            static INT32 Exchange( INT32 * param0, INT32 param1, HRESULT &hr );
            static INT32 CompareExchange( INT32 * param0, INT32 param1, INT32 param2, HRESULT &hr );
        };
    }
}
#endif  //_CORLIB_NATIVE_SYSTEM_THREADING_INTERLOCKED_H_
