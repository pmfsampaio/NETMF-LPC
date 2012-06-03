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


#ifndef _LPC24XX_ADC_NXP_INTEROP_ADC_H_
#define _LPC24XX_ADC_NXP_INTEROP_ADC_H_

namespace NXP
{
    namespace Interop
    {
        struct ADC
        {
            // Helper Functions to access fields of managed object
            // Declaration of stubs. These functions are implemented by Interop code developers
            static void Initialize( CLR_RT_HeapBlock* pMngObj, INT16 param0, HRESULT &hr );
            static void Uninitialize( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
            static void On( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
            static void Off( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
            static INT32 GetSample( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
        };
    }
}
#endif  //_LPC24XX_ADC_NXP_INTEROP_ADC_H_
