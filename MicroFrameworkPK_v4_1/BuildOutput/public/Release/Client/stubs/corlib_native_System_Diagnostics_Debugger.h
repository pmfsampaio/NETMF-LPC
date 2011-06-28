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


#ifndef _CORLIB_NATIVE_SYSTEM_DIAGNOSTICS_DEBUGGER_H_
#define _CORLIB_NATIVE_SYSTEM_DIAGNOSTICS_DEBUGGER_H_

namespace System
{
    namespace Diagnostics
    {
        struct Debugger
        {
            // Helper Functions to access fields of managed object
            // Declaration of stubs. These functions are implemented by Interop code developers
            static INT8 get_IsAttached( HRESULT &hr );
            static void Break( HRESULT &hr );
        };
    }
}
#endif  //_CORLIB_NATIVE_SYSTEM_DIAGNOSTICS_DEBUGGER_H_
