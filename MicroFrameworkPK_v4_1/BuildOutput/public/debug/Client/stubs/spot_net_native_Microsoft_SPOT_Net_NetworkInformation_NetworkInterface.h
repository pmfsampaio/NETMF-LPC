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


#ifndef _SPOT_NET_NATIVE_MICROSOFT_SPOT_NET_NETWORKINFORMATION_NETWORKINTERFACE_H_
#define _SPOT_NET_NATIVE_MICROSOFT_SPOT_NET_NETWORKINFORMATION_NETWORKINTERFACE_H_

namespace Microsoft
{
    namespace SPOT
    {
        namespace Net
        {
            namespace NetworkInformation
            {
                struct NetworkInterface
                {
                    // Helper Functions to access fields of managed object
                    static INT32& Get__interfaceIndex( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT32( pMngObj, Library_spot_net_native_Microsoft_SPOT_Net_NetworkInformation_NetworkInterface::FIELD___interfaceIndex ); }

                    static UINT32& Get__flags( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UINT32( pMngObj, Library_spot_net_native_Microsoft_SPOT_Net_NetworkInformation_NetworkInterface::FIELD___flags ); }

                    static UINT32& Get__ipAddress( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UINT32( pMngObj, Library_spot_net_native_Microsoft_SPOT_Net_NetworkInformation_NetworkInterface::FIELD___ipAddress ); }

                    static UINT32& Get__gatewayAddress( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UINT32( pMngObj, Library_spot_net_native_Microsoft_SPOT_Net_NetworkInformation_NetworkInterface::FIELD___gatewayAddress ); }

                    static UINT32& Get__subnetMask( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UINT32( pMngObj, Library_spot_net_native_Microsoft_SPOT_Net_NetworkInformation_NetworkInterface::FIELD___subnetMask ); }

                    static UINT32& Get__dnsAddress1( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UINT32( pMngObj, Library_spot_net_native_Microsoft_SPOT_Net_NetworkInformation_NetworkInterface::FIELD___dnsAddress1 ); }

                    static UINT32& Get__dnsAddress2( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UINT32( pMngObj, Library_spot_net_native_Microsoft_SPOT_Net_NetworkInformation_NetworkInterface::FIELD___dnsAddress2 ); }

                    static INT32& Get__networkInterfaceType( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT32( pMngObj, Library_spot_net_native_Microsoft_SPOT_Net_NetworkInformation_NetworkInterface::FIELD___networkInterfaceType ); }

                    static UNSUPPORTED_TYPE& Get__macAddress( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_spot_net_native_Microsoft_SPOT_Net_NetworkInformation_NetworkInterface::FIELD___macAddress ); }

                    // Declaration of stubs. These functions are implemented by Interop code developers
                    static void InitializeNetworkInterfaceSettings( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
                    static void UpdateConfiguration( CLR_RT_HeapBlock* pMngObj, INT32 param0, HRESULT &hr );
                    static INT32 GetNetworkInterfaceCount( HRESULT &hr );
                    static UNSUPPORTED_TYPE GetNetworkInterface( void param0, HRESULT &hr );
                    static UINT32 IPAddressFromString( LPCSTR param0, HRESULT &hr );
                };
            }
        }
    }
}
#endif  //_SPOT_NET_NATIVE_MICROSOFT_SPOT_NET_NETWORKINFORMATION_NETWORKINTERFACE_H_
