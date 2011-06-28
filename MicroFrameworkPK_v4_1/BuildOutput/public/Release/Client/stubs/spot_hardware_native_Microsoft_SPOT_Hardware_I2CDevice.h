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


#ifndef _SPOT_HARDWARE_NATIVE_MICROSOFT_SPOT_HARDWARE_I2CDEVICE_H_
#define _SPOT_HARDWARE_NATIVE_MICROSOFT_SPOT_HARDWARE_I2CDEVICE_H_

namespace Microsoft
{
    namespace SPOT
    {
        namespace Hardware
        {
            struct I2CDevice
            {
                // Helper Functions to access fields of managed object
                static UNSUPPORTED_TYPE& Get_m_xAction( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_spot_hardware_native_Microsoft_SPOT_Hardware_I2CDevice::FIELD__m_xAction ); }

                static UNSUPPORTED_TYPE& Get_Config( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_spot_hardware_native_Microsoft_SPOT_Hardware_I2CDevice::FIELD__Config ); }

                static INT8& Get_m_disposed( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT8( pMngObj, Library_spot_hardware_native_Microsoft_SPOT_Hardware_I2CDevice::FIELD__m_disposed ); }

                // Declaration of stubs. These functions are implemented by Interop code developers
                static INT32 Execute( CLR_RT_HeapBlock* pMngObj, CLR_RT_TypedArray_UNSUPPORTED_TYPE param0, UNSUPPORTED_TYPE param1, HRESULT &hr );
                static void Initialize( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
            };
        }
    }
}
#endif  //_SPOT_HARDWARE_NATIVE_MICROSOFT_SPOT_HARDWARE_I2CDEVICE_H_
