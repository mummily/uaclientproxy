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
#ifndef OPCUA_SIMPLEBINARYENCODER_H
#define OPCUA_SIMPLEBINARYENCODER_H

#include <opcua_proxystub.h>
#include <opcua_encoder.h>

typedef struct _OpcUa_SimpleBinaryEncoder
{
    OpcUa_OutputStream *pOutputStream;
    OpcUa_Encoder *pEncoder;
    OpcUa_MessageContext cContext;
    OpcUa_Handle hEncodeContext;
} OpcUa_SimpleBinaryEncoder;

OpcUa_StatusCode OpcUa_SimpleBinaryEncoder_Initialize(OpcUa_SimpleBinaryEncoder *a_pEncoder);
OpcUa_StatusCode OpcUa_SimpleBinaryEncoder_Attach(OpcUa_SimpleBinaryEncoder *a_pEncoder,
                                          OpcUa_Byte *a_pBuffer,
                                          OpcUa_UInt32 a_bufferSize,
                                          OpcUa_UInt32 a_position);
OpcUa_StatusCode OpcUa_SimpleBinaryEncoder_Open(OpcUa_SimpleBinaryEncoder *a_pEncoder);
OpcUa_StatusCode OpcUa_SimpleBinaryEncoder_Close(OpcUa_SimpleBinaryEncoder *a_pEncoder);
OpcUa_StatusCode OpcUa_SimpleBinaryEncoder_Detach(OpcUa_SimpleBinaryEncoder *a_pEncoder,
                                          OpcUa_Byte **a_ppData,
                                          OpcUa_Int32 *a_pLength);
OpcUa_StatusCode OpcUa_SimpleBinaryEncoder_Clear(OpcUa_SimpleBinaryEncoder *a_pEncoder);

OpcUa_StatusCode OpcUa_SimpleBinaryEncoder_WriteBoolean(OpcUa_SimpleBinaryEncoder *a_pEncoder, OpcUa_Boolean value);
OpcUa_StatusCode OpcUa_SimpleBinaryEncoder_WriteSByte(OpcUa_SimpleBinaryEncoder *a_pEncoder, OpcUa_SByte value);
OpcUa_StatusCode OpcUa_SimpleBinaryEncoder_WriteByte(OpcUa_SimpleBinaryEncoder *a_pEncoder, OpcUa_Byte value);
OpcUa_StatusCode OpcUa_SimpleBinaryEncoder_WriteInt16(OpcUa_SimpleBinaryEncoder *a_pEncoder, OpcUa_Int16 value);
OpcUa_StatusCode OpcUa_SimpleBinaryEncoder_WriteUInt16(OpcUa_SimpleBinaryEncoder *a_pEncoder, OpcUa_UInt16 value);
OpcUa_StatusCode OpcUa_SimpleBinaryEncoder_WriteInt32(OpcUa_SimpleBinaryEncoder *a_pEncoder, OpcUa_Int32 value);
OpcUa_StatusCode OpcUa_SimpleBinaryEncoder_WriteUInt32(OpcUa_SimpleBinaryEncoder *a_pEncoder, OpcUa_UInt32 value);
OpcUa_StatusCode OpcUa_SimpleBinaryEncoder_WriteInt64(OpcUa_SimpleBinaryEncoder *a_pEncoder, OpcUa_Int64 value);
OpcUa_StatusCode OpcUa_SimpleBinaryEncoder_WriteUInt64(OpcUa_SimpleBinaryEncoder *a_pEncoder, OpcUa_UInt64 value);
OpcUa_StatusCode OpcUa_SimpleBinaryEncoder_WriteFloat(OpcUa_SimpleBinaryEncoder *a_pEncoder, OpcUa_Float value);
OpcUa_StatusCode OpcUa_SimpleBinaryEncoder_WriteDouble(OpcUa_SimpleBinaryEncoder *a_pEncoder, OpcUa_Double value);

OpcUa_StatusCode OpcUa_SimpleBinaryEncoder_WriteString(OpcUa_SimpleBinaryEncoder *a_pEncoder, OpcUa_String *pValue);
OpcUa_StatusCode OpcUa_SimpleBinaryEncoder_WriteDateTime(OpcUa_SimpleBinaryEncoder *a_pEncoder, OpcUa_DateTime *pValue);
OpcUa_StatusCode OpcUa_SimpleBinaryEncoder_WriteGuid(OpcUa_SimpleBinaryEncoder *a_pEncoder, OpcUa_Guid *pValue);
OpcUa_StatusCode OpcUa_SimpleBinaryEncoder_WriteByteString(OpcUa_SimpleBinaryEncoder *a_pEncoder, OpcUa_ByteString *pValue);
OpcUa_StatusCode OpcUa_SimpleBinaryEncoder_WriteXmlElement(OpcUa_SimpleBinaryEncoder *a_pEncoder, OpcUa_XmlElement *pValue);
OpcUa_StatusCode OpcUa_SimpleBinaryEncoder_WriteNodeId(OpcUa_SimpleBinaryEncoder *a_pEncoder, OpcUa_NodeId *pValue);
OpcUa_StatusCode OpcUa_SimpleBinaryEncoder_WriteExpandedNodeId(OpcUa_SimpleBinaryEncoder *a_pEncoder, OpcUa_ExpandedNodeId *pValue);
OpcUa_StatusCode OpcUa_SimpleBinaryEncoder_WriteStatusCode(OpcUa_SimpleBinaryEncoder *a_pEncoder, OpcUa_StatusCode *pValue);
OpcUa_StatusCode OpcUa_SimpleBinaryEncoder_WriteQualifiedName(OpcUa_SimpleBinaryEncoder *a_pEncoder, OpcUa_QualifiedName *pValue);
OpcUa_StatusCode OpcUa_SimpleBinaryEncoder_WriteLocalizedText(OpcUa_SimpleBinaryEncoder *a_pEncoder, OpcUa_LocalizedText *pValue);
OpcUa_StatusCode OpcUa_SimpleBinaryEncoder_WriteExtensionObject(OpcUa_SimpleBinaryEncoder *a_pEncoder, OpcUa_ExtensionObject *pValue);
OpcUa_StatusCode OpcUa_SimpleBinaryEncoder_WriteDataValue(OpcUa_SimpleBinaryEncoder *a_pEncoder, OpcUa_DataValue *pValue);
OpcUa_StatusCode OpcUa_SimpleBinaryEncoder_WriteVariant(OpcUa_SimpleBinaryEncoder *a_pEncoder, OpcUa_Variant *pValue);
OpcUa_StatusCode OpcUa_SimpleBinaryEncoder_WriteDiagnosticInfo(OpcUa_SimpleBinaryEncoder *a_pEncoder, OpcUa_DiagnosticInfo *pValue);

#endif /* OPCUA_SIMPLEBINARYENCODER_H */
