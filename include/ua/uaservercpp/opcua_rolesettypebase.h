/******************************************************************************
** opcua_rolesettypebase.h
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

#ifndef __OPCUA_ROLESETTYPEBASE_H__
#define __OPCUA_ROLESETTYPEBASE_H__

#include "opcua_baseobjecttype.h"
#include "basenodes.h"
#include "opcua_identifiers.h"
#include "opcua_propertytype.h"
#include "uaargument.h"
#include "uaidentitymappingruletype.h"

// Namespace for the UA information model http://opcfoundation.org/UA/
namespace OpcUa {

class PropertyType;
class RoleType;

/** Generated base class for a RoleSetType.
 *
 *  This class contains the generated base code for the object type RoleSetType
 *  representing an OPC UA ObjectType. This class is used to create the object type and to
 *  create and represent instances of the object type in the server address space.
 *
 *  **Object members of the RoleSetType:**
 *
 *  Browse Name  | TypeDefinition | Modelling Rule      | See Also
 *  -------------|----------------|---------------------|---------
 *  \<RoleName\> | RoleType       | OptionalPlaceholder | &nbsp;
 *
 */
class SERVER_CORE_EXPORT RoleSetTypeBase:
    public OpcUa::BaseObjectType
{
    UA_DISABLE_COPY(RoleSetTypeBase);
protected:
    virtual ~RoleSetTypeBase();
public:
    // construction / destruction
    RoleSetTypeBase(const UaNodeId& nodeId, UaObject* pInstanceDeclarationObject, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    RoleSetTypeBase(const UaNodeId& nodeId, const UaString& name, OpcUa_UInt16 browseNameNameSpaceIndex, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    RoleSetTypeBase(
        UaBase::Object*    pBaseNode,
        XmlUaNodeFactoryManager*   pFactory,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);
    static void createTypes();
    static void clearStaticMembers();

    virtual UaNodeId       typeDefinitionId() const;

#if SUPPORT_Method_Server_Facet
    //- Interface MethodManager -----------------------------------------------------------
    /** Call method of an UA object. */
    virtual UaStatus beginCall(
        MethodManagerCallback* pCallback,
        const ServiceContext&  serviceContext,
        OpcUa_UInt32           callbackHandle,
        MethodHandle*          pMethodHandle,
        const UaVariantArray&  inputArguments);
    virtual UaStatus call(
        const ServiceContext&  serviceContext,
        MethodHandle*          pMethodHandle,
        const UaVariantArray&  inputArguments,
        UaVariantArray&        outputArguments,
        UaStatusCodeArray&     inputArgumentResults,
        UaDiagnosticInfos&     inputArgumentDiag);
    //- Interface MethodManager -----------------------------------------------------------
#endif // SUPPORT_Method_Server_Facet

#if SUPPORT_Method_Server_Facet
    virtual UaStatus AddRole(
        const ServiceContext& serviceContext /**<General context for the service calls containing
                                                 information like the session object,
                                                 return diagnostic mask and timeout hint.*/,
        const UaString& RoleName,
        const UaString& NamespaceUri,
        UaNodeId& RoleNodeId) = 0;
    virtual UaStatus RemoveRole(
        const ServiceContext& serviceContext /**<General context for the service calls containing
                                                 information like the session object,
                                                 return diagnostic mask and timeout hint.*/,
        const UaNodeId& RoleNodeId) = 0;
#endif // SUPPORT_Method_Server_Facet

#if SUPPORT_Method_Server_Facet
    virtual OpcUa::BaseMethod* getAddRole();
    virtual const OpcUa::BaseMethod* getAddRole() const;
    virtual OpcUa::BaseMethod* getRemoveRole();
    virtual const OpcUa::BaseMethod* getRemoveRole() const;
#endif // SUPPORT_Method_Server_Facet

// Add placeholders
    virtual UaStatus addRoleName_Placeholder(OpcUa::RoleType *pRoleName_Placeholder);

    // NodeAccessInfo management
    virtual void useAccessInfoFromType();
    void useAccessInfoFromInstance(RoleSetTypeBase *pInstance);

protected:
    // Object nodes
    // Object RoleName_Placeholder
    static OpcUa::RoleType*  s_pRoleName_Placeholder;


    // Method nodes
    static OpcUa::BaseMethod* s_pAddRoleMethod;
    OpcUa::BaseMethod*  m_pAddRoleMethod;
    static OpcUa::BaseMethod* s_pRemoveRoleMethod;
    OpcUa::BaseMethod*  m_pRemoveRoleMethod;


private:
    void initialize();

private:
    static bool s_typeNodesCreated;
};

} // End namespace for the UA information model http://opcfoundation.org/UA/

#endif // #ifndef __OPCUAROLESETTYPEBASE_H__


