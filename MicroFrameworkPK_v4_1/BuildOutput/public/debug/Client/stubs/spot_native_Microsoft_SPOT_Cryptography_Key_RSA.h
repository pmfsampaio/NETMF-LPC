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


#ifndef _SPOT_NATIVE_MICROSOFT_SPOT_CRYPTOGRAPHY_KEY_RSA_H_
#define _SPOT_NATIVE_MICROSOFT_SPOT_CRYPTOGRAPHY_KEY_RSA_H_

namespace Microsoft
{
    namespace SPOT
    {
        namespace Cryptography
        {
            struct Key_RSA
            {
                // Helper Functions to access fields of managed object
                static UNSUPPORTED_TYPE& Get_m_modulus( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_spot_native_Microsoft_SPOT_Cryptography_Key_RSA::FIELD__m_modulus ); }

                static UNSUPPORTED_TYPE& Get_m_exponent( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_spot_native_Microsoft_SPOT_Cryptography_Key_RSA::FIELD__m_exponent ); }

                // Declaration of stubs. These functions are implemented by Interop code developers
                static UINT8 Encrypt( CLR_RT_HeapBlock* pMngObj, CLR_RT_TypedArray_UINT8 param0, INT32 param1, INT32 param2, CLR_RT_TypedArray_UINT8 param3, HRESULT &hr );
                static UINT8 Decrypt( CLR_RT_HeapBlock* pMngObj, CLR_RT_TypedArray_UINT8 param0, INT32 param1, INT32 param2, CLR_RT_TypedArray_UINT8 param3, HRESULT &hr );
                static INT8 VerifySignature( CLR_RT_HeapBlock* pMngObj, CLR_RT_TypedArray_UINT8 param0, INT32 param1, INT32 param2, CLR_RT_TypedArray_UINT8 param3, INT32 param4, INT32 param5, HRESULT &hr );
            };
        }
    }
}
#endif  //_SPOT_NATIVE_MICROSOFT_SPOT_CRYPTOGRAPHY_KEY_RSA_H_
