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


#ifndef _SPOT_TIME_NATIVE_MICROSOFT_SPOT_TIME_TIMESERVICE_H_
#define _SPOT_TIME_NATIVE_MICROSOFT_SPOT_TIME_TIMESERVICE_H_

namespace Microsoft
{
    namespace SPOT
    {
        namespace Time
        {
            struct TimeService
            {
                // Helper Functions to access fields of managed object
                // Declaration of stubs. These functions are implemented by Interop code developers
                static UNSUPPORTED_TYPE get_Settings( HRESULT &hr );
                static void set_Settings( UNSUPPORTED_TYPE param0, HRESULT &hr );
                static void Start( HRESULT &hr );
                static void Stop( HRESULT &hr );
                static UNSUPPORTED_TYPE get_LastSyncStatus( HRESULT &hr );
                static UNSUPPORTED_TYPE Update( UNSUPPORTED_TYPE param0, UINT32 param1, HRESULT &hr );
                static void SetUtcTime( INT64 param0, HRESULT &hr );
                static void SetTimeZoneOffset( INT32 param0, HRESULT &hr );
            };
        }
    }
}
#endif  //_SPOT_TIME_NATIVE_MICROSOFT_SPOT_TIME_TIMESERVICE_H_
