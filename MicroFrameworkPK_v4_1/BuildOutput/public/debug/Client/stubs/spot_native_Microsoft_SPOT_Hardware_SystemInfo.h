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


#ifndef _SPOT_NATIVE_MICROSOFT_SPOT_HARDWARE_SYSTEMINFO_H_
#define _SPOT_NATIVE_MICROSOFT_SPOT_HARDWARE_SYSTEMINFO_H_

namespace Microsoft
{
    namespace SPOT
    {
        namespace Hardware
        {
            struct SystemInfo
            {
                // Helper Functions to access fields of managed object
                // Declaration of stubs. These functions are implemented by Interop code developers
                static void GetSystemVersion( INT32 * param0, INT32 * param1, INT32 * param2, INT32 * param3, HRESULT &hr );
                static LPCSTR get_OEMString( HRESULT &hr );
                static INT8 get_IsBigEndian( HRESULT &hr );
            };
        }
    }
}
#endif  //_SPOT_NATIVE_MICROSOFT_SPOT_HARDWARE_SYSTEMINFO_H_
