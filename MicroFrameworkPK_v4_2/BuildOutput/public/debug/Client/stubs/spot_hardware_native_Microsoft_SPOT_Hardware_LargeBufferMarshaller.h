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


#ifndef _SPOT_HARDWARE_NATIVE_MICROSOFT_SPOT_HARDWARE_LARGEBUFFERMARSHALLER_H_
#define _SPOT_HARDWARE_NATIVE_MICROSOFT_SPOT_HARDWARE_LARGEBUFFERMARSHALLER_H_

namespace Microsoft
{
    namespace SPOT
    {
        namespace Hardware
        {
            struct LargeBufferMarshaller
            {
                // Helper Functions to access fields of managed object
                static UINT16& Get_m_id( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UINT16( pMngObj, Library_spot_hardware_native_Microsoft_SPOT_Hardware_LargeBufferMarshaller::FIELD__m_id ); }

                // Declaration of stubs. These functions are implemented by Interop code developers
                static void MarshalBuffer( CLR_RT_HeapBlock* pMngObj, UNSUPPORTED_TYPE param0, HRESULT &hr );
                static void UnMarshalBuffer( CLR_RT_HeapBlock* pMngObj, UNSUPPORTED_TYPE * param0, HRESULT &hr );
            };
        }
    }
}
#endif  //_SPOT_HARDWARE_NATIVE_MICROSOFT_SPOT_HARDWARE_LARGEBUFFERMARSHALLER_H_
