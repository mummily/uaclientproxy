/******************************************************************************
** opcua_roletype.h
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

#ifndef __OPCUA_ROLETYPE_H__
#define __OPCUA_ROLETYPE_H__

#include "opcua_roletypebase.h"

// Namespace for the UA information model http://opcfoundation.org/UA/
namespace OpcUa {

/** @brief Class implementing the UaObject interface for the RoleType.
 *
 * OPC UA Objects are used to represent systems, system components, real-world objects and software
 * objects. They have the NodeClass @ref L3UaNodeClassObject. The detailed description of Objects and their attributes
 * can be found in the general description of the @ref L3UaNodeClassObject node class.
 *
 *  **Variable members of the RoleType:**
 *
 *  Browse Name         | DataType                | TypeDefinition | Modelling Rule | See Also
 *  --------------------|-------------------------|----------------|----------------|---------------------------------------------------------------------------------------------------------------------------------------
 *  Applications        | String                  | PropertyType   | Optional       | \ref RoleTypeBase::getApplications "getApplications", \ref RoleTypeBase::setApplications "setApplications"
 *  ApplicationsExclude | Boolean                 | PropertyType   | Optional       | \ref RoleTypeBase::getApplicationsExclude "getApplicationsExclude", \ref RoleTypeBase::setApplicationsExclude "setApplicationsExclude"
 *  Endpoints           | EndpointType            | PropertyType   | Optional       | \ref RoleTypeBase::getEndpoints "getEndpoints", \ref RoleTypeBase::setEndpoints "setEndpoints"
 *  EndpointsExclude    | Boolean                 | PropertyType   | Optional       | \ref RoleTypeBase::getEndpointsExclude "getEndpointsExclude", \ref RoleTypeBase::setEndpointsExclude "setEndpointsExclude"
 *  Identities          | IdentityMappingRuleType | PropertyType   | Mandatory      | \ref RoleTypeBase::getIdentities "getIdentities", \ref RoleTypeBase::setIdentities "setIdentities"
 *
 *  **Method members of the RoleType:**
 *
 *  Browse Name            | Modelling Rule
 *  -----------------------|---------------
 *  \ref AddApplication    | Optional
 *  \ref AddEndpoint       | Optional
 *  \ref AddIdentity       | Optional
 *  \ref RemoveApplication | Optional
 *  \ref RemoveEndpoint    | Optional
 *  \ref RemoveIdentity    | Optional
 *
 */
class SERVER_CORE_EXPORT RoleType:
    public RoleTypeBase
{
    UA_DISABLE_COPY(RoleType);
protected:
    // destruction
    virtual ~RoleType();
public:
    // construction
    RoleType(const UaNodeId& nodeId, UaObject* pInstanceDeclarationObject, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    RoleType(const UaNodeId& nodeId, const UaString& name, OpcUa_UInt16 browseNameNameSpaceIndex, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    RoleType(
        UaBase::Object*    pBaseNode,
        XmlUaNodeFactoryManager*   pFactory,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);
    static void createTypes();
    static void clearStaticMembers();

    // UaRoleType method AddApplication
    virtual UaStatus AddApplication(
        const ServiceContext& serviceContext,
        const UaString& RuleToAdd);
    // UaRoleType method AddEndpoint
    virtual UaStatus AddEndpoint(
        const ServiceContext& serviceContext,
        const UaEndpointType& RuleToAdd);
    // UaRoleType method AddIdentity
    virtual UaStatus AddIdentity(
        const ServiceContext& serviceContext,
        const UaIdentityMappingRuleType& RuleToAdd);
    // UaRoleType method RemoveApplication
    virtual UaStatus RemoveApplication(
        const ServiceContext& serviceContext,
        const UaString& RuleToRemove);
    // UaRoleType method RemoveEndpoint
    virtual UaStatus RemoveEndpoint(
        const ServiceContext& serviceContext,
        const UaEndpointType& RuleToRemove);
    // UaRoleType method RemoveIdentity
    virtual UaStatus RemoveIdentity(
        const ServiceContext& serviceContext,
        const UaIdentityMappingRuleType& RuleToRemove);

    void createOptionalComponents();
    void setAccessRestrictions();

protected:

private:
};

} // End namespace for the UA information model http://opcfoundation.org/UA/

#endif // #ifndef __OPCUAROLETYPE_H__

