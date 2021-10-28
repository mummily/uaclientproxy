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

#ifndef _OpcUa_MemoryStream_H_
#define _OpcUa_MemoryStream_H_ 1
#if OPCUA_HAVE_MEMORYSTREAM
#include <opcua_stream.h>

OPCUA_BEGIN_EXTERN_C
 
/** 
  @brief Allocates a new readable memory stream.
 
  The caller must ensure the buffer is valid memory until Close is called.

  @param buffer     [in]  The buffer which is the source for the stream.
  @param bufferSize [in]  The length of the buffer.
  @param freeBuffer [in]  Should the buffer be freed (OpcUa_Free) when the stream is deleted?
  @param istrm      [out] The input stream.
*/
OPCUA_EXPORT OpcUa_StatusCode OpcUa_MemoryStream_CreateReadable(
    const OpcUa_Byte*   buffer,
    OpcUa_UInt32        bufferSize,
    OpcUa_Boolean       freeBuffer,
    OpcUa_InputStream** istrm);

/** 
  @brief Allocates a new writable memory stream.
 
  @param blockSize  [in]  The size of the block to allocate when new memory is required.
  @param maxSize    [in]  The maximum buffer size (0 means no limit).
  @param ostrm      [out] The output stream.
*/
OPCUA_EXPORT OpcUa_StatusCode OpcUa_MemoryStream_CreateWriteable(
    OpcUa_UInt32         blockSize,
    OpcUa_UInt32         maxSize,
    OpcUa_OutputStream** ostrm);

/** 
  @brief Returns the internal buffer for a writable stream.
 
  This function cannot be called until the stream is closed.

  The memory returned by this function is owned by the stream and will be
  de-allocated when OpcUa_MemoryStream_Delete is called.

  @param ostrm      [in]  The output stream.
  @param buffer     [out] The buffer which contains the data written to the stream.
  @param bufferSize [out] The amount of valid data in the buffer.
*/
OPCUA_EXPORT OpcUa_StatusCode OpcUa_MemoryStream_GetBuffer(
    OpcUa_OutputStream* ostrm,
    OpcUa_Byte**        buffer,
    OpcUa_UInt32*       bufferSize);

/** 
  @brief Returns the internal buffer for a writable stream.
 
  This function cannot be called until the stream is closed.

  The memory returned by this function is no longer owned by the stream and has
  to be freed manually. The stream is no longer usable.

  @param ostrm      [in]  The output stream.
  @param buffer     [out] The buffer which contains the data written to the stream.
  @param bufferSize [out] The amount of valid data in the buffer.
*/
OPCUA_EXPORT OpcUa_StatusCode OpcUa_MemoryStream_DetachBuffer(
    OpcUa_OutputStream* ostrm,
    OpcUa_Byte**        buffer,
    OpcUa_UInt32*       bufferSize);

/**
  @brief Adds user data to the stream which can be retrieve by calling OpcUa_MemoryStream_GetUserData.

  @param ostrm      [in]  The output stream.
  @param buffer     [out] The buffer which contains the data written to the stream.
  @param bufferSize [out] The amount of valid data in the buffer.
*/
OPCUA_EXPORT OpcUa_StatusCode OpcUa_MemoryStream_SetUserData(
    OpcUa_Stream*       strm,
    OpcUa_Void*         data);

/**
  @brief Retrieve user data set by OpcUa_MemoryStream_SetUserData.

  @param ostrm      [in]  The output stream.
  @param buffer     [out] The buffer which contains the data written to the stream.
  @param bufferSize [out] The amount of valid data in the buffer.
*/
OPCUA_EXPORT OpcUa_StatusCode OpcUa_MemoryStream_GetUserData(
    OpcUa_Stream*       strm,
    OpcUa_Void**        pdata);

OPCUA_END_EXTERN_C

#endif /* OPCUA_HAVE_MEMORYSTREAM */
#endif /* _OpcUa_MemoryStream_H_ */
