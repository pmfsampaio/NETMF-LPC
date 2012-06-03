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


#ifndef _SPOT_HARDWARE_NATIVE_MICROSOFT_SPOT_HARDWARE_BATTERY__CHARGERMODEL_H_
#define _SPOT_HARDWARE_NATIVE_MICROSOFT_SPOT_HARDWARE_BATTERY__CHARGERMODEL_H_

namespace Microsoft
{
    namespace SPOT
    {
        namespace Hardware
        {
            struct Battery_ChargerModel
            {
                // Helper Functions to access fields of managed object
                static INT32& Get_Charge_Min( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT32( pMngObj, Library_spot_hardware_native_Microsoft_SPOT_Hardware_Battery__ChargerModel::FIELD__Charge_Min ); }

                static INT32& Get_Charge_Low( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT32( pMngObj, Library_spot_hardware_native_Microsoft_SPOT_Hardware_Battery__ChargerModel::FIELD__Charge_Low ); }

                static INT32& Get_Charge_Medium( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT32( pMngObj, Library_spot_hardware_native_Microsoft_SPOT_Hardware_Battery__ChargerModel::FIELD__Charge_Medium ); }

                static INT32& Get_Charge_Full( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT32( pMngObj, Library_spot_hardware_native_Microsoft_SPOT_Hardware_Battery__ChargerModel::FIELD__Charge_Full ); }

                static INT32& Get_Charge_FullMin( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT32( pMngObj, Library_spot_hardware_native_Microsoft_SPOT_Hardware_Battery__ChargerModel::FIELD__Charge_FullMin ); }

                static INT32& Get_Charge_Hysteresis( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT32( pMngObj, Library_spot_hardware_native_Microsoft_SPOT_Hardware_Battery__ChargerModel::FIELD__Charge_Hysteresis ); }

                static UNSUPPORTED_TYPE& Get_Timeout_Charging( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_spot_hardware_native_Microsoft_SPOT_Hardware_Battery__ChargerModel::FIELD__Timeout_Charging ); }

                static UNSUPPORTED_TYPE& Get_Timeout_Charged( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_spot_hardware_native_Microsoft_SPOT_Hardware_Battery__ChargerModel::FIELD__Timeout_Charged ); }

                static UNSUPPORTED_TYPE& Get_Timeout_Charger( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_spot_hardware_native_Microsoft_SPOT_Hardware_Battery__ChargerModel::FIELD__Timeout_Charger ); }

                static UNSUPPORTED_TYPE& Get_Timeout_Backlight( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_spot_hardware_native_Microsoft_SPOT_Hardware_Battery__ChargerModel::FIELD__Timeout_Backlight ); }

                // Declaration of stubs. These functions are implemented by Interop code developers
                static void _ctor( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
            };
        }
    }
}
#endif  //_SPOT_HARDWARE_NATIVE_MICROSOFT_SPOT_HARDWARE_BATTERY__CHARGERMODEL_H_
