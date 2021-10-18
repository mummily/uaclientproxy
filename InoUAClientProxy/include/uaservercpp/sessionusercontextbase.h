/******************************************************************************
** sessionusercontextbase.h
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
** Description: OPC server core module session user context class.
**
******************************************************************************/
#ifndef SESSIONUSERCONTEXTBASE_H
#define SESSIONUSERCONTEXTBASE_H

#include "sessionusercontext.h"
#include "uamutex.h"

class UaUserIdentityToken;

/** @brief Class for user context of a Session.

 Toolkit implementation of the SessionUserContext interface that supports a list of RoleIds
 */
class SERVER_CORE_EXPORT SessionUserContextBase : public SessionUserContext
{
public:
    SessionUserContextBase();

    // Interface SessionUserContext
    /** Add a role to the SessionUserContext.
    *  @param roleId    Unique identifier for the role. This id is set when the role is registered.
    *  @return          True if the RoleId was successfully added. False the SessionUserContext already had this role before.
    */
    virtual bool addRole(OpcUa_UInt32 roleId);
    /** Check if a specific role is assigned to this SessionUserContext.
    *  @param roleId    Unique identifier for the role. This id is set when the role is registered.
    *  @return          True if the RoleId is assigned to the SessionUserContext. False otherwise.
    */
    virtual bool hasRole(OpcUa_UInt32 roleId) const;
    /** Remove a Role from the SessionUserContext.
    *  @param roleId    Unique identifier for the role. This id is set when the role is registered.
    *  @return          True if the RoleId was removed from the SessionUserContext. False otherwise.
    */
    virtual bool removeRole(OpcUa_UInt32 roleId);
    /** Set the identiy for the SessionUserContext (e.g. Anonymous, UserName, Thumbprint)
    *  @param pIdentity The identity that was used to activate the Session.
    *  @return          Good.
    */
    virtual UaStatus setIdentity(const UaIdentityMappingRuleType* pIdentity);
    /** Set the identiy for the SessionUserContext (e.g. Anonymous, UserName, Thumbprint)
    *  @param pIdentity The identity that was used to activate the Session.
    *  @return          Good if converting the UserIdentityToken into a IdentityMappingRule succeeded. Bad otherwise.
    */
    virtual UaStatus setIdentity(const UaUserIdentityToken* pUserIdentityToken);
    /** Set the IdentityMappingRule assigned to the SessionUserContext.
    *  @return          The UaIdentityMappingRule set for the SessionUserContext.
    */
    virtual UaIdentityMappingRuleType getUserIdentity() const;
    /** Get a list of RoleIds that are assigned to the SessionUserContext.
    *  @return          List of RoleIds.
    */
    virtual UaUInt32Array getRoleIds() const;
    /** Check if the SessionUserContext has root priviledges.
    *  @return          True if the SessionUserContext has root priviledges. False otherwise.
    */
    virtual bool isRoot() const;
    // End - Interface SessionUserContext

    virtual void setIsRoot(bool bIsRoot);

protected:
    virtual ~SessionUserContextBase();
    UaIdentityMappingRuleType m_identity;

private:
    mutable UaMutex          m_mutex;
    bool                     m_bIsRoot;             // flag for root - root has access to everything
    UaUInt32Array            m_lstRoleIds;          // all roleIds this user is member of
};

#endif // SESSIONUSERCONTEXTBASE_H
