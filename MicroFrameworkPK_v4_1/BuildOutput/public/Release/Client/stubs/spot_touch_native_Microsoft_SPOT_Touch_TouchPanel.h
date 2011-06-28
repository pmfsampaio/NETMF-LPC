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


#ifndef _SPOT_TOUCH_NATIVE_MICROSOFT_SPOT_TOUCH_TOUCHPANEL_H_
#define _SPOT_TOUCH_NATIVE_MICROSOFT_SPOT_TOUCH_TOUCHPANEL_H_

namespace Microsoft
{
    namespace SPOT
    {
        namespace Touch
        {
            struct TouchPanel
            {
                // Helper Functions to access fields of managed object
                static INT8& Get__enabled( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT8( pMngObj, Library_spot_touch_native_Microsoft_SPOT_Touch_TouchPanel::FIELD___enabled ); }

                // Declaration of stubs. These functions are implemented by Interop code developers
                static void SetCalibration( CLR_RT_HeapBlock* pMngObj, INT32 param0, CLR_RT_TypedArray_INT16 param1, CLR_RT_TypedArray_INT16 param2, CLR_RT_TypedArray_INT16 param3, CLR_RT_TypedArray_INT16 param4, HRESULT &hr );
                static void GetCalibrationPointCount( CLR_RT_HeapBlock* pMngObj, INT32 * param0, HRESULT &hr );
                static void StartCalibration( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
                static void GetCalibrationPoint( CLR_RT_HeapBlock* pMngObj, INT32 param0, INT32 * param1, INT32 * param2, HRESULT &hr );
                static void EnableInternal( CLR_RT_HeapBlock* pMngObj, INT8 param0, HRESULT &hr );
            };
        }
    }
}
#endif  //_SPOT_TOUCH_NATIVE_MICROSOFT_SPOT_TOUCH_TOUCHPANEL_H_
