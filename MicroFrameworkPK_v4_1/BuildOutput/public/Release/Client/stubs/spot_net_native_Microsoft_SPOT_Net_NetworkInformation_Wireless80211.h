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


#ifndef _SPOT_NET_NATIVE_MICROSOFT_SPOT_NET_NETWORKINFORMATION_WIRELESS80211_H_
#define _SPOT_NET_NATIVE_MICROSOFT_SPOT_NET_NETWORKINFORMATION_WIRELESS80211_H_

namespace Microsoft
{
    namespace SPOT
    {
        namespace Net
        {
            namespace NetworkInformation
            {
                struct Wireless80211
                {
                    // Helper Functions to access fields of managed object
                    static INT32& Get_Authentication( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT32( pMngObj, Library_spot_net_native_Microsoft_SPOT_Net_NetworkInformation_Wireless80211::FIELD__Authentication ); }

                    static INT32& Get_Encryption( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT32( pMngObj, Library_spot_net_native_Microsoft_SPOT_Net_NetworkInformation_Wireless80211::FIELD__Encryption ); }

                    static INT32& Get_Radio( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT32( pMngObj, Library_spot_net_native_Microsoft_SPOT_Net_NetworkInformation_Wireless80211::FIELD__Radio ); }

                    static LPCSTR& Get_PassPhrase( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_LPCSTR( pMngObj, Library_spot_net_native_Microsoft_SPOT_Net_NetworkInformation_Wireless80211::FIELD__PassPhrase ); }

                    static UNSUPPORTED_TYPE& Get_NetworkKey( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_spot_net_native_Microsoft_SPOT_Net_NetworkInformation_Wireless80211::FIELD__NetworkKey ); }

                    static UNSUPPORTED_TYPE& Get_ReKeyInternal( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_spot_net_native_Microsoft_SPOT_Net_NetworkInformation_Wireless80211::FIELD__ReKeyInternal ); }

                    static LPCSTR& Get_Ssid( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_LPCSTR( pMngObj, Library_spot_net_native_Microsoft_SPOT_Net_NetworkInformation_Wireless80211::FIELD__Ssid ); }

                    static UINT32& Get_Id( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UINT32( pMngObj, Library_spot_net_native_Microsoft_SPOT_Net_NetworkInformation_Wireless80211::FIELD__Id ); }

                    // Declaration of stubs. These functions are implemented by Interop code developers
                    static void UpdateConfiguration( UNSUPPORTED_TYPE param0, CHAR param1, HRESULT &hr );
                    static void SaveAllConfigurations( HRESULT &hr );
                };
            }
        }
    }
}
#endif  //_SPOT_NET_NATIVE_MICROSOFT_SPOT_NET_NETWORKINFORMATION_WIRELESS80211_H_
