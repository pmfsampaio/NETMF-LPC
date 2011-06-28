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


#ifndef _SPOT_HARDWARE_NATIVE_MICROSOFT_SPOT_HARDWARE_PORT_H_
#define _SPOT_HARDWARE_NATIVE_MICROSOFT_SPOT_HARDWARE_PORT_H_

namespace Microsoft
{
    namespace SPOT
    {
        namespace Hardware
        {
            struct Port
            {
                // Helper Functions to access fields of managed object
                static INT32& Get_m_interruptMode( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT32( pMngObj, Library_spot_hardware_native_Microsoft_SPOT_Hardware_Port::FIELD__m_interruptMode ); }

                static INT32& Get_m_resistorMode( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT32( pMngObj, Library_spot_hardware_native_Microsoft_SPOT_Hardware_Port::FIELD__m_resistorMode ); }

                static UINT32& Get_m_portId( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UINT32( pMngObj, Library_spot_hardware_native_Microsoft_SPOT_Hardware_Port::FIELD__m_portId ); }

                static UINT32& Get_m_flags( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UINT32( pMngObj, Library_spot_hardware_native_Microsoft_SPOT_Hardware_Port::FIELD__m_flags ); }

                static INT8& Get_m_glitchFilterEnable( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT8( pMngObj, Library_spot_hardware_native_Microsoft_SPOT_Hardware_Port::FIELD__m_glitchFilterEnable ); }

                static INT8& Get_m_initialState( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT8( pMngObj, Library_spot_hardware_native_Microsoft_SPOT_Hardware_Port::FIELD__m_initialState ); }

                // Declaration of stubs. These functions are implemented by Interop code developers
                static void Dispose( CLR_RT_HeapBlock* pMngObj, INT8 param0, HRESULT &hr );
                static void _ctor( CLR_RT_HeapBlock* pMngObj, INT32 param0, INT8 param1, INT32 param2, INT32 param3, HRESULT &hr );
                static void _ctor( CLR_RT_HeapBlock* pMngObj, INT32 param0, INT8 param1, HRESULT &hr );
                static void _ctor( CLR_RT_HeapBlock* pMngObj, INT32 param0, INT8 param1, INT8 param2, INT32 param3, HRESULT &hr );
                static INT8 Read( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
                static INT32 get_Id( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
                static INT8 ReservePin( INT32 param0, INT8 param1, HRESULT &hr );
            };
        }
    }
}
#endif  //_SPOT_HARDWARE_NATIVE_MICROSOFT_SPOT_HARDWARE_PORT_H_
