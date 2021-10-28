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

#ifndef _OpcUa_P_PKI_H_
#define _OpcUa_P_PKI_H_ 1

OPCUA_BEGIN_EXTERN_C

#define OPCUA_P_CERTIFICATESTORECONFIGURATION_DATA_SIZE 0

#if defined(OPCUA_SUPPORT_PKI_OPENSSL) && OPCUA_SUPPORT_PKI_OPENSSL
/**
  @brief The PK infrastructure systems supported by the platform layer.
*/
#define OPCUA_P_PKI_TYPE_OPENSSL            "OpenSSL"
/**
  @brief The OpenSSL PKI specific store flags.
*/
#define OPCUA_P_PKI_OPENSSL_CHECK_REVOCATION_STATUS     1
#define OPCUA_P_PKI_OPENSSL_SET_DEFAULT_PATHS           2
#define OPCUA_P_PKI_OPENSSL_CERT_PATH_IS_HASH_DIRECTORY 4
#define OPCUA_P_PKI_OPENSSL_CRL_PATH_IS_HASH_DIRECTORY  8
#define OPCUA_P_PKI_OPENSSL_CRL_PATH_IS_MULTI_CRL_FILE  16
#endif /* OPCUA_SUPPORT_PKI_OPENSSL */

#if defined(OPCUA_SUPPORT_PKI_WIN32) && OPCUA_SUPPORT_PKI_WIN32
#define OPCUA_P_PKI_TYPE_WIN32              "WIN32"
/**
  @brief The WIN32 PKI specific store flags.
*/
#define OPCUA_P_PKI_WIN32_STORE_USER                    1
#define OPCUA_P_PKI_WIN32_STORE_MACHINE                 2
#define OPCUA_P_PKI_WIN32_STORE_SERVICES                4
#define OPCUA_P_PKI_WIN32_STORE_CHECK_REVOCATION_STATUS 8
#endif /* OPCUA_SUPPORT_PKI_WIN32 */

/**
  @brief The certificate und key format enumeration.
*/
typedef enum _OpcUa_P_Crypto_Encoding
{
    OpcUa_Crypto_Encoding_Invalid   = 0,
    OpcUa_Crypto_Encoding_DER       = 1,
    OpcUa_Crypto_Encoding_PEM       = 2,
    OpcUa_Crypto_Encoding_PKCS12    = 3
}
OpcUa_P_Crypto_Encoding;

/**
  @brief Loads a X.509 certificate from the specified file.
  */
OpcUa_StatusCode OpcUa_P_OpenSSL_X509_LoadFromFile(
    OpcUa_StringA               fileName,
    OpcUa_P_Crypto_Encoding     fileFormat,
    OpcUa_StringA               sPassword,      /* optional: just for OpcUa_PKCS12 */
    OpcUa_ByteString*           pCertificate);

/**
  @brief Loads a RSA private key from the specified file.
  */
OpcUa_StatusCode OpcUa_P_OpenSSL_RSA_LoadPrivateKey(
    const OpcUa_Void*       loadHandle,
    OpcUa_P_Crypto_Encoding fileFormat,
    const OpcUa_ByteString* password,
    OpcUa_Key*              privateKey);

OpcUa_StatusCode OpcUa_P_OpenSSL_RSA_SavePrivateKey(
    const OpcUa_Void*       saveHandle,
    OpcUa_P_Crypto_Encoding fileFormat,
    const OpcUa_ByteString* password,
    const OpcUa_Key*        privateKey);

/**
  @brief Get native PKI system information about current certificate error.
  */
OPCUA_IMEXPORT OpcUa_StatusCode OpcUa_P_OpenSSL_VerifyContext_GetCurrentErrorInformation(
                    OpcUa_Void*         a_pvVerifyContext,
                    OpcUa_Int32*        a_piNativeError,
                    const OpcUa_CharA** a_psErrorMessage);

OPCUA_END_EXTERN_C

#endif
