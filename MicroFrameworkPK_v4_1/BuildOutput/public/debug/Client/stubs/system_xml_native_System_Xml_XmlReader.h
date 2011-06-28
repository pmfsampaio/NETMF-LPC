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


#ifndef _SYSTEM_XML_NATIVE_SYSTEM_XML_XMLREADER_H_
#define _SYSTEM_XML_NATIVE_SYSTEM_XML_XMLREADER_H_

namespace System
{
    namespace Xml
    {
        struct XmlReader
        {
            // Helper Functions to access fields of managed object
            static UNSUPPORTED_TYPE& Get__buffer( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_system_xml_native_System_Xml_XmlReader::FIELD___buffer ); }

            static INT32& Get__offset( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT32( pMngObj, Library_system_xml_native_System_Xml_XmlReader::FIELD___offset ); }

            static INT32& Get__length( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT32( pMngObj, Library_system_xml_native_System_Xml_XmlReader::FIELD___length ); }

            static UNSUPPORTED_TYPE& Get__xmlNodes( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_system_xml_native_System_Xml_XmlReader::FIELD___xmlNodes ); }

            static UNSUPPORTED_TYPE& Get__namespaces( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_system_xml_native_System_Xml_XmlReader::FIELD___namespaces ); }

            static UNSUPPORTED_TYPE& Get__xmlSpaces( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_system_xml_native_System_Xml_XmlReader::FIELD___xmlSpaces ); }

            static UNSUPPORTED_TYPE& Get__xmlLangs( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_system_xml_native_System_Xml_XmlReader::FIELD___xmlLangs ); }

            static INT32& Get__nodeType( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT32( pMngObj, Library_system_xml_native_System_Xml_XmlReader::FIELD___nodeType ); }

            static LPCSTR& Get__value( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_LPCSTR( pMngObj, Library_system_xml_native_System_Xml_XmlReader::FIELD___value ); }

            static INT8& Get__isEmptyElement( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT8( pMngObj, Library_system_xml_native_System_Xml_XmlReader::FIELD___isEmptyElement ); }

            static UNSUPPORTED_TYPE& Get__attributes( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_system_xml_native_System_Xml_XmlReader::FIELD___attributes ); }

            static UNSUPPORTED_TYPE& Get__nameTable( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_system_xml_native_System_Xml_XmlReader::FIELD___nameTable ); }

            static UNSUPPORTED_TYPE& Get__state( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_system_xml_native_System_Xml_XmlReader::FIELD___state ); }

            static INT8& Get__isDone( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT8( pMngObj, Library_system_xml_native_System_Xml_XmlReader::FIELD___isDone ); }

            static INT32& Get__currentAttribute( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT32( pMngObj, Library_system_xml_native_System_Xml_XmlReader::FIELD___currentAttribute ); }

            static UNSUPPORTED_TYPE& Get__stream( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_system_xml_native_System_Xml_XmlReader::FIELD___stream ); }

            static INT32& Get__readState( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT32( pMngObj, Library_system_xml_native_System_Xml_XmlReader::FIELD___readState ); }

            // Declaration of stubs. These functions are implemented by Interop code developers
            static LPCSTR LookupNamespace( CLR_RT_HeapBlock* pMngObj, LPCSTR param0, HRESULT &hr );
            static void Initialize( CLR_RT_HeapBlock* pMngObj, UINT32 param0, HRESULT &hr );
            static INT32 ReadInternal( CLR_RT_HeapBlock* pMngObj, UINT32 param0, HRESULT &hr );
            static INT8 StringRefEquals( LPCSTR param0, LPCSTR param1, HRESULT &hr );
        };
    }
}
#endif  //_SYSTEM_XML_NATIVE_SYSTEM_XML_XMLREADER_H_
