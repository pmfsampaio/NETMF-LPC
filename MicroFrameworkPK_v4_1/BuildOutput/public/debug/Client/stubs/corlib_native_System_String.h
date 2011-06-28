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


#ifndef _CORLIB_NATIVE_SYSTEM_STRING_H_
#define _CORLIB_NATIVE_SYSTEM_STRING_H_

namespace System
{
    struct String
    {
        // Helper Functions to access fields of managed object
        // Declaration of stubs. These functions are implemented by Interop code developers
        static CHAR get_Chars( CLR_RT_HeapBlock* pMngObj, INT32 param0, HRESULT &hr );
        static CHAR ToCharArray( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
        static CHAR ToCharArray( CLR_RT_HeapBlock* pMngObj, INT32 param0, INT32 param1, HRESULT &hr );
        static INT32 get_Length( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
        static LPCSTR Split( CLR_RT_HeapBlock* pMngObj, CLR_RT_TypedArray_CHAR param0, HRESULT &hr );
        static LPCSTR Split( CLR_RT_HeapBlock* pMngObj, CLR_RT_TypedArray_CHAR param0, INT32 param1, HRESULT &hr );
        static LPCSTR Substring( CLR_RT_HeapBlock* pMngObj, INT32 param0, HRESULT &hr );
        static LPCSTR Substring( CLR_RT_HeapBlock* pMngObj, INT32 param0, INT32 param1, HRESULT &hr );
        static LPCSTR Trim( CLR_RT_HeapBlock* pMngObj, CLR_RT_TypedArray_CHAR param0, HRESULT &hr );
        static LPCSTR TrimStart( CLR_RT_HeapBlock* pMngObj, CLR_RT_TypedArray_CHAR param0, HRESULT &hr );
        static LPCSTR TrimEnd( CLR_RT_HeapBlock* pMngObj, CLR_RT_TypedArray_CHAR param0, HRESULT &hr );
        static void _ctor( CLR_RT_HeapBlock* pMngObj, CLR_RT_TypedArray_CHAR param0, INT32 param1, INT32 param2, HRESULT &hr );
        static void _ctor( CLR_RT_HeapBlock* pMngObj, CLR_RT_TypedArray_CHAR param0, HRESULT &hr );
        static void _ctor( CLR_RT_HeapBlock* pMngObj, CHAR param0, INT32 param1, HRESULT &hr );
        static INT32 CompareTo( CLR_RT_HeapBlock* pMngObj, UNSUPPORTED_TYPE param0, HRESULT &hr );
        static INT32 CompareTo( CLR_RT_HeapBlock* pMngObj, LPCSTR param0, HRESULT &hr );
        static INT32 IndexOf( CLR_RT_HeapBlock* pMngObj, CHAR param0, HRESULT &hr );
        static INT32 IndexOf( CLR_RT_HeapBlock* pMngObj, CHAR param0, INT32 param1, HRESULT &hr );
        static INT32 IndexOf( CLR_RT_HeapBlock* pMngObj, CHAR param0, INT32 param1, INT32 param2, HRESULT &hr );
        static INT32 IndexOfAny( CLR_RT_HeapBlock* pMngObj, CLR_RT_TypedArray_CHAR param0, HRESULT &hr );
        static INT32 IndexOfAny( CLR_RT_HeapBlock* pMngObj, CLR_RT_TypedArray_CHAR param0, INT32 param1, HRESULT &hr );
        static INT32 IndexOfAny( CLR_RT_HeapBlock* pMngObj, CLR_RT_TypedArray_CHAR param0, INT32 param1, INT32 param2, HRESULT &hr );
        static INT32 IndexOf( CLR_RT_HeapBlock* pMngObj, LPCSTR param0, HRESULT &hr );
        static INT32 IndexOf( CLR_RT_HeapBlock* pMngObj, LPCSTR param0, INT32 param1, HRESULT &hr );
        static INT32 IndexOf( CLR_RT_HeapBlock* pMngObj, LPCSTR param0, INT32 param1, INT32 param2, HRESULT &hr );
        static INT32 LastIndexOf( CLR_RT_HeapBlock* pMngObj, CHAR param0, HRESULT &hr );
        static INT32 LastIndexOf( CLR_RT_HeapBlock* pMngObj, CHAR param0, INT32 param1, HRESULT &hr );
        static INT32 LastIndexOf( CLR_RT_HeapBlock* pMngObj, CHAR param0, INT32 param1, INT32 param2, HRESULT &hr );
        static INT32 LastIndexOfAny( CLR_RT_HeapBlock* pMngObj, CLR_RT_TypedArray_CHAR param0, HRESULT &hr );
        static INT32 LastIndexOfAny( CLR_RT_HeapBlock* pMngObj, CLR_RT_TypedArray_CHAR param0, INT32 param1, HRESULT &hr );
        static INT32 LastIndexOfAny( CLR_RT_HeapBlock* pMngObj, CLR_RT_TypedArray_CHAR param0, INT32 param1, INT32 param2, HRESULT &hr );
        static INT32 LastIndexOf( CLR_RT_HeapBlock* pMngObj, LPCSTR param0, HRESULT &hr );
        static INT32 LastIndexOf( CLR_RT_HeapBlock* pMngObj, LPCSTR param0, INT32 param1, HRESULT &hr );
        static INT32 LastIndexOf( CLR_RT_HeapBlock* pMngObj, LPCSTR param0, INT32 param1, INT32 param2, HRESULT &hr );
        static LPCSTR ToLower( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
        static LPCSTR ToUpper( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
        static LPCSTR Trim( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
        static INT8 Equals( LPCSTR param0, LPCSTR param1, HRESULT &hr );
        static INT8 op_Equality( LPCSTR param0, LPCSTR param1, HRESULT &hr );
        static INT8 op_Inequality( LPCSTR param0, LPCSTR param1, HRESULT &hr );
        static INT32 Compare( LPCSTR param0, LPCSTR param1, HRESULT &hr );
        static LPCSTR Concat( LPCSTR param0, LPCSTR param1, HRESULT &hr );
        static LPCSTR Concat( LPCSTR param0, LPCSTR param1, LPCSTR param2, HRESULT &hr );
        static LPCSTR Concat( LPCSTR param0, LPCSTR param1, LPCSTR param2, LPCSTR param3, HRESULT &hr );
        static LPCSTR Concat( CLR_RT_TypedArray_LPCSTR param0, HRESULT &hr );
    };
}
#endif  //_CORLIB_NATIVE_SYSTEM_STRING_H_
