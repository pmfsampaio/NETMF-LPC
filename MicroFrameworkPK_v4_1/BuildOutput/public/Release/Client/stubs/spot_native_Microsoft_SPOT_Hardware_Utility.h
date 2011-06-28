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


#ifndef _SPOT_NATIVE_MICROSOFT_SPOT_HARDWARE_UTILITY_H_
#define _SPOT_NATIVE_MICROSOFT_SPOT_HARDWARE_UTILITY_H_

namespace Microsoft
{
    namespace SPOT
    {
        namespace Hardware
        {
            struct Utility
            {
                // Helper Functions to access fields of managed object
                // Declaration of stubs. These functions are implemented by Interop code developers
                static UINT32 ComputeCRC( CLR_RT_TypedArray_UINT8 param0, INT32 param1, INT32 param2, UINT32 param3, HRESULT &hr );
                static UINT32 ExtractValueFromArray( CLR_RT_TypedArray_UINT8 param0, INT32 param1, INT32 param2, HRESULT &hr );
                static void InsertValueIntoArray( CLR_RT_TypedArray_UINT8 param0, INT32 param1, INT32 param2, UINT32 param3, HRESULT &hr );
                static UINT8 ExtractRangeFromArray( CLR_RT_TypedArray_UINT8 param0, INT32 param1, INT32 param2, HRESULT &hr );
                static UINT8 CombineArrays( CLR_RT_TypedArray_UINT8 param0, CLR_RT_TypedArray_UINT8 param1, HRESULT &hr );
                static UINT8 CombineArrays( CLR_RT_TypedArray_UINT8 param0, INT32 param1, INT32 param2, CLR_RT_TypedArray_UINT8 param3, INT32 param4, INT32 param5, HRESULT &hr );
                static void SetLocalTime( UNSUPPORTED_TYPE param0, HRESULT &hr );
                static INT32 GetMachineTime( HRESULT &hr );
                static void Piezo( UINT32 param0, UINT32 param1, HRESULT &hr );
                static void Backlight( INT8 param0, HRESULT &hr );
            };
        }
    }
}
#endif  //_SPOT_NATIVE_MICROSOFT_SPOT_HARDWARE_UTILITY_H_
