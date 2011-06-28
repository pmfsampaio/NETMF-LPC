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


#ifndef _CORLIB_NATIVE_SYSTEM_RANDOM_H_
#define _CORLIB_NATIVE_SYSTEM_RANDOM_H_

namespace System
{
    struct Random
    {
        // Helper Functions to access fields of managed object
        static UNSUPPORTED_TYPE& Get__random( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_corlib_native_System_Random::FIELD___random ); }

        // Declaration of stubs. These functions are implemented by Interop code developers
        static INT32 Next( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
        static INT32 Next( CLR_RT_HeapBlock* pMngObj, INT32 param0, HRESULT &hr );
        static double NextDouble( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
        static void NextBytes( CLR_RT_HeapBlock* pMngObj, CLR_RT_TypedArray_UINT8 param0, HRESULT &hr );
        static void _ctor( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
        static void _ctor( CLR_RT_HeapBlock* pMngObj, INT32 param0, HRESULT &hr );
    };
}
#endif  //_CORLIB_NATIVE_SYSTEM_RANDOM_H_
