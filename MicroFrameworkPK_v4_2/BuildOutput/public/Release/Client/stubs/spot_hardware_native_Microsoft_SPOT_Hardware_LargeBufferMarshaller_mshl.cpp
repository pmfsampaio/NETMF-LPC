//-----------------------------------------------------------------------------
//
//    ** DO NOT EDIT THIS FILE! **
//    This file was generated by a tool
//    re-running the tool will overwrite this file.
//
//-----------------------------------------------------------------------------


#include "spot_hardware_native.h"
#include "spot_hardware_native_Microsoft_SPOT_Hardware_LargeBufferMarshaller.h"

using namespace Microsoft::SPOT::Hardware;


HRESULT Library_spot_hardware_native_Microsoft_SPOT_Hardware_LargeBufferMarshaller::MarshalBuffer___VOID__MicrosoftSPOTHardwareLargeBuffer( CLR_RT_StackFrame& stack )
{
    TINYCLR_HEADER(); hr = S_OK;
    {
        CLR_RT_HeapBlock* pMngObj = Interop_Marshal_RetrieveManagedObject( stack );

        FAULT_ON_NULL(pMngObj);

        UNSUPPORTED_TYPE param0;
        TINYCLR_CHECK_HRESULT( Interop_Marshal_UNSUPPORTED_TYPE( stack, 1, param0 ) );

        LargeBufferMarshaller::MarshalBuffer( pMngObj,  param0, hr );
        TINYCLR_CHECK_HRESULT( hr );
    }
    TINYCLR_NOCLEANUP();
}

HRESULT Library_spot_hardware_native_Microsoft_SPOT_Hardware_LargeBufferMarshaller::UnMarshalBuffer___VOID__BYREF_MicrosoftSPOTHardwareLargeBuffer( CLR_RT_StackFrame& stack )
{
    TINYCLR_HEADER(); hr = S_OK;
    {
        CLR_RT_HeapBlock* pMngObj = Interop_Marshal_RetrieveManagedObject( stack );

        FAULT_ON_NULL(pMngObj);

        UNSUPPORTED_TYPE * param0;
        UINT8 heapblock0[CLR_RT_HEAP_BLOCK_SIZE];
        TINYCLR_CHECK_HRESULT( Interop_Marshal_UNSUPPORTED_TYPE_ByRef( stack, heapblock0, 1, param0 ) );

        LargeBufferMarshaller::UnMarshalBuffer( pMngObj,  param0, hr );
        TINYCLR_CHECK_HRESULT( hr );
        TINYCLR_CHECK_HRESULT( Interop_Marshal_StoreRef( stack, heapblock0, 1 ) );
    }
    TINYCLR_NOCLEANUP();
}