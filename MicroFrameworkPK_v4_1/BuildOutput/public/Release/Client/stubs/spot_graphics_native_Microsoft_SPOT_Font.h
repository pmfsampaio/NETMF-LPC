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


#ifndef _SPOT_GRAPHICS_NATIVE_MICROSOFT_SPOT_FONT_H_
#define _SPOT_GRAPHICS_NATIVE_MICROSOFT_SPOT_FONT_H_

namespace Microsoft
{
    namespace SPOT
    {
        struct Font
        {
            // Helper Functions to access fields of managed object
            static UNSUPPORTED_TYPE& Get_m_font( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_spot_graphics_native_Microsoft_SPOT_Font::FIELD__m_font ); }

            // Declaration of stubs. These functions are implemented by Interop code developers
            static INT32 CharWidth( CLR_RT_HeapBlock* pMngObj, CHAR param0, HRESULT &hr );
            static INT32 get_Height( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
            static INT32 get_AverageWidth( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
            static INT32 get_MaxWidth( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
            static INT32 get_Ascent( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
            static INT32 get_Descent( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
            static INT32 get_InternalLeading( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
            static INT32 get_ExternalLeading( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
            static void ComputeExtent( CLR_RT_HeapBlock* pMngObj, LPCSTR param0, INT32 * param1, INT32 * param2, INT32 param3, HRESULT &hr );
            static void ComputeTextInRect( CLR_RT_HeapBlock* pMngObj, LPCSTR param0, INT32 * param1, INT32 * param2, INT32 param3, INT32 param4, INT32 param5, INT32 param6, UINT32 param7, HRESULT &hr );
        };
    }
}
#endif  //_SPOT_GRAPHICS_NATIVE_MICROSOFT_SPOT_FONT_H_
