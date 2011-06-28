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


#ifndef _SPOT_GRAPHICS_NATIVE_MICROSOFT_SPOT_BITMAP_H_
#define _SPOT_GRAPHICS_NATIVE_MICROSOFT_SPOT_BITMAP_H_

namespace Microsoft
{
    namespace SPOT
    {
        struct Bitmap
        {
            // Helper Functions to access fields of managed object
            static UNSUPPORTED_TYPE& Get_m_bitmap( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_spot_graphics_native_Microsoft_SPOT_Bitmap::FIELD__m_bitmap ); }

            // Declaration of stubs. These functions are implemented by Interop code developers
            static void _ctor( CLR_RT_HeapBlock* pMngObj, INT32 param0, INT32 param1, HRESULT &hr );
            static void _ctor( CLR_RT_HeapBlock* pMngObj, CLR_RT_TypedArray_UINT8 param0, UINT8 param1, HRESULT &hr );
            static void Flush( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
            static void Flush( CLR_RT_HeapBlock* pMngObj, INT32 param0, INT32 param1, INT32 param2, INT32 param3, HRESULT &hr );
            static void Clear( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
            static INT8 DrawTextInRect( CLR_RT_HeapBlock* pMngObj, LPCSTR * param0, INT32 * param1, INT32 * param2, INT32 param3, INT32 param4, INT32 param5, INT32 param6, UINT32 param7, UINT32 param8, UNSUPPORTED_TYPE param9, HRESULT &hr );
            static void SetClippingRectangle( CLR_RT_HeapBlock* pMngObj, INT32 param0, INT32 param1, INT32 param2, INT32 param3, HRESULT &hr );
            static INT32 get_Width( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
            static INT32 get_Height( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
            static void DrawEllipse( CLR_RT_HeapBlock* pMngObj, UINT32 param0, INT32 param1, INT32 param2, INT32 param3, INT32 param4, INT32 param5, UINT32 param6, INT32 param7, INT32 param8, UINT32 param9, INT32 param10, INT32 param11, UINT16 param12, HRESULT &hr );
            static void DrawImage( CLR_RT_HeapBlock* pMngObj, INT32 param0, INT32 param1, UNSUPPORTED_TYPE param2, void param3, INT32 param4, INT32 param5, INT32 param6, INT32 param7, HRESULT &hr );
            static void RotateImage( CLR_RT_HeapBlock* pMngObj, INT32 param0, INT32 param1, INT32 param2, UNSUPPORTED_TYPE param3, void param4, INT32 param5, INT32 param6, INT32 param7, INT32 param8, HRESULT &hr );
            static void MakeTransparent( CLR_RT_HeapBlock* pMngObj, UINT32 param0, HRESULT &hr );
            static void StretchImage( CLR_RT_HeapBlock* pMngObj, INT32 param0, INT32 param1, UNSUPPORTED_TYPE param2, void param3, INT32 param4, INT32 param5, HRESULT &hr );
            static void DrawLine( CLR_RT_HeapBlock* pMngObj, UINT32 param0, INT32 param1, INT32 param2, INT32 param3, INT32 param4, INT32 param5, HRESULT &hr );
            static void DrawRectangle( CLR_RT_HeapBlock* pMngObj, UINT32 param0, INT32 param1, INT32 param2, INT32 param3, INT32 param4, INT32 param5, INT32 param6, INT32 param7, UINT32 param8, INT32 param9, INT32 param10, UINT32 param11, INT32 param12, INT32 param13, UINT16 param14, HRESULT &hr );
            static void DrawText( CLR_RT_HeapBlock* pMngObj, LPCSTR param0, UNSUPPORTED_TYPE param1, UINT32 param2, UINT32 param3, INT32 param4, HRESULT &hr );
            static void SetPixel( CLR_RT_HeapBlock* pMngObj, INT32 param0, INT32 param1, UINT32 param2, HRESULT &hr );
            static UINT32 GetPixel( CLR_RT_HeapBlock* pMngObj, INT32 param0, INT32 param1, HRESULT &hr );
            static UINT8 GetBitmap( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
            static void StretchImage( CLR_RT_HeapBlock* pMngObj, INT32 param0, INT32 param1, INT32 param2, INT32 param3, UNSUPPORTED_TYPE param4, void param5, INT32 param6, INT32 param7, INT32 param8, INT32 param9, HRESULT &hr );
            static void TileImage( CLR_RT_HeapBlock* pMngObj, INT32 param0, INT32 param1, UNSUPPORTED_TYPE param2, void param3, INT32 param4, INT32 param5, HRESULT &hr );
            static void Scale9Image( CLR_RT_HeapBlock* pMngObj, INT32 param0, INT32 param1, INT32 param2, INT32 param3, UNSUPPORTED_TYPE param4, void param5, INT32 param6, INT32 param7, INT32 param8, INT32 param9, HRESULT &hr );
            static void Dispose( CLR_RT_HeapBlock* pMngObj, INT8 param0, HRESULT &hr );
        };
    }
}
#endif  //_SPOT_GRAPHICS_NATIVE_MICROSOFT_SPOT_BITMAP_H_
