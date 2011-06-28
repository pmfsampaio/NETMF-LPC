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


#ifndef _SPOT_HARDWARE_SERIAL_NATIVE_SYSTEM_IO_PORTS_SERIALPORT_H_
#define _SPOT_HARDWARE_SERIAL_NATIVE_SYSTEM_IO_PORTS_SERIALPORT_H_

namespace System
{
    namespace IO
    {
        namespace Ports
        {
            struct SerialPort
            {
                // Helper Functions to access fields of managed object
                static UNSUPPORTED_TYPE& Get_m_config( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_spot_hardware_serial_native_System_IO_Ports_SerialPort::FIELD__m_config ); }

                static INT8& Get_m_fDisposed( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT8( pMngObj, Library_spot_hardware_serial_native_System_IO_Ports_SerialPort::FIELD__m_fDisposed ); }

                static INT8& Get_m_fOpened( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT8( pMngObj, Library_spot_hardware_serial_native_System_IO_Ports_SerialPort::FIELD__m_fOpened ); }

                static LPCSTR& Get_m_portName( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_LPCSTR( pMngObj, Library_spot_hardware_serial_native_System_IO_Ports_SerialPort::FIELD__m_portName ); }

                static UNSUPPORTED_TYPE& Get_m_evtErrorEvent( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_spot_hardware_serial_native_System_IO_Ports_SerialPort::FIELD__m_evtErrorEvent ); }

                static UNSUPPORTED_TYPE& Get_m_evtDataEvent( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_spot_hardware_serial_native_System_IO_Ports_SerialPort::FIELD__m_evtDataEvent ); }

                static UNSUPPORTED_TYPE& Get_m_callbacksErrorEvent( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_spot_hardware_serial_native_System_IO_Ports_SerialPort::FIELD__m_callbacksErrorEvent ); }

                static UNSUPPORTED_TYPE& Get_m_callbacksDataEvent( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_spot_hardware_serial_native_System_IO_Ports_SerialPort::FIELD__m_callbacksDataEvent ); }

                // Declaration of stubs. These functions are implemented by Interop code developers
                static void InternalOpen( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
                static void InternalClose( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
                static INT32 Read( CLR_RT_HeapBlock* pMngObj, CLR_RT_TypedArray_UINT8 param0, INT32 param1, INT32 param2, HRESULT &hr );
                static INT32 Write( CLR_RT_HeapBlock* pMngObj, CLR_RT_TypedArray_UINT8 param0, INT32 param1, INT32 param2, HRESULT &hr );
                static void InternalDispose( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
                static void Flush( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
                static INT32 BytesInBuffer( CLR_RT_HeapBlock* pMngObj, INT8 param0, HRESULT &hr );
                static void DiscardBuffer( CLR_RT_HeapBlock* pMngObj, INT8 param0, HRESULT &hr );
            };
        }
    }
}
#endif  //_SPOT_HARDWARE_SERIAL_NATIVE_SYSTEM_IO_PORTS_SERIALPORT_H_
