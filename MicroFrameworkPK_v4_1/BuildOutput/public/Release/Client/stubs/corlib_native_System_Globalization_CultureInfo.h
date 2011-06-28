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


#ifndef _CORLIB_NATIVE_SYSTEM_GLOBALIZATION_CULTUREINFO_H_
#define _CORLIB_NATIVE_SYSTEM_GLOBALIZATION_CULTUREINFO_H_

namespace System
{
    namespace Globalization
    {
        struct CultureInfo
        {
            // Helper Functions to access fields of managed object
            static UNSUPPORTED_TYPE& Get_numInfo( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_corlib_native_System_Globalization_CultureInfo::FIELD__numInfo ); }

            static UNSUPPORTED_TYPE& Get_dateTimeInfo( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_corlib_native_System_Globalization_CultureInfo::FIELD__dateTimeInfo ); }

            static LPCSTR& Get_m_name( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_LPCSTR( pMngObj, Library_corlib_native_System_Globalization_CultureInfo::FIELD__m_name ); }

            static UNSUPPORTED_TYPE& Get_m_rm( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_corlib_native_System_Globalization_CultureInfo::FIELD__m_rm ); }

            static UNSUPPORTED_TYPE& Get_m_parent( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_corlib_native_System_Globalization_CultureInfo::FIELD__m_parent ); }

            // Declaration of stubs. These functions are implemented by Interop code developers
            static UNSUPPORTED_TYPE get_CurrentUICultureInternal( HRESULT &hr );
            static void set_CurrentUICultureInternal( UNSUPPORTED_TYPE param0, HRESULT &hr );
        };
    }
}
#endif  //_CORLIB_NATIVE_SYSTEM_GLOBALIZATION_CULTUREINFO_H_
