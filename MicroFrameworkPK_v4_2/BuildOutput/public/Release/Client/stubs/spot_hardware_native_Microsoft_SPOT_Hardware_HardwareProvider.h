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


#ifndef _SPOT_HARDWARE_NATIVE_MICROSOFT_SPOT_HARDWARE_HARDWAREPROVIDER_H_
#define _SPOT_HARDWARE_NATIVE_MICROSOFT_SPOT_HARDWARE_HARDWAREPROVIDER_H_

namespace Microsoft
{
    namespace SPOT
    {
        namespace Hardware
        {
            struct HardwareProvider
            {
                // Helper Functions to access fields of managed object
                // Declaration of stubs. These functions are implemented by Interop code developers
                static void NativeGetSerialPins( CLR_RT_HeapBlock* pMngObj, INT32 param0, UNSUPPORTED_TYPE * param1, UNSUPPORTED_TYPE param2, UNSUPPORTED_TYPE param3, UNSUPPORTED_TYPE * param4, HRESULT &hr );
                static INT32 NativeGetSerialPortsCount( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
                static INT8 NativeSupportsNonStandardBaudRate( CLR_RT_HeapBlock* pMngObj, INT32 param0, HRESULT &hr );
                static void NativeGetBaudRateBoundary( CLR_RT_HeapBlock* pMngObj, INT32 param0, UINT32 * param1, UINT32 * param2, HRESULT &hr );
                static INT8 NativeIsSupportedBaudRate( CLR_RT_HeapBlock* pMngObj, INT32 param0, UINT32 * param1, HRESULT &hr );
                static void NativeGetSpiPins( CLR_RT_HeapBlock* pMngObj, INT32 param0, UNSUPPORTED_TYPE * param1, UNSUPPORTED_TYPE param2, UNSUPPORTED_TYPE param3, HRESULT &hr );
                static INT32 NativeGetSpiPortsCount( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
                static void NativeGetI2CPins( CLR_RT_HeapBlock* pMngObj, UNSUPPORTED_TYPE * param0, UNSUPPORTED_TYPE param1, HRESULT &hr );
                static INT32 NativeGetPinsCount( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
                static void NativeGetPinsMap( CLR_RT_HeapBlock* pMngObj, CLR_RT_TypedArray_UNSUPPORTED_TYPE param0, HRESULT &hr );
                static UINT8 NativeGetPinUsage( CLR_RT_HeapBlock* pMngObj, INT32 param0, HRESULT &hr );
                static UINT8 NativeGetSupportedResistorModes( CLR_RT_HeapBlock* pMngObj, INT32 param0, HRESULT &hr );
                static UINT8 NativeGetSupportedInterruptModes( CLR_RT_HeapBlock* pMngObj, INT32 param0, HRESULT &hr );
                static INT32 NativeGetButtonPins( CLR_RT_HeapBlock* pMngObj, INT32 param0, HRESULT &hr );
                static void NativeGetLCDMetrics( CLR_RT_HeapBlock* pMngObj, INT32 * param0, INT32 * param1, INT32 * param2, INT32 * param3, HRESULT &hr );
                static INT32 NativeGetPWMChannelsCount( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
                static INT32 NativeGetPWMPinForChannel( CLR_RT_HeapBlock* pMngObj, INT32 param0, HRESULT &hr );
                static INT32 NativeGetAnalogChannelsCount( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
                static INT32 NativeGetAnalogPinForChannel( CLR_RT_HeapBlock* pMngObj, INT32 param0, HRESULT &hr );
                static INT32 NativeGetAvailablePrecisionInBitsForChannel( CLR_RT_HeapBlock* pMngObj, INT32 param0, HRESULT &hr );
            };
        }
    }
}
#endif  //_SPOT_HARDWARE_NATIVE_MICROSOFT_SPOT_HARDWARE_HARDWAREPROVIDER_H_
