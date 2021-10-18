/******************************************************************************
** nodeaccessinfo.h
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
#ifndef NODEACCESSINFO_H
#define NODEACCESSINFO_H

#include "opcuatypes.h"
#include "referencecounter.h"
#include "uarolepermissiontype.h"
#include "session.h"

/** @brief Class for the user access flags of a node in the address space.

 OPC UA defines different information model elements like Objects, Variables, Method and Events
 and different services to access the information. This access can be restricted based on the user
 that tries to access the information. The user authentication is done during the Session
 creation and the user information is stored in the Session using the class SessionUserContext.

 The access masks and the authorized user and group are stored in the UaNode with the class
 NodeAccessInfo. The information from SessionUserContext and NodeAccessInfo is used to determine
 if the requested operation like Read, Write or Browse can be executed.

 The different permissions are defined by the PermissionType.

 The different masks are defined by AccessMask.

 The class is reference counted. After creation, the reference counter is 1. If the NodeAccessInfo is
 set on a node with UaNode::attachAccessInfo(), the reference counter is not incremented and the node
 takes ownership of the one reference. If you want to set NodeAccessInfo on additional nodes, the
 method UaNode::setAccessInfo() is used. It increments the reference counter of NodeAccessInfo.
 */
class SERVER_CORE_EXPORT NodeAccessInfo : public ReferenceCounter
{
    UA_DISABLE_COPY(NodeAccessInfo);
public:
    /// @brief Definition of the PermissionType Enumeration defining the permissions of the NodeAccessInfo
    /** PermissionFlags enumeration  */
    enum PermissionFlags
    {
        PERMISSION_NONE                 = 0x00000000,       /*!< No access to any attribute or reference of the Node */
        PERMISSION_BROWSE               = 0x00000001,       /*!< See referenes to and from the Node. This includes reading all attributes other than Value and RolePermissions */
        PERMISSION_READROLEPERMISSIONS  = 0x00000002,       /*!< Read access to the attribute RolePermissions */
        PERMISSION_WRITEATTRIBUTE       = 0x00000004,       /*!< Write access to the attributes other than Value, Historizing and  RolePermissions if the WriteMask indicates that the Attribute is writeable */
        PERMISSION_WRITEROLEPERMISSIONS = 0x00000008,       /*!< Write access to the attribute RolePermissions if the WriteMask indicates that the Attribute is writeable*/
        PERMISSION_WRITEHISTORIZING     = 0x00000010,       /*!< Write access to the attribute Historizing if the WriteMask indicates that the Attribute is writeable*/
        PERMISSION_READ                 = 0x00000020,       /*!< Read access to the Value attribute */
        PERMISSION_WRITE                = 0x00000040,       /*!< Write access to the Value attribute */
        PERMISSION_READHISTORY          = 0x00000080,       /*!< Read history associated with the Node */
        PERMISSION_INSERTHISTORY        = 0x00000100,       /*!< Insert history associated with the Node */
        PERMISSION_MODIFYHISTORY        = 0x00000200,       /*!< Modify history associated with the Node */
        PERMISSION_DELETEHISTORY        = 0x00000400,       /*!< Delete history associated with the Node */
        PERMISSION_RECEIVEEVENTS        = 0x00000800,       /*!< Receive events rights */
        PERMISSION_CALL                 = 0x00001000,       /*!< Execute method call rights */
        PERMISSION_ADDREFERENCE         = 0x00002000,       /*!< Allow adding references to the Node */
        PERMISSION_REMOVEREFERENCE      = 0x00004000,       /*!< Allow removing references to / from the Node */
        PERMISSION_DELETENODE           = 0x00008000,       /*!< Allow to delete the Node */
        PERMISSION_ADDNODE              = 0x00010000,       /*!< Allow to add Nodes to the Namespace. Only used for RolePermissions Properties of the NamespaceMetadata object */
        PERMISSION_OBSERVATION          = PERMISSION_BROWSE | PERMISSION_READ | PERMISSION_READHISTORY | PERMISSION_RECEIVEEVENTS,  /*!< Typical access permissions for an observer role */
        PERMISSION_OPERATION            = PERMISSION_OBSERVATION | PERMISSION_WRITE | PERMISSION_CALL,                              /*!< Typical access permissions for an operator role */
        PERMISSION_OBSERVATION_VARIABLE = PERMISSION_BROWSE | PERMISSION_READ | PERMISSION_READHISTORY,                             /*!< Typical access permissions for an observer role for a variable */
        PERMISSION_OPERATION_VARIABLE   = PERMISSION_OBSERVATION_VARIABLE | PERMISSION_WRITE,                                       /*!< Typical access permissions for an operator role for a variable*/
        PERMISSION_OBSERVATION_METHOD   = PERMISSION_BROWSE,                                                                        /*!< Typical access permissions for an observer role for a method*/
        PERMISSION_OPERATION_METHOD     = PERMISSION_OBSERVATION_METHOD | PERMISSION_CALL,                                          /*!< Typical access permissions for an operator role for a method*/
        PERMISSION_OBSERVATION_OBJECT   = PERMISSION_BROWSE | PERMISSION_READHISTORY | PERMISSION_RECEIVEEVENTS,                    /*!< Typical access permissions for an observer role for an object*/
        PERMISSION_OPERATION_OBJECT     = PERMISSION_OBSERVATION_OBJECT | PERMISSION_CALL,                                          /*!< Typical access permissions for an operator role for an object*/
        PERMISSION_ALL                  = 0x0001FFFF        /*!< Full access */
    };
    // Type to use as parameter when using Permission flags
    typedef OpcUa_UInt32 Permissions;
    static const OpcUa_UInt16 NumPermissionBits = 17;

    /// @brief Definition of the RestrictionFlags Enumeration defining possible restrictions to access a resource
    /** RestrictionFlags enumeration  */
    enum RestrictionFlags
    {
        RESTRICTION_NONE                        = 0x00,     /*!< No requirements for access */
        RESTRICTION_SIGNING_REQUIRED            = 0x01,     /*!< Access requires message signing */
        RESTRICTION_SIGN_AND_ENCRYPT_REQUIRED   = 0x03,     /*!< Access requires message signing and encryption */
        RESTRICTION_SESSION_REQUIRED            = 0x04,     /*!< Access requires a session */
        RESTRICTION_APPLY_TO_BROWSE             = 0x08,     /*!< Also apply the restrictions flags for the browse service */
        RESTRICTION_ALL                         = 0x0F,     /*!< Require all flags above */
        RESTRICTION_REQUIRED_MASK               = RESTRICTION_SIGN_AND_ENCRYPT_REQUIRED | RESTRICTION_SESSION_REQUIRED  /*!< Mask to just use the 'Required' flags i.e. not RESTRICTION_APPLY_TO_BROWSE */
    };
    // Type to use as parameter when using AccessRestriction flags
    typedef OpcUa_UInt16 AccessRestrictions;

    // interface definition
    /** Check if access to a requested operation is granted for a specific SessionUserContext.
    *  The requested permission can be a single flag or a combination of PermissionFlags.
    *  @param pUserContext          The SessionUserContext gives access to a list of RoleIds associated with a user.
    *  @param requestedPermissions  The requested permission can be a single flag or a combination of PermissionFlags.
    *  @param availableFlags        The RestrictionFlags that are available form the session.
    *  @return                      True if access is granted. Otherwise false.
    */
    virtual UaStatus hasAccess(const SessionUserContext* pUserContext, Permissions requestedPermissions, AccessRestrictions availableFlags) const = 0;
    /** Check if access to a requested operation is granted for a specific SessionUserContext.
    *  The requested permission can be a single flag or a combination of PermissionFlags.
    *  @param pUserContext          The SessionUserContext gives access to a list of RoleIds associated with a user.
    *  @param requestedPermissions  The requested permission can be a single flag or a combination of PermissionFlags.
    *  @return                      True if access is granted. Otherwise false.
    */
    virtual bool hasAccess(const SessionUserContext* pUserContext, Permissions requestedPermissions) const = 0;
    /** Return the RestrictionFlags for the NodeAccessInfo.
    *  @return      The bitwise OR combination of the RestrictionFlags
    */
    virtual AccessRestrictions accessRestrictions() const = 0;
    /** Return all RolePermissions configured for the NodeAccessInfo.
    *  A RolePermission is combination of RoleId and a number of PermissionFlags.
    *  @return      A list of all RolePermissions configured for the NodeAccessInfo
    */
    virtual UaRolePermissionTypes getRolePermissions() const = 0;
    /** Return all RolePermissions configured for the NodeAccessInfo for a specific user.
    *  A RolePermission consists of RoleId and a number of PermissionFlags.
    *  @param pUserContext      The SessionUserContext gives access to a list of RoleIds associated with a user.
    *  @return                  A list of all RolePermissions configured for the NodeAccessInfo
    */
    virtual UaRolePermissionTypes getUserRolePermissions(const SessionUserContext* pUserContext) const = 0;

    /** Helper method to easily check access based on a session context.
    *  The Precedence to do the checks is:
    *  1. Check the NodePermissions if set
    *  2. Check the DefaultPermissions if set
    *  @param pSession              The session context providing access to the SessionUserContext.
    *                               The SessionUserContext is needed to check the permissions (NodePermissions and DefaultPermissions).
    *  @param pNodePermissions      The NodeAccessInfo to validate.
    *  @param pDefaultPermissions   The default NodeAccessInfo to validate.
    *  @param requestedPermissions  PermissionFlags specifying what kind of permissions are requested
    *  @return                      Good when access is granted otherwise a specific error indicating why the access is denied.
    */
    static UaStatus checkAccess(
        const Session* pSession,
        const NodeAccessInfo* pNodePermissions,
        const NodeAccessInfo* pDefaultPermissions,
        Permissions requestedPermissions)
    {
        SessionUserContext* pSessionUserContext = (pSession == NULL ? NULL : pSession->pUserContext());

        AccessRestrictions accessRestrictions = accessRestrictionsFromSession(pSession);

        // Check Permission set for the Node
        if (pNodePermissions)
        {
            return pNodePermissions->hasAccess(pSessionUserContext, requestedPermissions, accessRestrictions);
        }
        // // Check DefaultPermission
        else if (pDefaultPermissions)
        {
            return pDefaultPermissions->hasAccess(pSessionUserContext, requestedPermissions, accessRestrictions);
        }
        // if nothing is configured we grant access
        return OpcUa_Good;
    }

    /** Helper method to extract the available RestrictionFlags from the SessionContext.
    *  - if the Session is not SessionLess the flag RESTRICTION_SESSION_REQUIRED is set.
    *  - if the MessageSecurityMode of the Session includes signing the flag RESTRICTION_SIGNING_REQUIRED is set.
    *  - if the MessageSecurityMode of the Session includes encryption the flag RESTRICTION_SIGN_AND_ENCRYPT_REQUIRED is set.
    *  @param pSession      The session context.
    *  @return              The bitwise OR combination of the RestrictionFlags described above.
    */
    static AccessRestrictions accessRestrictionsFromSession(const Session* pSession)
    {
        AccessRestrictions accessRestrictions = RESTRICTION_NONE;

        OpcUa_MessageSecurityMode securityMode = (pSession == NULL ? OpcUa_MessageSecurityMode_None : pSession->getSecureChannelMessageSecurityMode());

        if (pSession && pSession->isSessionLess() == OpcUa_False)
        {
            accessRestrictions |= RESTRICTION_SESSION_REQUIRED;
        }

        if (securityMode == OpcUa_MessageSecurityMode_SignAndEncrypt)
        {
            accessRestrictions |= RESTRICTION_SIGN_AND_ENCRYPT_REQUIRED;
        }
        else if (securityMode == OpcUa_MessageSecurityMode_Sign)
        {
            accessRestrictions |= RESTRICTION_SIGNING_REQUIRED;
        }

        return accessRestrictions;
    }

protected:
    NodeAccessInfo() {}
    virtual ~NodeAccessInfo() {}
};

#endif // NODEACCESSINFO_H
