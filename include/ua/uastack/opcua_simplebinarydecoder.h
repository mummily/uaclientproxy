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
*****************************************************************************/
#ifndef OPCUA_SIMPLEBINARYDECODER_H
#define OPCUA_SIMPLEBINARYDECODER_H

#include <opcua_proxystub.h>
#include <opcua_encoder.h>
#include <opcua_decoder.h>

typedef struct _OpcUa_SimpleBinaryDecoder
{
    OpcUa_InputStream *pInputStream;
    OpcUa_Decoder *pDecoder;
    OpcUa_MessageContext cContext;
    OpcUa_Handle hDecodeContext;
} OpcUa_SimpleBinaryDecoder;

OpcUa_StatusCode OpcUa_SimpleBinaryDecoder_Initialize(OpcUa_SimpleBinaryDecoder *a_pDecoder);
OpcUa_StatusCode OpcUa_SimpleBinaryDecoder_Attach(OpcUa_SimpleBinaryDecoder *a_pDecoder,
                                          OpcUa_Byte *a_pBuffer,
                                          OpcUa_UInt32 a_bufferSize,
                                          OpcUa_UInt32 a_position);
OpcUa_StatusCode OpcUa_SimpleBinaryDecoder_Open(OpcUa_SimpleBinaryDecoder *a_pDecoder);
OpcUa_StatusCode OpcUa_SimpleBinaryDecoder_Close(OpcUa_SimpleBinaryDecoder *a_pDecoder);
OpcUa_StatusCode OpcUa_SimpleBinaryDecoder_Detach(OpcUa_SimpleBinaryDecoder *a_pDecoder,
                                          OpcUa_Byte **a_ppData,
                                          OpcUa_Int32 *a_pLength);
OpcUa_StatusCode OpcUa_SimpleBinaryDecoder_Clear(OpcUa_SimpleBinaryDecoder *a_pDecoder);

OpcUa_StatusCode OpcUa_SimpleBinaryDecoder_ReadBoolean(OpcUa_SimpleBinaryDecoder *a_pDecoder, OpcUa_Boolean *pValue);
OpcUa_StatusCode OpcUa_SimpleBinaryDecoder_ReadSByte(OpcUa_SimpleBinaryDecoder *a_pDecoder, OpcUa_SByte *pValue);
OpcUa_StatusCode OpcUa_SimpleBinaryDecoder_ReadByte(OpcUa_SimpleBinaryDecoder *a_pDecoder, OpcUa_Byte *pValue);
OpcUa_StatusCode OpcUa_SimpleBinaryDecoder_ReadInt16(OpcUa_SimpleBinaryDecoder *a_pDecoder, OpcUa_Int16 *pValue);
OpcUa_StatusCode OpcUa_SimpleBinaryDecoder_ReadUInt16(OpcUa_SimpleBinaryDecoder *a_pDecoder, OpcUa_UInt16 *pValue);
OpcUa_StatusCode OpcUa_SimpleBinaryDecoder_ReadInt32(OpcUa_SimpleBinaryDecoder *a_pDecoder, OpcUa_Int32 *pValue);
OpcUa_StatusCode OpcUa_SimpleBinaryDecoder_ReadUInt32(OpcUa_SimpleBinaryDecoder *a_pDecoder, OpcUa_UInt32 *pValue);
OpcUa_StatusCode OpcUa_SimpleBinaryDecoder_ReadInt64(OpcUa_SimpleBinaryDecoder *a_pDecoder, OpcUa_Int64 *pValue);
OpcUa_StatusCode OpcUa_SimpleBinaryDecoder_ReadUInt64(OpcUa_SimpleBinaryDecoder *a_pDecoder, OpcUa_UInt64 *pValue);
OpcUa_StatusCode OpcUa_SimpleBinaryDecoder_ReadFloat(OpcUa_SimpleBinaryDecoder *a_pDecoder, OpcUa_Float *pValue);
OpcUa_StatusCode OpcUa_SimpleBinaryDecoder_ReadDouble(OpcUa_SimpleBinaryDecoder *a_pDecoder, OpcUa_Double *pValue);

OpcUa_StatusCode OpcUa_SimpleBinaryDecoder_ReadString(OpcUa_SimpleBinaryDecoder *a_pDecoder, OpcUa_String *pValue);
OpcUa_StatusCode OpcUa_SimpleBinaryDecoder_ReadDateTime(OpcUa_SimpleBinaryDecoder *a_pDecoder, OpcUa_DateTime *pValue);
OpcUa_StatusCode OpcUa_SimpleBinaryDecoder_ReadGuid(OpcUa_SimpleBinaryDecoder *a_pDecoder, OpcUa_Guid *pValue);
OpcUa_StatusCode OpcUa_SimpleBinaryDecoder_ReadByteString(OpcUa_SimpleBinaryDecoder *a_pDecoder, OpcUa_ByteString *pValue);
OpcUa_StatusCode OpcUa_SimpleBinaryDecoder_ReadXmlElement(OpcUa_SimpleBinaryDecoder *a_pDecoder, OpcUa_XmlElement *pValue);
OpcUa_StatusCode OpcUa_SimpleBinaryDecoder_ReadNodeId(OpcUa_SimpleBinaryDecoder *a_pDecoder, OpcUa_NodeId *pValue);
OpcUa_StatusCode OpcUa_SimpleBinaryDecoder_ReadExpandedNodeId(OpcUa_SimpleBinaryDecoder *a_pDecoder, OpcUa_ExpandedNodeId *pValue);
OpcUa_StatusCode OpcUa_SimpleBinaryDecoder_ReadStatusCode(OpcUa_SimpleBinaryDecoder *a_pDecoder, OpcUa_StatusCode *pValue);
OpcUa_StatusCode OpcUa_SimpleBinaryDecoder_ReadQualifiedName(OpcUa_SimpleBinaryDecoder *a_pDecoder, OpcUa_QualifiedName *pValue);
OpcUa_StatusCode OpcUa_SimpleBinaryDecoder_ReadLocalizedText(OpcUa_SimpleBinaryDecoder *a_pDecoder, OpcUa_LocalizedText *pValue);
OpcUa_StatusCode OpcUa_SimpleBinaryDecoder_ReadExtensionObject(OpcUa_SimpleBinaryDecoder *a_pDecoder, OpcUa_ExtensionObject *pValue);
OpcUa_StatusCode OpcUa_SimpleBinaryDecoder_ReadDataValue(OpcUa_SimpleBinaryDecoder *a_pDecoder, OpcUa_DataValue *pValue);
OpcUa_StatusCode OpcUa_SimpleBinaryDecoder_ReadVariant(OpcUa_SimpleBinaryDecoder *a_pDecoder, OpcUa_Variant *pValue);
OpcUa_StatusCode OpcUa_SimpleBinaryDecoder_ReadDiagnosticInfo(OpcUa_SimpleBinaryDecoder *a_pDecoder, OpcUa_DiagnosticInfo *pValue);

#endif /* OPCUA_SIMPLEBINARYDECODER_H */
