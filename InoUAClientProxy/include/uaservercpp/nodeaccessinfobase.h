/******************************************************************************
** nodeaccessinfobase.h
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
#ifndef NODEACCESSINFOBASE_H
#define NODEACCESSINFOBASE_H

#include "nodeaccessinfo.h"

/** @brief Class for the user access flags of a node in the address space.
Toolkit implementation to support any number of roles.
*/
class SERVER_CORE_EXPORT NodeAccessInfoBase : public NodeAccessInfo
{
    UA_DISABLE_COPY(NodeAccessInfoBase);
public:
    /** Creates a NodeAccessInfoBase object.
    */
    NodeAccessInfoBase();

    void setAccessRestrictions(AccessRestrictions accessRestrictions);
    void setRolePermissions(OpcUa_UInt32 roleId, Permissions permissions);
    void setRolePermissions(const UaRolePermissionTypes& rolePermissions);

    // Interface NodeAccessInfo
    virtual UaStatus hasAccess(const SessionUserContext* pUserContext, Permissions requestedPermissions, AccessRestrictions availableFlags) const;
    virtual bool hasAccess(const SessionUserContext* pUserContext, Permissions requestedPermissions) const;
    virtual AccessRestrictions accessRestrictions() const;
    virtual UaRolePermissionTypes getRolePermissions() const;
    virtual UaRolePermissionTypes getUserRolePermissions(const SessionUserContext* pUserContext) const;
    // End - Interface NodeAccessInfo

protected:
    virtual ~NodeAccessInfoBase();
    void clear();

    friend UABASE_EXPORT UaDataStream &operator<<(UaDataStream &, const NodeAccessInfoBase &);
    friend UABASE_EXPORT UaDataStream &operator >> (UaDataStream &, NodeAccessInfoBase &);

protected:
    OpcUa_UInt32* m_pRoleIds;
    OpcUa_UInt32* m_pPermissions;
    OpcUa_UInt32  m_numRolePermissions;
    AccessRestrictions m_accessRestrictions;
};

// define UaDataStream operators for NodeAccessInfoBase.
UABASE_EXPORT UaDataStream &operator<<(UaDataStream &, const NodeAccessInfoBase &);
UABASE_EXPORT UaDataStream &operator >> (UaDataStream &, NodeAccessInfoBase &);

#endif // NODEACCESSINFOBASE_H
