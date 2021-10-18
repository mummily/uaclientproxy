/*****************************************************************************
 *                                                                           *
 * Copyright (c) 2006-2018 Unified Automation GmbH. All rights reserved.     *
 *                                                                           *
 * Software License Agreement ("SLA") Version 2.7                            *
 *                                                                           *
 * Unless explicitly acquired and licensed from Licensor under another       *
 * license, the contents of this file are subject to the Software License    *
 * Agreement ("SLA") Version 2.7, or subsequent versions as allowed by the   *
 * SLA, and You may not copy or use this file in either source code or       *
 * executable form, except in compliance with the terms and conditions of    *
 * the SLA.                                                                  *
 *                                                                           *
 * All software distributed under the SLA is provided strictly on an "AS     *
 * IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,       *
 * AND LICENSOR HEREBY DISCLAIMS ALL SUCH WARRANTIES, INCLUDING WITHOUT      *
 * LIMITATION, ANY WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR   *
 * PURPOSE, QUIET ENJOYMENT, OR NON-INFRINGEMENT. See the SLA for specific   *
 * language governing rights and limitations under the SLA.                  *
 *                                                                           *
 * The complete license agreement can be found here:                         *
 * http://unifiedautomation.com/License/SLA/2.7/                             *
 *                                                                           *
 * Project: Unified Automation OPC UA ANSI C Communication Stack             *
 *                                                                           *
 * This software is based in part on the ANSI C Stack of the OPC Foundation. *
 * Initial version of the ANSI C Stack was founded and copyrighted by OPC    *
 * Foundation, Inc.                                                          *
 * Copyright (C) 2008, 2014 OPC Foundation, Inc., All Rights Reserved.       *
 *****************************************************************************/

#include <opcua_builtintypes.h>
#include <opcua_stream.h>
#include <opcua_messagecontext.h>
#include <opcua_encoder.h>
#include <opcua_decoder.h>

#ifndef _OpcUa_BinaryEncoder_H_
#define _OpcUa_BinaryEncoder_H_ 1

OPCUA_BEGIN_EXTERN_C

/** 
  @brief Used to create an instance of a binary encoder.
 
  @param ppEncoder [out] The encoder.
*/
OPCUA_EXPORT OpcUa_StatusCode OpcUa_BinaryEncoder_Create(
    OpcUa_Encoder**       ppEncoder);


/** 
  @brief Used to create an instance of a binary decoder.
 
  @param ppDecoder [out] The decoder.
*/
OPCUA_EXPORT OpcUa_StatusCode OpcUa_BinaryDecoder_Create(
    OpcUa_Decoder** ppDecoder);

/** 
  @brief Writes a Boolean value.
 
  @param bValue [in] The value to encode.
  @param pOstrm [in] The stream.
*/
OPCUA_EXPORT OpcUa_StatusCode OpcUa_Boolean_BinaryEncode(
    OpcUa_Boolean       bValue,
    OpcUa_OutputStream* pOstrm);

/** 
  @brief Reads a Boolean value.
 
  @param pValue [out] The decoded value.
  @param pIstrm [in]  The stream.
*/
OPCUA_EXPORT OpcUa_StatusCode OpcUa_Boolean_BinaryDecode(
    OpcUa_Boolean*     pValue,
    OpcUa_InputStream* pIstrm);

/** 
  @brief Writes a SByte value.
 
  @param nValue [in] The value to encode.
  @param pOstrm [in] The stream.
*/
OPCUA_EXPORT OpcUa_StatusCode OpcUa_SByte_BinaryEncode(
    OpcUa_SByte         nValue,
    OpcUa_OutputStream* pOstrm);

/** 
  @brief Reads a SByte value.
 
  @param pValue [out] The decoded value.
  @param pIstrm [in]  The stream.
*/
OPCUA_EXPORT OpcUa_StatusCode OpcUa_SByte_BinaryDecode(
    OpcUa_SByte*       pValue,
    OpcUa_InputStream* pIstrm);

/** 
  @brief Writes a Byte value.
 
  @param nValue [in] The value to encode.
  @param pOstrm [in] The stream.
*/
OPCUA_EXPORT OpcUa_StatusCode OpcUa_Byte_BinaryEncode(
    OpcUa_Byte          nValue,
    OpcUa_OutputStream* pOstrm);
/** 
  @brief Reads a Byte value.
 
  @param pValue [out] The decoded value.
  @param pIstrm [in]  The stream.
*/
OPCUA_EXPORT OpcUa_StatusCode OpcUa_Byte_BinaryDecode(
    OpcUa_Byte*        pValue,
    OpcUa_InputStream* pIstrm);

/** 
  @brief Writes a Int16 value.
 
  @param nValue [in] The value to encode.
  @param pOstrm [in] The stream.
*/
OPCUA_EXPORT OpcUa_StatusCode OpcUa_Int16_BinaryEncode(
    OpcUa_Int16         nValue,
    OpcUa_OutputStream* pOstrm);
/** 
  @brief Reads a Int16 value.
 
  @param pValue [out] The decoded value.
  @param pIstrm [in]  The stream.
*/
OPCUA_EXPORT OpcUa_StatusCode OpcUa_Int16_BinaryDecode(
    OpcUa_Int16*       pValue,
    OpcUa_InputStream* pIstrm);

/** 
  @brief Writes a UInt16 value.
 
  @param nValue [in] The value to encode.
  @param pOstrm [in] The stream.
*/
OPCUA_EXPORT OpcUa_StatusCode OpcUa_UInt16_BinaryEncode(
    OpcUa_UInt16        nValue,
    OpcUa_OutputStream* pOstrm);

/** 
  @brief Reads a UInt16 value.
 
  @param pValue [out] The decoded value.
  @param pIstrm [in]  The stream.
*/
OPCUA_EXPORT OpcUa_StatusCode OpcUa_UInt16_BinaryDecode(
    OpcUa_UInt16*      pValue,
    OpcUa_InputStream* pIstrm);
/** 
  @brief Writes a Int32 value.
 
  @param nValue [in] The value to encode.
  @param pOstrm [in] The stream.
*/
OPCUA_EXPORT OpcUa_StatusCode OpcUa_Int32_BinaryEncode(
    OpcUa_Int32         nValue,
    OpcUa_OutputStream* pOstrm);

/** 
  @brief Reads a Int32 value.
 
  @param pValue [out] The decoded value.
  @param pIstrm [in]  The stream.
*/
OPCUA_EXPORT OpcUa_StatusCode OpcUa_Int32_BinaryDecode(
    OpcUa_Int32*       pValue,
    OpcUa_InputStream* pIstrm);

/** 
  @brief Writes a UInt32 value.
 
  @param nValue [in] The value to encode.
  @param pOstrm [in] The stream.
*/
OPCUA_EXPORT OpcUa_StatusCode OpcUa_UInt32_BinaryEncode(
    OpcUa_UInt32        nValue,
    OpcUa_OutputStream* pOstrm);

/** 
  @brief Reads a UInt32 value.
 
  @param pValue [out] The decoded value.
  @param pIstrm [in]  The stream.
*/
OPCUA_EXPORT OpcUa_StatusCode OpcUa_UInt32_BinaryDecode(
    OpcUa_UInt32*      pValue,
    OpcUa_InputStream* pIstrm);

/** 
  @brief Writes a Int64 value.
 
  @param nValue [in] The value to encode.
  @param pOstrm [in] The stream.
*/
OPCUA_EXPORT OpcUa_StatusCode OpcUa_Int64_BinaryEncode(
    OpcUa_Int64         nValue,
    OpcUa_OutputStream* pOstrm);

/** 
  @brief Reads a Int64 value.
 
  @param pValue [out] The decoded value.
  @param pIstrm [in]  The stream.
*/
OPCUA_EXPORT OpcUa_StatusCode OpcUa_Int64_BinaryDecode(
    OpcUa_Int64*       pValue,
    OpcUa_InputStream* pIstrm);

/** 
  @brief Writes a UInt64 value.
 
  @param nValue [in] The value to encode.
  @param pOstrm [in] The stream.
*/
OPCUA_EXPORT OpcUa_StatusCode OpcUa_UInt64_BinaryEncode(
    OpcUa_UInt64        nValue,
    OpcUa_OutputStream* pOstrm);

/** 
  @brief Reads a UInt64 value.
 
  @param pValue [out] The decoded value.
  @param pIstrm [in]  The stream.
*/
OPCUA_EXPORT OpcUa_StatusCode OpcUa_UInt64_BinaryDecode(
    OpcUa_UInt64*      pValue,
    OpcUa_InputStream* pIstrm);

/** 
  @brief Writes a Float value.
 
  @param nValue [in] The value to encode.
  @param pOstrm [in] The stream.
*/
OPCUA_EXPORT OpcUa_StatusCode OpcUa_Float_BinaryEncode(
    OpcUa_Float         nValue,
    OpcUa_OutputStream* pOstrm);

/** 
  @brief Reads a Float value.
 
  @param pValue [out] The decoded value.
  @param pIstrm [in]  The stream.
*/
OPCUA_EXPORT OpcUa_StatusCode OpcUa_Float_BinaryDecode(
    OpcUa_Float*       pValue,
    OpcUa_InputStream* pIstrm);

/** 
  @brief Writes a Double value.
 
  @param nValue [in] The value to encode.
  @param pOstrm [in] The stream.
*/
OPCUA_EXPORT OpcUa_StatusCode OpcUa_Double_BinaryEncode(
    OpcUa_Double        nValue,
    OpcUa_OutputStream* pOstrm);

/** 
  @brief Reads a Double value.
 
  @param pValue [out] The decoded value.
  @param pIstrm [in]  The stream.
*/
OPCUA_EXPORT OpcUa_StatusCode OpcUa_Double_BinaryDecode(
    OpcUa_Double*      pValue,
    OpcUa_InputStream* pIstrm);

/** 
  @brief Writes a String value.
 
  @param pValue [in] The value to encode.
  @param pOstrm [in] The stream.
*/
OPCUA_EXPORT OpcUa_StatusCode OpcUa_String_BinaryEncode(
    OpcUa_String*       pValue,
    OpcUa_OutputStream* pOstrm);

/** 
  @brief Reads a String value.
 
  @param pValue     [out] The decoded value.
  @param nMaxLength [in]  The maximum length for the decoded string (0 means no limit).
  @param pIstrm     [in]  The stream.
*/
OPCUA_EXPORT OpcUa_StatusCode OpcUa_String_BinaryDecode(
    OpcUa_String*      pValue,
    OpcUa_UInt32       nMaxLength,
    OpcUa_InputStream* pIstrm);

/** 
  @brief Writes a DateTime value.
 
  @param pValue [in] The value to encode.
  @param pOstrm [in] The stream.
*/
OPCUA_EXPORT OpcUa_StatusCode OpcUa_DateTime_BinaryEncode(
    OpcUa_DateTime*     pValue,
    OpcUa_OutputStream* pOstrm); 

/** 
  @brief Reads a DateTime value.
 
  @param pValue [out] The decoded value.
  @param pIstrm [in]  The stream.
*/
OPCUA_EXPORT OpcUa_StatusCode OpcUa_DateTime_BinaryDecode(
    OpcUa_DateTime*    pValue,
    OpcUa_InputStream* pIstrm);

/** 
  @brief Writes a Guid value.
 
  @param pValue [in] The value to encode.
  @param pOstrm [in] The stream.
*/
OPCUA_EXPORT OpcUa_StatusCode OpcUa_Guid_BinaryEncode(
    OpcUa_Guid*         pValue,
    OpcUa_OutputStream* pOstrm);

/** 
  @brief Reads a Guid value.
 
  @param pValue [out] The decoded value.
  @param pIstrm [in]  The stream.
*/
OPCUA_EXPORT OpcUa_StatusCode OpcUa_Guid_BinaryDecode(
    OpcUa_Guid*        pValue,
    OpcUa_InputStream* pIstrm);

/** 
  @brief Writes a ByteString value.
 
  @param pValue [in] The value to encode.
  @param pOstrm [in] The stream.
*/
OPCUA_EXPORT OpcUa_StatusCode OpcUa_ByteString_BinaryEncode(
    OpcUa_ByteString*   pValue,
    OpcUa_OutputStream* pOstrm);

/** 
  @brief Reads a ByteString value.
 
  @param pValue     [out] The decoded value.
  @param nMaxLength [in]  The maximum length for the decoded byte string (0 means no limit).
  @param pIstrm     [in]  The stream.
*/
OPCUA_EXPORT OpcUa_StatusCode OpcUa_ByteString_BinaryDecode(
    OpcUa_ByteString*  pValue,
    OpcUa_UInt32       nMaxLength,
    OpcUa_InputStream* pIstrm);

/** 
  @brief Writes a Variant value.
 
  @param pValue         [in] The value to encode.
  @param pOstrm         [in] The stream.
  @param pNamespaceUris [in] Namespace table for extension objects.
*/
OPCUA_EXPORT OpcUa_StatusCode OpcUa_Variant_BinaryEncode(
    OpcUa_Variant*      a_pValue,
    OpcUa_OutputStream* a_pOutStream,
    OpcUa_StringTable*  a_pNamespaceUris);

/** 
  @brief Reads a Variant value.
 
  @param pValue         [out] The decoded value.
  @param pIstrm         [in]  The stream.
  @param pNamespaceUris [in]  Namespace table for extension objects.
*/
OPCUA_EXPORT OpcUa_StatusCode OpcUa_Variant_BinaryDecode(
    OpcUa_Variant*     pValue,
    OpcUa_InputStream* pIstrm,
    OpcUa_StringTable* pNamespaceUris);

OPCUA_END_EXTERN_C

#endif /* _OpcUa_BinaryEncoder_H_ */
