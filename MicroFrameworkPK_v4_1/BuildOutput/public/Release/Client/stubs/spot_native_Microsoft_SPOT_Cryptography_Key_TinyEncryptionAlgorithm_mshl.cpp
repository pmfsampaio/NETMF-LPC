//-----------------------------------------------------------------------------
//
//    ** DO NOT EDIT THIS FILE! **
//    This file was generated by a tool
//    re-running the tool will overwrite this file.
//
//-----------------------------------------------------------------------------


#include "spot_native.h"
#include "spot_native_Microsoft_SPOT_Cryptography_Key_TinyEncryptionAlgorithm.h"

using namespace Microsoft::SPOT::Cryptography;


HRESULT Library_spot_native_Microsoft_SPOT_Cryptography_Key_TinyEncryptionAlgorithm::Encrypt___SZARRAY_U1__SZARRAY_U1__I4__I4__SZARRAY_U1( CLR_RT_StackFrame& stack )
{
    TINYCLR_HEADER(); hr = S_OK;
    {
        CLR_RT_HeapBlock* pMngObj = Interop_Marshal_RetrieveManagedObject( stack );

        FAULT_ON_NULL(pMngObj);

        CLR_RT_TypedArray_UINT8 param0;
        TINYCLR_CHECK_HRESULT( Interop_Marshal_UINT8_ARRAY( stack, 1, param0 ) );

        INT32 param1;
        TINYCLR_CHECK_HRESULT( Interop_Marshal_INT32( stack, 2, param1 ) );

        INT32 param2;
        TINYCLR_CHECK_HRESULT( Interop_Marshal_INT32( stack, 3, param2 ) );

        CLR_RT_TypedArray_UINT8 param3;
        TINYCLR_CHECK_HRESULT( Interop_Marshal_UINT8_ARRAY( stack, 4, param3 ) );

        UINT8 retVal = Key_TinyEncryptionAlgorithm::Encrypt( pMngObj,  param0, param1, param2, param3, hr );
        TINYCLR_CHECK_HRESULT( hr );
        SetResult_UINT8( stack, retVal );

    }
    TINYCLR_NOCLEANUP();
}

HRESULT Library_spot_native_Microsoft_SPOT_Cryptography_Key_TinyEncryptionAlgorithm::Decrypt___SZARRAY_U1__SZARRAY_U1__I4__I4__SZARRAY_U1( CLR_RT_StackFrame& stack )
{
    TINYCLR_HEADER(); hr = S_OK;
    {
        CLR_RT_HeapBlock* pMngObj = Interop_Marshal_RetrieveManagedObject( stack );

        FAULT_ON_NULL(pMngObj);

        CLR_RT_TypedArray_UINT8 param0;
        TINYCLR_CHECK_HRESULT( Interop_Marshal_UINT8_ARRAY( stack, 1, param0 ) );

        INT32 param1;
        TINYCLR_CHECK_HRESULT( Interop_Marshal_INT32( stack, 2, param1 ) );

        INT32 param2;
        TINYCLR_CHECK_HRESULT( Interop_Marshal_INT32( stack, 3, param2 ) );

        CLR_RT_TypedArray_UINT8 param3;
        TINYCLR_CHECK_HRESULT( Interop_Marshal_UINT8_ARRAY( stack, 4, param3 ) );

        UINT8 retVal = Key_TinyEncryptionAlgorithm::Decrypt( pMngObj,  param0, param1, param2, param3, hr );
        TINYCLR_CHECK_HRESULT( hr );
        SetResult_UINT8( stack, retVal );

    }
    TINYCLR_NOCLEANUP();
}

HRESULT Library_spot_native_Microsoft_SPOT_Cryptography_Key_TinyEncryptionAlgorithm::get_Signature___SZARRAY_U1( CLR_RT_StackFrame& stack )
{
    TINYCLR_HEADER(); hr = S_OK;
    {
        CLR_RT_HeapBlock* pMngObj = Interop_Marshal_RetrieveManagedObject( stack );

        FAULT_ON_NULL(pMngObj);

        UINT8 retVal = Key_TinyEncryptionAlgorithm::get_Signature( pMngObj,  hr );
        TINYCLR_CHECK_HRESULT( hr );
        SetResult_UINT8( stack, retVal );

    }
    TINYCLR_NOCLEANUP();
}

HRESULT Library_spot_native_Microsoft_SPOT_Cryptography_Key_TinyEncryptionAlgorithm::GetActivationString___STRING__U2__U2( CLR_RT_StackFrame& stack )
{
    TINYCLR_HEADER(); hr = S_OK;
    {
        CLR_RT_HeapBlock* pMngObj = Interop_Marshal_RetrieveManagedObject( stack );

        FAULT_ON_NULL(pMngObj);

        UINT16 param0;
        TINYCLR_CHECK_HRESULT( Interop_Marshal_UINT16( stack, 1, param0 ) );

        UINT16 param1;
        TINYCLR_CHECK_HRESULT( Interop_Marshal_UINT16( stack, 2, param1 ) );

        LPCSTR retVal = Key_TinyEncryptionAlgorithm::GetActivationString( pMngObj,  param0, param1, hr );
        TINYCLR_CHECK_HRESULT( hr );
        SetResult_LPCSTR( stack, retVal );

    }
    TINYCLR_NOCLEANUP();
}
