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


#ifndef _SPOT_NATIVE_MICROSOFT_SPOT_DEBUG_H_
#define _SPOT_NATIVE_MICROSOFT_SPOT_DEBUG_H_

namespace Microsoft
{
    namespace SPOT
    {
        struct Debug
        {
            // Helper Functions to access fields of managed object
            // Declaration of stubs. These functions are implemented by Interop code developers
            static void Print( LPCSTR param0, HRESULT &hr );
            static UINT32 GC( INT8 param0, HRESULT &hr );
            static void EnableGCMessages( INT8 param0, HRESULT &hr );
        };
    }
}
#endif  //_SPOT_NATIVE_MICROSOFT_SPOT_DEBUG_H_
