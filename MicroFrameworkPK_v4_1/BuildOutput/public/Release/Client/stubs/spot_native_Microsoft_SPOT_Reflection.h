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


#ifndef _SPOT_NATIVE_MICROSOFT_SPOT_REFLECTION_H_
#define _SPOT_NATIVE_MICROSOFT_SPOT_REFLECTION_H_

namespace Microsoft
{
    namespace SPOT
    {
        struct Reflection
        {
            // Helper Functions to access fields of managed object
            // Declaration of stubs. These functions are implemented by Interop code developers
            static UNSUPPORTED_TYPE GetTypesImplementingInterface( UNSUPPORTED_TYPE param0, HRESULT &hr );
            static INT8 IsTypeLoaded( UNSUPPORTED_TYPE param0, HRESULT &hr );
            static UINT32 GetTypeHash( UNSUPPORTED_TYPE param0, HRESULT &hr );
            static UINT32 GetAssemblyHash( UNSUPPORTED_TYPE param0, HRESULT &hr );
            static UNSUPPORTED_TYPE GetAssemblies( HRESULT &hr );
            static INT8 GetAssemblyInfo( CLR_RT_TypedArray_UINT8 param0, UNSUPPORTED_TYPE param1, HRESULT &hr );
            static INT8 GetAssemblyMemoryInfo( UNSUPPORTED_TYPE param0, UNSUPPORTED_TYPE param1, HRESULT &hr );
            static UNSUPPORTED_TYPE GetTypeFromHash( UNSUPPORTED_TYPE param0, HRESULT &hr );
            static UNSUPPORTED_TYPE GetAssemblyFromHash( UNSUPPORTED_TYPE param0, HRESULT &hr );
            static UINT8 Serialize( UNSUPPORTED_TYPE param0, UNSUPPORTED_TYPE param1, HRESULT &hr );
            static UNSUPPORTED_TYPE Deserialize( CLR_RT_TypedArray_UINT8 param0, UNSUPPORTED_TYPE param1, HRESULT &hr );
        };
    }
}
#endif  //_SPOT_NATIVE_MICROSOFT_SPOT_REFLECTION_H_
