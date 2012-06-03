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


#ifndef _SPOT_HARDWARE_NATIVE_MICROSOFT_SPOT_HARDWARE_POWERSTATE_H_
#define _SPOT_HARDWARE_NATIVE_MICROSOFT_SPOT_HARDWARE_POWERSTATE_H_

namespace Microsoft
{
    namespace SPOT
    {
        namespace Hardware
        {
            struct PowerState
            {
                // Helper Functions to access fields of managed object
                // Declaration of stubs. These functions are implemented by Interop code developers
                static void Reboot( INT8 param0, HRESULT &hr );
                static INT8 WaitForIdleCPU( INT32 param0, INT32 param1, HRESULT &hr );
                static UNSUPPORTED_TYPE get_MaximumTimeToActive( HRESULT &hr );
                static void set_MaximumTimeToActive( UNSUPPORTED_TYPE param0, HRESULT &hr );
                static INT32 get_WakeupEvents( HRESULT &hr );
                static void set_WakeupEvents( INT32 param0, HRESULT &hr );
                static UNSUPPORTED_TYPE get_Uptime( HRESULT &hr );
                static void InternalSleep( UINT8 param0, INT32 param1, HRESULT &hr );
                static void InternalChangePowerLevel( UINT8 param0, HRESULT &hr );
            };
        }
    }
}
#endif  //_SPOT_HARDWARE_NATIVE_MICROSOFT_SPOT_HARDWARE_POWERSTATE_H_
