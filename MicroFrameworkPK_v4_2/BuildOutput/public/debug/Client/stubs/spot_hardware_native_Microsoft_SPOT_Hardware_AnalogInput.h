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


#ifndef _SPOT_HARDWARE_NATIVE_MICROSOFT_SPOT_HARDWARE_ANALOGINPUT_H_
#define _SPOT_HARDWARE_NATIVE_MICROSOFT_SPOT_HARDWARE_ANALOGINPUT_H_

namespace Microsoft
{
    namespace SPOT
    {
        namespace Hardware
        {
            struct AnalogInput
            {
                // Helper Functions to access fields of managed object
                static INT32& Get_m_pin( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT32( pMngObj, Library_spot_hardware_native_Microsoft_SPOT_Hardware_AnalogInput::FIELD__m_pin ); }

                static INT32& Get_m_channel( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT32( pMngObj, Library_spot_hardware_native_Microsoft_SPOT_Hardware_AnalogInput::FIELD__m_channel ); }

                static double& Get_m_scale( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_double( pMngObj, Library_spot_hardware_native_Microsoft_SPOT_Hardware_AnalogInput::FIELD__m_scale ); }

                static double& Get_m_offset( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_double( pMngObj, Library_spot_hardware_native_Microsoft_SPOT_Hardware_AnalogInput::FIELD__m_offset ); }

                static INT32& Get_m_precision( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT32( pMngObj, Library_spot_hardware_native_Microsoft_SPOT_Hardware_AnalogInput::FIELD__m_precision ); }

                static INT8& Get_m_disposed( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT8( pMngObj, Library_spot_hardware_native_Microsoft_SPOT_Hardware_AnalogInput::FIELD__m_disposed ); }

                // Declaration of stubs. These functions are implemented by Interop code developers
                static INT32 ReadRaw( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
                static void Initialize( INT32 param0, INT32 param1, HRESULT &hr );
            };
        }
    }
}
#endif  //_SPOT_HARDWARE_NATIVE_MICROSOFT_SPOT_HARDWARE_ANALOGINPUT_H_
