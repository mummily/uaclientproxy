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

#ifndef _OpcUa_P_Config_H_
#define _OpcUa_P_Config_H_ 1

/*============================================================================
 * platform layer version information
 *===========================================================================*/
/* helper to get build time through buildsystem */
#ifndef OPCUA_P_BUILDINFO_BUILD_TIMESTAMP
#if (defined(__DATE__) && defined(__TIME__))
#define OPCUA_P_TIMESTAMP __DATE__ " " __TIME__
#define OPCUA_P_BUILDINFO_BUILD_TIMESTAMP OPCUA_P_TIMESTAMP
#endif /* __DATE__ && __TIME__ */
#endif /* OPCUA_P_BUILDINFO_BUILD_TIMESTAMP */

/** @brief Name of the platform or operating system this platform layer was created for. */
#ifndef OPCUA_P_BUILDINFO_PLATFORMNAME
# define OPCUA_P_BUILDINFO_PLATFORMNAME             "Windows V6"
#endif /* OPCUA_P_BUILDINFO_PLATFORMNAME */

/** @brief The date and time when the source was last modified. */
#ifndef OPCUA_P_BUILDINFO_SOURCE_TIMESTAMP
# define OPCUA_P_BUILDINFO_SOURCE_TIMESTAMP         "2018-09-25 13:27:28"
#endif /* OPCUA_P_BUILDINFO_SOURCE_TIMESTAMP */

/** @brief The date and time when the binary is build. */
#ifndef OPCUA_P_BUILDINFO_BUILD_TIMESTAMP
# define OPCUA_P_BUILDINFO_BUILD_TIMESTAMP          "OPCUA_P_BUILDINFO_BUILD_TIMESTAMP not set"
#endif /* OPCUA_P_BUILDINFO_BUILD_TIMESTAMP */

/** @brief The name of the company which build the binary. */
#ifndef OPCUA_P_BUILDINFO_VENDOR_NAME
# define OPCUA_P_BUILDINFO_VENDOR_NAME              "Unified Automation GmbH"
#endif /* OPCUA_P_BUILDINFO_VENDOR_NAME */

/** @brief Additional information from the company, ie. internal revision number. */
#ifndef OPCUA_P_BUILDINFO_VENDOR_INFO
# define OPCUA_P_BUILDINFO_VENDOR_INFO              ""
#endif /* OPCUA_P_BUILDINFO_VENDOR_INFO */

/**********************************************************************************/
/*/  Security Configuration section.                                             /*/
/**********************************************************************************/
#ifndef OPCUA_SUPPORT_SECURITYPOLICY_NONE
# define OPCUA_SUPPORT_SECURITYPOLICY_NONE                  OPCUA_CONFIG_ON
#endif  /* OPCUA_SUPPORT_SECURITYPOLICY_NONE */

#ifndef OPCUA_SUPPORT_SECURITYPOLICY_BASIC128RSA15
# define OPCUA_SUPPORT_SECURITYPOLICY_BASIC128RSA15         OPCUA_CONFIG_ON
#endif  /* OPCUA_SUPPORT_SECURITYPOLICY_BASIC128RSA15 */

#ifndef OPCUA_SUPPORT_SECURITYPOLICY_BASIC256
# define OPCUA_SUPPORT_SECURITYPOLICY_BASIC256              OPCUA_CONFIG_ON
#endif /* OPCUA_SUPPORT_SECURITYPOLICY_BASIC256 */

#ifndef OPCUA_SUPPORT_SECURITYPOLICY_BASIC256SHA256
# define OPCUA_SUPPORT_SECURITYPOLICY_BASIC256SHA256        OPCUA_CONFIG_ON
#endif  /* OPCUA_SUPPORT_SECURITYPOLICY_BASIC256SHA256 */

#ifndef OPCUA_SUPPORT_SECURITYPOLICY_AES128SHA256RSAOAEP
# define OPCUA_SUPPORT_SECURITYPOLICY_AES128SHA256RSAOAEP OPCUA_CONFIG_ON
#endif  /* OPCUA_SUPPORT_SECURITYPOLICY_AES128SHA256RSAOAEP */

#ifndef OPCUA_SUPPORT_SECURITYPOLICY_AES256SHA256RSAPSS
# define OPCUA_SUPPORT_SECURITYPOLICY_AES256SHA256RSAPSS  OPCUA_CONFIG_ON
#endif  /* OPCUA_SUPPORT_SECURITYPOLICY_AES256SHA256RSAPSS */

#ifndef OPCUA_SUPPORT_PKI
# define OPCUA_SUPPORT_PKI                              OPCUA_CONFIG_ON
#endif  /* OPCUA_SUPPORT_PKI */

#ifndef OPCUA_HAVE_OPENSSL
# define OPCUA_HAVE_OPENSSL                             OPCUA_CONFIG_ON
#endif  /* OPCUA_HAVE_OPENSSL */

#if OPCUA_SUPPORT_PKI
# ifndef OPCUA_SUPPORT_PKI_OVERRIDE
#  define OPCUA_SUPPORT_PKI_OVERRIDE                    OPCUA_CONFIG_OFF
# endif /* OPCUA_SUPPORT_PKI_OVERRIDE */
# ifndef OPCUA_SUPPORT_PKI_OPENSSL
#  define OPCUA_SUPPORT_PKI_OPENSSL                     OPCUA_CONFIG_ON
# endif /* OPCUA_SUPPORT_PKI_OPENSSL */
# ifndef OPCUA_SUPPORT_PKI_WIN32
#  if !defined(_WIN32_WCE) && defined(_MSC_VER) && _MSC_VER >= 1400
#   define OPCUA_SUPPORT_PKI_WIN32                      OPCUA_CONFIG_OFF
#  else
#   define OPCUA_SUPPORT_PKI_WIN32                      OPCUA_CONFIG_OFF
#  endif
# endif /* OPCUA_SUPPORT_PKI_WIN32 */
#else /* OPCUA_SUPPORT_PKI */
# ifndef OPCUA_SUPPORT_PKI_OVERRIDE
#  define OPCUA_SUPPORT_PKI_OVERRIDE                    OPCUA_CONFIG_OFF
# endif /* OPCUA_SUPPORT_PKI_OVERRIDE */
# ifndef OPCUA_SUPPORT_PKI_OPENSSL
#  define OPCUA_SUPPORT_PKI_OPENSSL                     OPCUA_CONFIG_OFF
# endif /* OPCUA_SUPPORT_PKI_OPENSSL */
# ifndef OPCUA_SUPPORT_PKI_WIN32
#  define OPCUA_SUPPORT_PKI_WIN32                       OPCUA_CONFIG_OFF
# endif /* OPCUA_SUPPORT_PKI_WIN32 */
#endif /* OPCUA_SUPPORT_PKI */

#if OPCUA_SUPPORT_PKI_OPENSSL
#  ifndef OPCUA_P_OPENSSL_USE_RAND_SCREEN
/** @brief If true, screen content will be used to initialize the OpenSSL PRNG. */
#    define OPCUA_P_OPENSSL_USE_RAND_SCREEN             OPCUA_CONFIG_ON
#  endif /* OPCUA_P_OPENSSL_USE_RAND_SCREEN */
#endif /* OPCUA_SUPPORT_PKI_OPENSSL */

/**********************************************************************************/
/*/  General section.                                                            /*/
/**********************************************************************************/

/** @brief The maximum number of sockets supported by a socket manager. */
#ifndef OPCUA_P_SOCKETMANAGER_NUMBEROFSOCKETS
# define OPCUA_P_SOCKETMANAGER_NUMBEROFSOCKETS                  104
#endif /* OPCUA_P_SOCKETMANAGER_NUMBEROFSOCKETS */

/** @brief Toggle SSL support in the socket manager class. */
#ifndef OPCUA_P_SOCKETMANAGER_SUPPORT_SSL
# define OPCUA_P_SOCKETMANAGER_SUPPORT_SSL                      OPCUA_CONFIG_ON
#endif /* OPCUA_P_SOCKETMANAGER_SUPPORT_SSL */

/** @brief The number of timers available to the system. */
#ifndef OPCUA_P_TIMER_NO_OF_TIMERS
# define OPCUA_P_TIMER_NO_OF_TIMERS                             200
#endif

#endif /* _OpcUa_P_Config_H_ */
