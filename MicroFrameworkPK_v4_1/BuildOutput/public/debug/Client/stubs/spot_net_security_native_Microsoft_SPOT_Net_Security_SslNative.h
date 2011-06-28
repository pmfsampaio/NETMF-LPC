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


#ifndef _SPOT_NET_SECURITY_NATIVE_MICROSOFT_SPOT_NET_SECURITY_SSLNATIVE_H_
#define _SPOT_NET_SECURITY_NATIVE_MICROSOFT_SPOT_NET_SECURITY_SSLNATIVE_H_

namespace Microsoft
{
    namespace SPOT
    {
        namespace Net
        {
            namespace Security
            {
                struct SslNative
                {
                    // Helper Functions to access fields of managed object
                    // Declaration of stubs. These functions are implemented by Interop code developers
                    static INT32 SecureServerInit( INT32 param0, INT32 param1, UNSUPPORTED_TYPE param2, double param3, HRESULT &hr );
                    static INT32 SecureClientInit( INT32 param0, INT32 param1, UNSUPPORTED_TYPE param2, double param3, HRESULT &hr );
                    static void UpdateCertificates( INT32 param0, UNSUPPORTED_TYPE param1, double param2, HRESULT &hr );
                    static void SecureAccept( INT32 param0, UNSUPPORTED_TYPE param1, HRESULT &hr );
                    static void SecureConnect( INT32 param0, LPCSTR param1, UNSUPPORTED_TYPE param2, HRESULT &hr );
                    static INT32 SecureRead( UNSUPPORTED_TYPE param0, CLR_RT_TypedArray_UINT8 param1, INT32 param2, INT32 param3, INT32 param4, HRESULT &hr );
                    static INT32 SecureWrite( UNSUPPORTED_TYPE param0, CLR_RT_TypedArray_UINT8 param1, INT32 param2, INT32 param3, INT32 param4, HRESULT &hr );
                    static INT32 SecureCloseSocket( UNSUPPORTED_TYPE param0, HRESULT &hr );
                    static INT32 ExitSecureContext( INT32 param0, HRESULT &hr );
                    static void ParseCertificate( CLR_RT_TypedArray_UINT8 param0, LPCSTR param1, LPCSTR * param2, LPCSTR * param3, UNSUPPORTED_TYPE * param4, float param5, HRESULT &hr );
                    static INT32 DataAvailable( UNSUPPORTED_TYPE param0, HRESULT &hr );
                };
            }
        }
    }
}
#endif  //_SPOT_NET_SECURITY_NATIVE_MICROSOFT_SPOT_NET_SECURITY_SSLNATIVE_H_
