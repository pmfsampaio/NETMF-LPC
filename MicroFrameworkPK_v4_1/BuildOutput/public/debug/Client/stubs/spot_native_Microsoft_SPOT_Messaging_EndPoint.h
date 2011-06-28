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


#ifndef _SPOT_NATIVE_MICROSOFT_SPOT_MESSAGING_ENDPOINT_H_
#define _SPOT_NATIVE_MICROSOFT_SPOT_MESSAGING_ENDPOINT_H_

namespace Microsoft
{
    namespace SPOT
    {
        namespace Messaging
        {
            struct EndPoint
            {
                // Helper Functions to access fields of managed object
                static UNSUPPORTED_TYPE& Get_m_handle( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_spot_native_Microsoft_SPOT_Messaging_EndPoint::FIELD__m_handle ); }

                // Declaration of stubs. These functions are implemented by Interop code developers
                static void _ctor( CLR_RT_HeapBlock* pMngObj, UNSUPPORTED_TYPE param0, UNSUPPORTED_TYPE param1, HRESULT &hr );
                static INT8 Check( CLR_RT_HeapBlock* pMngObj, UNSUPPORTED_TYPE param0, UNSUPPORTED_TYPE param1, UINT32 param2, HRESULT &hr );
                static UNSUPPORTED_TYPE GetMessage( CLR_RT_HeapBlock* pMngObj, UNSUPPORTED_TYPE param0, HRESULT &hr );
                static UINT8 SendMessageRaw( CLR_RT_HeapBlock* pMngObj, UNSUPPORTED_TYPE param0, UNSUPPORTED_TYPE param1, UINT32 param2, INT32 param3, HRESULT &hr );
                static void ReplyRaw( CLR_RT_HeapBlock* pMngObj, UNSUPPORTED_TYPE param0, UNSUPPORTED_TYPE param1, HRESULT &hr );
            };
        }
    }
}
#endif  //_SPOT_NATIVE_MICROSOFT_SPOT_MESSAGING_ENDPOINT_H_
