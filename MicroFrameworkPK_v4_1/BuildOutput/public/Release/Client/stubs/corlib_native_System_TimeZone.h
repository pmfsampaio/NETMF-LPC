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


#ifndef _CORLIB_NATIVE_SYSTEM_TIMEZONE_H_
#define _CORLIB_NATIVE_SYSTEM_TIMEZONE_H_

namespace System
{
    struct TimeZone
    {
        // Helper Functions to access fields of managed object
        static INT32& Get_m_id( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT32( pMngObj, Library_corlib_native_System_TimeZone::FIELD__m_id ); }

        // Declaration of stubs. These functions are implemented by Interop code developers
        static INT64 GetTimeZoneOffset( HRESULT &hr );
    };
}
#endif  //_CORLIB_NATIVE_SYSTEM_TIMEZONE_H_
