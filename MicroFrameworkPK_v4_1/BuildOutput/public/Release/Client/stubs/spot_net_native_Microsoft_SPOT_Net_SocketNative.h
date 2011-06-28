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


#ifndef _SPOT_NET_NATIVE_MICROSOFT_SPOT_NET_SOCKETNATIVE_H_
#define _SPOT_NET_NATIVE_MICROSOFT_SPOT_NET_SOCKETNATIVE_H_

namespace Microsoft
{
    namespace SPOT
    {
        namespace Net
        {
            struct SocketNative
            {
                // Helper Functions to access fields of managed object
                // Declaration of stubs. These functions are implemented by Interop code developers
                static INT32 socket( INT32 param0, INT32 param1, INT32 param2, HRESULT &hr );
                static void bind( UNSUPPORTED_TYPE param0, CLR_RT_TypedArray_UINT8 param1, HRESULT &hr );
                static void connect( UNSUPPORTED_TYPE param0, CLR_RT_TypedArray_UINT8 param1, INT8 param2, HRESULT &hr );
                static INT32 send( UNSUPPORTED_TYPE param0, CLR_RT_TypedArray_UINT8 param1, INT32 param2, INT32 param3, INT32 param4, INT32 param5, HRESULT &hr );
                static INT32 recv( UNSUPPORTED_TYPE param0, CLR_RT_TypedArray_UINT8 param1, INT32 param2, INT32 param3, INT32 param4, INT32 param5, HRESULT &hr );
                static INT32 close( UNSUPPORTED_TYPE param0, HRESULT &hr );
                static void listen( UNSUPPORTED_TYPE param0, INT32 param1, HRESULT &hr );
                static INT32 accept( UNSUPPORTED_TYPE param0, HRESULT &hr );
                static void getaddrinfo( LPCSTR param0, LPCSTR * param1, UNSUPPORTED_TYPE * param2, HRESULT &hr );
                static void shutdown( UNSUPPORTED_TYPE param0, INT32 param1, INT32 * param2, HRESULT &hr );
                static INT32 sendto( UNSUPPORTED_TYPE param0, CLR_RT_TypedArray_UINT8 param1, INT32 param2, INT32 param3, INT32 param4, INT32 param5, CLR_RT_TypedArray_UINT8 param6, HRESULT &hr );
                static INT32 recvfrom( UNSUPPORTED_TYPE param0, CLR_RT_TypedArray_UINT8 param1, INT32 param2, INT32 param3, INT32 param4, INT32 param5, UNSUPPORTED_TYPE * param6, HRESULT &hr );
                static void getpeername( UNSUPPORTED_TYPE param0, UNSUPPORTED_TYPE * param1, HRESULT &hr );
                static void getsockname( UNSUPPORTED_TYPE param0, UNSUPPORTED_TYPE * param1, HRESULT &hr );
                static void getsockopt( UNSUPPORTED_TYPE param0, INT32 param1, INT32 param2, CLR_RT_TypedArray_UINT8 param3, HRESULT &hr );
                static void setsockopt( UNSUPPORTED_TYPE param0, INT32 param1, INT32 param2, CLR_RT_TypedArray_UINT8 param3, HRESULT &hr );
                static INT8 poll( UNSUPPORTED_TYPE param0, INT32 param1, INT32 param2, HRESULT &hr );
                static void ioctl( UNSUPPORTED_TYPE param0, UINT32 param1, UINT32 * param2, HRESULT &hr );
            };
        }
    }
}
#endif  //_SPOT_NET_NATIVE_MICROSOFT_SPOT_NET_SOCKETNATIVE_H_
