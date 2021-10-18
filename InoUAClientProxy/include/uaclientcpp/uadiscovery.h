/******************************************************************************
** uadiscovery.h
**
** Copyright (c) 2006-2018 Unified Automation GmbH. All rights reserved.
**
** Software License Agreement ("SLA") Version 2.7
**
** Unless explicitly acquired and licensed from Licensor under another
** license, the contents of this file are subject to the Software License
** Agreement ("SLA") Version 2.7, or subsequent versions
** as allowed by the SLA, and You may not copy or use this file in either
** source code or executable form, except in compliance with the terms and
** conditions of the SLA.
**
** All software distributed under the SLA is provided strictly on an
** "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
** AND LICENSOR HEREBY DISCLAIMS ALL SUCH WARRANTIES, INCLUDING WITHOUT
** LIMITATION, ANY WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
** PURPOSE, QUIET ENJOYMENT, OR NON-INFRINGEMENT. See the SLA for specific
** language governing rights and limitations under the SLA.
**
** The complete license agreement can be found here:
** http://unifiedautomation.com/License/SLA/2.7/
**
** Project: C++ OPC Client SDK
**
** Description: Interface for UA Discovery.
**
******************************************************************************/
#ifndef UACLIENTSDK_UADISCOVERY_H
#define UACLIENTSDK_UADISCOVERY_H

#include "uaclientsdk.h"
#include "uaserveronnetwork.h"

namespace UaClientSdk {

class UaSession;
class UaDiscoveryPrivate;

/*! \addtogroup UaClientLibrary
*  @{
*/

/** \brief Callback interface for the reverse Discovery functionality.
*/
class UACLIENT_EXPORT UaReverseDiscoveryCallback
{
public:
    virtual ~UaReverseDiscoveryCallback() {}

    /** Callback informing the discovery client about a reverse connect from a server
     *
     * The Endpoint URL can be used to call getEndpoints
     */
    virtual void receivedReverseConnect(
        const UaString& sServerUri,  //!< [in] The ServerUri of the server initiating a reverse connect
        const UaString& sEndpointUrl //!< [in] The endpoint URL of the server initiating a reverse connect
        ) = 0;
};

/** \brief The UaDiscovery class manages a UA Client side discovery functionality.

 Discovery is a two-step approach. In the first step, the available servers are discovered and in the second
 step the selected server is asked for its available Endpoints, describing combinations of protocols and security
 settings available to connect to the server.
*/
class UACLIENT_EXPORT UaDiscovery
{
    UA_DISABLE_COPY(UaDiscovery);
public:
    UaDiscovery();
    ~UaDiscovery();

    UaStatus findServers(
        const UaString&            sDiscoveryURL,
        UaApplicationDescriptions& applicationDescriptions);

    UaStatus findServers(
        ServiceSettings&           serviceSettings,
        const UaString&            sDiscoveryURL,
        ClientSecurityInfo&        clientSecurityInfo,
        UaApplicationDescriptions& applicationDescriptions);

    UaStatus findServers(
        ServiceSettings&           serviceSettings,
        const UaString&            sDiscoveryURL,
        ClientSecurityInfo&        clientSecurityInfo,
        const UaStringArray&       localIds,
        const UaStringArray&       serverUris,
        UaApplicationDescriptions& applicationDescriptions);

    UaStatus getEndpoints(
        const UaString&           sDiscoveryURL,
        UaEndpointDescriptions&   endpointDescriptions);

    UaStatus getEndpoints(
        ServiceSettings&          serviceSettings,
        const UaString&           sDiscoveryURL,
        ClientSecurityInfo&       clientSecurityInfo,
        UaEndpointDescriptions&   endpointDescriptions);

    UaStatus getEndpoints(
        ServiceSettings&          serviceSettings,
        const UaString&           sDiscoveryURL,
        ClientSecurityInfo&       clientSecurityInfo,
        const UaStringArray&      localIds,
        const UaStringArray&      transportProfileUris,
        UaEndpointDescriptions&   endpointDescriptions);

    UaStatus findServersOnNetwork(
        ServiceSettings&    serviceSettings,
        const UaString&      sDiscoveryURL,
        ClientSecurityInfo&  clientSecurityInfo,
        OpcUa_UInt32         startingRecordId,
        const UaStringArray& serverCapabilities,
        OpcUa_UInt32         maxRecordsToReturn,
        UaDateTime&          lastCounterResetTime,
        UaServerOnNetworks&  servers);

    UaStatus findServersOnNetwork(
        ServiceSettings&    serviceSettings,
        const UaString&      sDiscoveryURL,
        ClientSecurityInfo&  clientSecurityInfo,
        OpcUa_UInt32         startingRecordId,
        UaDateTime&          lastCounterResetTime,
        UaServerOnNetworks&  servers);

    UaStatus queryDirectory(
        ServiceSettings&     serviceSettings,
        const UaString&      sGdsURL,
        OpcUa_UInt32         startingRecordId,
        UaDateTime&          lastCounterResetTime,
        UaServerOnNetworks&  servers);

    UaStatus queryDirectory(
        ServiceSettings&     serviceSettings,
        UaSession*           pSession,
        OpcUa_UInt32         startingRecordId,
        UaDateTime&          lastCounterResetTime,
        UaServerOnNetworks&  servers);

    UaStatus queryDirectory(
        ServiceSettings&     serviceSettings,
        UaSession*           pSession,
        OpcUa_UInt32         startingRecordId,
        OpcUa_UInt32         maxRecordsToReturn,
        const UaString&      applicationName,
        const UaString&      applicationUri,
        const UaString&      productUri,
        const UaStringArray& serverCapabilities,
        UaDateTime&          lastCounterResetTime,
        UaServerOnNetworks&  servers);

    UaStatus queryDirectory(
        ServiceSettings&     serviceSettings,
        const UaString&      sGdsURL,
        SessionConnectInfo&  sessionConnectInfo,
        SessionSecurityInfo& sessionSecurityInfo,
        OpcUa_UInt32         startingRecordId,
        OpcUa_UInt32         maxRecordsToReturn,
        const UaString&      applicationName,
        const UaString&      applicationUri,
        const UaString&      productUri,
        const UaStringArray& serverCapabilities,
        UaDateTime&          lastCounterResetTime,
        UaServerOnNetworks&  servers);

    UaStatus startReverseDiscovery(
        const UaString& sClientEndpointUrl,
        UaReverseDiscoveryCallback* pReverseConnectCallback);
    UaStatus stopReverseDiscovery();
    UaString getClientEndpointUrl();
private:
    UaDiscoveryPrivate* d;
};
/*! @} */
}

#endif // UACLIENTSDK_UADISCOVERY_H
