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


#ifndef _CORLIB_NATIVE_SYSTEM_OBJECT_H_
#define _CORLIB_NATIVE_SYSTEM_OBJECT_H_

namespace System
{
    struct Object
    {
        // Helper Functions to access fields of managed object
        // Declaration of stubs. These functions are implemented by Interop code developers
        static INT8 Equals( CLR_RT_HeapBlock* pMngObj, UNSUPPORTED_TYPE param0, HRESULT &hr );
        static INT32 GetHashCode( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
        static UNSUPPORTED_TYPE GetType( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
        static UNSUPPORTED_TYPE MemberwiseClone( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
        static INT8 ReferenceEquals( UNSUPPORTED_TYPE param0, UNSUPPORTED_TYPE param1, HRESULT &hr );
    };
}
#endif  //_CORLIB_NATIVE_SYSTEM_OBJECT_H_
