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


#ifndef _SPOT_NATIVE_MICROSOFT_SPOT_EXTENDEDWEAKREFERENCE_H_
#define _SPOT_NATIVE_MICROSOFT_SPOT_EXTENDEDWEAKREFERENCE_H_

namespace Microsoft
{
    namespace SPOT
    {
        struct ExtendedWeakReference
        {
            // Helper Functions to access fields of managed object
            // Declaration of stubs. These functions are implemented by Interop code developers
            static void _ctor( CLR_RT_HeapBlock* pMngObj, UNSUPPORTED_TYPE param0, UNSUPPORTED_TYPE param1, UNSUPPORTED_TYPE param2, UINT32 param3, HRESULT &hr );
            static UNSUPPORTED_TYPE get_Selector( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
            static UINT32 get_Id( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
            static UINT32 get_Flags( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
            static INT32 get_Priority( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
            static void set_Priority( CLR_RT_HeapBlock* pMngObj, INT32 param0, HRESULT &hr );
            static void PushBackIntoRecoverList( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
            static UNSUPPORTED_TYPE Recover( UNSUPPORTED_TYPE param0, UNSUPPORTED_TYPE param1, HRESULT &hr );
        };
    }
}
#endif  //_SPOT_NATIVE_MICROSOFT_SPOT_EXTENDEDWEAKREFERENCE_H_
