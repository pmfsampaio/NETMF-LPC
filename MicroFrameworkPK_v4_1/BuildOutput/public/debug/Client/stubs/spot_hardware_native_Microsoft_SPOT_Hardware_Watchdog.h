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


#ifndef _SPOT_HARDWARE_NATIVE_MICROSOFT_SPOT_HARDWARE_WATCHDOG_H_
#define _SPOT_HARDWARE_NATIVE_MICROSOFT_SPOT_HARDWARE_WATCHDOG_H_

namespace Microsoft
{
    namespace SPOT
    {
        namespace Hardware
        {
            struct Watchdog
            {
                // Helper Functions to access fields of managed object
                // Declaration of stubs. These functions are implemented by Interop code developers
                static INT8 get_Enabled( HRESULT &hr );
                static void set_Enabled( INT8 param0, HRESULT &hr );
                static UNSUPPORTED_TYPE get_Timeout( HRESULT &hr );
                static void set_Timeout( UNSUPPORTED_TYPE param0, HRESULT &hr );
                static INT32 get_Behavior( HRESULT &hr );
                static void set_Behavior( INT32 param0, HRESULT &hr );
                static UNSUPPORTED_TYPE get_Log( HRESULT &hr );
                static void set_Log( UNSUPPORTED_TYPE param0, HRESULT &hr );
                static INT8 GetLastOcurrenceDetails( UNSUPPORTED_TYPE * param0, UNSUPPORTED_TYPE param1, UNSUPPORTED_TYPE * param2, HRESULT &hr );
            };
        }
    }
}
#endif  //_SPOT_HARDWARE_NATIVE_MICROSOFT_SPOT_HARDWARE_WATCHDOG_H_
