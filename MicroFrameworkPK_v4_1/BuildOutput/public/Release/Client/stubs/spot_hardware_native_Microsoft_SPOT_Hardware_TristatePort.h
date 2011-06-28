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


#ifndef _SPOT_HARDWARE_NATIVE_MICROSOFT_SPOT_HARDWARE_TRISTATEPORT_H_
#define _SPOT_HARDWARE_NATIVE_MICROSOFT_SPOT_HARDWARE_TRISTATEPORT_H_

namespace Microsoft
{
    namespace SPOT
    {
        namespace Hardware
        {
            struct TristatePort
            {
                // Helper Functions to access fields of managed object
                // Declaration of stubs. These functions are implemented by Interop code developers
                static INT8 get_Active( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
                static void set_Active( CLR_RT_HeapBlock* pMngObj, INT8 param0, HRESULT &hr );
                static INT32 get_Resistor( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
                static void set_Resistor( CLR_RT_HeapBlock* pMngObj, INT32 param0, HRESULT &hr );
                static INT8 get_GlitchFilter( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
            };
        }
    }
}
#endif  //_SPOT_HARDWARE_NATIVE_MICROSOFT_SPOT_HARDWARE_TRISTATEPORT_H_
