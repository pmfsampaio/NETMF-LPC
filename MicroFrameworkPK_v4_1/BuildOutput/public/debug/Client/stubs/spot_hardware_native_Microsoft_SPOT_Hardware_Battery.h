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


#ifndef _SPOT_HARDWARE_NATIVE_MICROSOFT_SPOT_HARDWARE_BATTERY_H_
#define _SPOT_HARDWARE_NATIVE_MICROSOFT_SPOT_HARDWARE_BATTERY_H_

namespace Microsoft
{
    namespace SPOT
    {
        namespace Hardware
        {
            struct Battery
            {
                // Helper Functions to access fields of managed object
                // Declaration of stubs. These functions are implemented by Interop code developers
                static INT32 ReadVoltage( HRESULT &hr );
                static INT32 ReadTemperature( HRESULT &hr );
                static INT8 OnCharger( HRESULT &hr );
                static INT8 IsFullyCharged( HRESULT &hr );
                static INT32 StateOfCharge( HRESULT &hr );
                static INT8 WaitForEvent( INT32 param0, HRESULT &hr );
            };
        }
    }
}
#endif  //_SPOT_HARDWARE_NATIVE_MICROSOFT_SPOT_HARDWARE_BATTERY_H_
