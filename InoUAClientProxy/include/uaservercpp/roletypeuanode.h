/******************************************************************************
** roletypeuanode.h
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
** Project: C++ OPC Server SDK core module
**
** Description: OPC server core module access info for user authorisation
**
******************************************************************************/
#ifndef ROLETYPEUANODE_H
#define ROLETYPEUANODE_H

#include "roletypeoperations.h"
#include "opcua_roletype.h"


/** @brief Class for the user access flags of a node in the address space.
 Toolkit implementation to support 2 roles and a default e.g. role1, role2, others.
 */
class SERVER_CORE_EXPORT RoleTypeUaNode : public RoleTypeOperations
{
    UA_DISABLE_COPY(RoleTypeUaNode);
protected:
    // destruction
    virtual ~RoleTypeUaNode();
public:
    // construction
    RoleTypeUaNode(const UaNodeId& nodeId, UaObject* pInstanceDeclarationObject, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    RoleTypeUaNode(const UaNodeId& nodeId, const UaString& name, OpcUa_UInt16 browseNameNameSpaceIndex, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    RoleTypeUaNode(UaBase::Object* pBaseNode, XmlUaNodeFactoryManager* pFactory, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);

    // Interface RoleTypeOperations
    virtual UaNodeId getNodeId() const;
    virtual OpcUa_UInt32 getRoleId() const;
    virtual void setRoleId(OpcUa_UInt32 roleId);
    virtual UaQualifiedName getBrowseName();
    virtual bool grantAccess(const Session* pSession, const UaIdentityMappingRuleType& identity) const;
    virtual UaStatus addIdentity(const UaIdentityMappingRuleType& rule);
    virtual UaStatus removeIdentity(const UaIdentityMappingRuleType& rule);
    virtual UaStatus addApplication(const UaString&  applicationUri);
    virtual UaStatus removeApplication(const UaString& applicationUri);
    virtual UaStatus addEndpoint(const UaEndpointType& endpoint);
    virtual UaStatus removeEndpoint(const UaEndpointType& endpoint);

    // Methods for RoleTypeUaNode
    virtual OpcUa::BaseObjectType* getBaseObject();

protected:
    OpcUa_UInt32 m_RoleId;

private:
    OpcUa::RoleType* m_pRoleType;
    UaMutexRefCounted* m_pSharedMutex;
};

#endif // ROLETYPEUANODE_H
