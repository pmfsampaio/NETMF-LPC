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


#ifndef _SPOT_TOUCH_NATIVE_MICROSOFT_SPOT_TOUCH_TOUCHCOLLECTORCONFIGURATION_H_
#define _SPOT_TOUCH_NATIVE_MICROSOFT_SPOT_TOUCH_TOUCHCOLLECTORCONFIGURATION_H_

namespace Microsoft
{
    namespace SPOT
    {
        namespace Touch
        {
            struct TouchCollectorConfiguration
            {
                // Helper Functions to access fields of managed object
                // Declaration of stubs. These functions are implemented by Interop code developers
                static void EnableTouchCollection( INT32 param0, INT32 param1, INT32 param2, INT32 param3, INT32 param4, UNSUPPORTED_TYPE param5, HRESULT &hr );
                static void GetTouchPoints( INT32 * param0, CLR_RT_TypedArray_INT16 param1, CLR_RT_TypedArray_INT16 param2, HRESULT &hr );
                static void GetTouchInput( INT32 param0, INT32 * param1, INT32 * param2, INT32 * param3, HRESULT &hr );
                static void SetTouchInput( INT32 param0, INT32 param1, INT32 param2, INT32 param3, HRESULT &hr );
            };
        }
    }
}
#endif  //_SPOT_TOUCH_NATIVE_MICROSOFT_SPOT_TOUCH_TOUCHCOLLECTORCONFIGURATION_H_
