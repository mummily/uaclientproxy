/******************************************************************************
** roletypeoperations.h
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
** Project: C++ OPC Server SDK information model for namespace http://opcfoundation.org/UA/
**
** Description: OPC Unified Architecture Software Development Kit.
**
******************************************************************************/
#ifndef ROLETYPEOPERATIONS_H
#define ROLETYPEOPERATIONS_H

#include "opcuatypes.h"
#include "uaidentitymappingruletype.h"
#include "uaendpointtype.h"
#include "referencecounter.h"

class UaUserIdentityToken;

/** @ingroup ServerCoreInterfaces
*  Interface to modify the configuration of a role. This includes to add and remove Identities, Applications, Endpoints.
*  It is not possible to create shallow copies of this Interface.
*/
class SERVER_CORE_EXPORT RoleTypeOperations : public ReferenceCounter
{
    UA_DISABLE_COPY(RoleTypeOperations);
protected:
    /** destruction */
    virtual ~RoleTypeOperations() {}
public:
    /** construction */
    RoleTypeOperations() {}

    /** Return the NodeId for this Role Instance.
    *  @return The NodeId
    */
    virtual UaNodeId getNodeId() const = 0;

    /** Return the RoleId for this Role Instance.
    *  @return The RoleId
    */
    virtual OpcUa_UInt32 getRoleId() const = 0;

    /** Set the RoleId for this Role Instance.
    *  @param roleId    the new roleId
    */
    virtual void setRoleId(OpcUa_UInt32 roleId) = 0;

    /** Return the BrowseName for this Role Instance.
    *  @return The RoleId
    */
    virtual UaQualifiedName getBrowseName() = 0;

    /** Check if any rule grants access and check that no rule excludes the context (Endpoint, Application, User)
    */
    virtual bool grantAccess(const Session* pSession, const UaIdentityMappingRuleType& identity) const = 0;

    virtual UaStatus addIdentity(const UaIdentityMappingRuleType& rule) = 0;

    virtual UaStatus removeIdentity(const UaIdentityMappingRuleType& rule) = 0;

    virtual UaStatus addApplication(const UaString&  applicationUri) = 0;

    virtual UaStatus removeApplication(const UaString& applicationUri) = 0;

    virtual UaStatus addEndpoint(const UaEndpointType& endpoint) = 0;

    virtual UaStatus removeEndpoint(const UaEndpointType& endpoint) = 0;

    // todo
    // add exclude flags
};
#endif // ROLETYPEOPERATIONS_H
