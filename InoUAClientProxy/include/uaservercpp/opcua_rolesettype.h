/******************************************************************************
** opcua_rolesettype.h
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

#ifndef __OPCUA_ROLESETTYPE_H__
#define __OPCUA_ROLESETTYPE_H__

#include "opcua_rolesettypebase.h"

// Namespace for the UA information model http://opcfoundation.org/UA/
namespace OpcUa {

/** @brief Class implementing the UaObject interface for the RoleSetType.
 *
 * OPC UA Objects are used to represent systems, system components, real-world objects and software
 * objects. They have the NodeClass @ref L3UaNodeClassObject. The detailed description of Objects and their attributes
 * can be found in the general description of the @ref L3UaNodeClassObject node class.
 *
 *  **Object members of the RoleSetType:**
 *
 *  Browse Name  | TypeDefinition | Modelling Rule      | See Also
 *  -------------|----------------|---------------------|---------
 *  \<RoleName\> | RoleType       | OptionalPlaceholder | &nbsp;
 *
 *  **Method members of the RoleSetType:**
 *
 *  Browse Name     | Modelling Rule
 *  ----------------|---------------
 *  \ref AddRole    | Mandatory
 *  \ref RemoveRole | Mandatory
 *
 */
class SERVER_CORE_EXPORT RoleSetType:
    public RoleSetTypeBase
{
    UA_DISABLE_COPY(RoleSetType);
protected:
    // destruction
    virtual ~RoleSetType();
public:
    enum WellKnownRoleIds
    {
        WellKnownRoleId_Anonymous = 1,
        WellKnownRoleId_AuthenticatedUser = 2,
        WellKnownRoleId_Observer = 3,
        WellKnownRoleId_Operator = 4,
        WellKnownRoleId_Engineer = 5,
        WellKnownRoleId_Supervisor = 6,
        WellKnownRoleId_ConfigureAdmin = 7,
        WellKnownRoleId_SecurityAdmin = 8,
        WellKnownRoleId_FirstId = 100   // We start with 100 for our internal roleIds
    };

    // construction
    RoleSetType(const UaNodeId& nodeId, UaObject* pInstanceDeclarationObject, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    RoleSetType(const UaNodeId& nodeId, const UaString& name, OpcUa_UInt16 browseNameNameSpaceIndex, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    RoleSetType(
        UaBase::Object*    pBaseNode,
        XmlUaNodeFactoryManager*   pFactory,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);
    static void createTypes();
    static void clearStaticMembers();

    // UaRoleSetType method AddRole
    virtual UaStatus AddRole(
        const ServiceContext& serviceContext,
        const UaString& RoleName,
        const UaString& NamespaceUri,
        UaNodeId& RoleNodeId);
    // UaRoleSetType method RemoveRole
    virtual UaStatus RemoveRole(
        const ServiceContext& serviceContext,
        const UaNodeId& RoleNodeId);

    void initialize();

    // add RoleTypeOperations to management - this method sets the roleId
    virtual UaStatus registerRole(RoleTypeOperations* pRoleTypeOperations, bool bSetRoleId = true);
    // remove RoleTypeOperations from management
    virtual UaStatus unregisterRole(RoleTypeOperations* pRoleTypeOperations);

    // get the NodeId for the Role defined by the internal Id
    UaNodeId getRoleNodeId(OpcUa_UInt32 roleId) const;
    // get the internal Id for Role defined by NodeId
    OpcUa_UInt32 getRoleId(const UaNodeId& roleNodeId) const;
    // assign roleIds to the SessionUserContext associated with this session
    UaStatus setRoleIds(const Session* pSession) const;

    // find role by roleId
    UaStatus getRoleByRoleId(
        const OpcUa_UInt32 roleId,
        RoleTypeOperations** ppRoleTypeOperations) const;

    // find role by NodeId
    UaStatus getRoleByNodeId(
        const UaNodeId& roleNodeId,
        RoleTypeOperations** ppRoleTypeOperations) const;

    // find role by name and uri
    UaStatus getRoleByName(
        const UaQualifiedName& browseName,
        RoleTypeOperations** ppRoleTypeOperations) const;

    static OpcUa_UInt32 getIdForWellKnownRole(OpcUa_UInt32 numericIdentifier);
    UaStatus createWellKnownRoles();
    void removeWellKnownRoles();

protected:

private:
    std::list<RoleTypeOperations*> m_lstRoleTypeOperations;
    OpcUa_UInt32 m_nextRoleId;
    static bool s_wellKnownRolesCreated;
};

} // End namespace for the UA information model http://opcfoundation.org/UA/

#endif // #ifndef __OPCUAROLESETTYPE_H__
