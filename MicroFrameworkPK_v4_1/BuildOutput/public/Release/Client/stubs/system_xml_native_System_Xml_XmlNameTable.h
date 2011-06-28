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


#ifndef _SYSTEM_XML_NATIVE_SYSTEM_XML_XMLNAMETABLE_H_
#define _SYSTEM_XML_NATIVE_SYSTEM_XML_XMLNAMETABLE_H_

namespace System
{
    namespace Xml
    {
        struct XmlNameTable
        {
            // Helper Functions to access fields of managed object
            static UNSUPPORTED_TYPE& Get__entries( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_system_xml_native_System_Xml_XmlNameTable::FIELD___entries ); }

            static INT32& Get__count( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT32( pMngObj, Library_system_xml_native_System_Xml_XmlNameTable::FIELD___count ); }

            static INT32& Get__mask( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT32( pMngObj, Library_system_xml_native_System_Xml_XmlNameTable::FIELD___mask ); }

            static INT32& Get__hashCodeRandomizer( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT32( pMngObj, Library_system_xml_native_System_Xml_XmlNameTable::FIELD___hashCodeRandomizer ); }

            static UNSUPPORTED_TYPE& Get__tmp( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_system_xml_native_System_Xml_XmlNameTable::FIELD___tmp ); }

            // Declaration of stubs. These functions are implemented by Interop code developers
            static LPCSTR Get( CLR_RT_HeapBlock* pMngObj, LPCSTR param0, HRESULT &hr );
            static LPCSTR Add( CLR_RT_HeapBlock* pMngObj, LPCSTR param0, HRESULT &hr );
        };
    }
}
#endif  //_SYSTEM_XML_NATIVE_SYSTEM_XML_XMLNAMETABLE_H_
