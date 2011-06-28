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


#ifndef _SPOT_HARDWARE_NATIVE_MICROSOFT_SPOT_HARDWARE_CPU_H_
#define _SPOT_HARDWARE_NATIVE_MICROSOFT_SPOT_HARDWARE_CPU_H_

namespace Microsoft
{
    namespace SPOT
    {
        namespace Hardware
        {
            struct Cpu
            {
                // Helper Functions to access fields of managed object
                // Declaration of stubs. These functions are implemented by Interop code developers
                static UINT32 get_SystemClock( HRESULT &hr );
                static UINT32 get_SlowClock( HRESULT &hr );
                static UNSUPPORTED_TYPE get_GlitchFilterTime( HRESULT &hr );
                static void set_GlitchFilterTime( UNSUPPORTED_TYPE param0, HRESULT &hr );
            };
        }
    }
}
#endif  //_SPOT_HARDWARE_NATIVE_MICROSOFT_SPOT_HARDWARE_CPU_H_
