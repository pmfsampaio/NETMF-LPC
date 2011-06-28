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


#ifndef _CORLIB_NATIVE_SYSTEM_RESOURCES_RESOURCEMANAGER_H_
#define _CORLIB_NATIVE_SYSTEM_RESOURCES_RESOURCEMANAGER_H_

namespace System
{
    namespace Resources
    {
        struct ResourceManager
        {
            // Helper Functions to access fields of managed object
            static INT32& Get_m_resourceFileId( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT32( pMngObj, Library_corlib_native_System_Resources_ResourceManager::FIELD__m_resourceFileId ); }

            static UNSUPPORTED_TYPE& Get_m_assembly( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_corlib_native_System_Resources_ResourceManager::FIELD__m_assembly ); }

            static UNSUPPORTED_TYPE& Get_m_baseAssembly( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_corlib_native_System_Resources_ResourceManager::FIELD__m_baseAssembly ); }

            static LPCSTR& Get_m_baseName( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_LPCSTR( pMngObj, Library_corlib_native_System_Resources_ResourceManager::FIELD__m_baseName ); }

            static LPCSTR& Get_m_cultureName( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_LPCSTR( pMngObj, Library_corlib_native_System_Resources_ResourceManager::FIELD__m_cultureName ); }

            static UNSUPPORTED_TYPE& Get_m_rmFallback( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_corlib_native_System_Resources_ResourceManager::FIELD__m_rmFallback ); }

            // Declaration of stubs. These functions are implemented by Interop code developers
            static UNSUPPORTED_TYPE GetObjectInternal( CLR_RT_HeapBlock* pMngObj, INT16 param0, HRESULT &hr );
            static INT32 FindResource( LPCSTR param0, UNSUPPORTED_TYPE param1, HRESULT &hr );
            static UNSUPPORTED_TYPE GetObject( UNSUPPORTED_TYPE param0, UNSUPPORTED_TYPE param1, HRESULT &hr );
        };
    }
}
#endif  //_CORLIB_NATIVE_SYSTEM_RESOURCES_RESOURCEMANAGER_H_
