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


#ifndef _SPOT_HARDWARE_NATIVE_MICROSOFT_SPOT_HARDWARE_SPI_H_
#define _SPOT_HARDWARE_NATIVE_MICROSOFT_SPOT_HARDWARE_SPI_H_

namespace Microsoft
{
    namespace SPOT
    {
        namespace Hardware
        {
            struct SPI
            {
                // Helper Functions to access fields of managed object
                static UNSUPPORTED_TYPE& Get_m_config( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_spot_hardware_native_Microsoft_SPOT_Hardware_SPI::FIELD__m_config ); }

                static UNSUPPORTED_TYPE& Get_m_cs( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_spot_hardware_native_Microsoft_SPOT_Hardware_SPI::FIELD__m_cs ); }

                static INT8& Get_m_disposed( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT8( pMngObj, Library_spot_hardware_native_Microsoft_SPOT_Hardware_SPI::FIELD__m_disposed ); }

                // Declaration of stubs. These functions are implemented by Interop code developers
                static void InternalWriteRead( CLR_RT_HeapBlock* pMngObj, CLR_RT_TypedArray_UINT16 param0, INT32 param1, INT32 param2, CLR_RT_TypedArray_UINT16 param3, INT32 param4, INT32 param5, INT32 param6, HRESULT &hr );
                static void InternalWriteRead( CLR_RT_HeapBlock* pMngObj, CLR_RT_TypedArray_UINT8 param0, INT32 param1, INT32 param2, CLR_RT_TypedArray_UINT8 param3, INT32 param4, INT32 param5, INT32 param6, HRESULT &hr );
            };
        }
    }
}
#endif  //_SPOT_HARDWARE_NATIVE_MICROSOFT_SPOT_HARDWARE_SPI_H_
