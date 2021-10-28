/******************************************************************************
** opcua_roletypebase.h
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

#ifndef __OPCUA_ROLETYPEBASE_H__
#define __OPCUA_ROLETYPEBASE_H__

#include "opcua_baseobjecttype.h"
#include "basenodes.h"
#include "opcua_identifiers.h"
#include "opcua_propertytype.h"
#include "uaargument.h"
#include "uaendpointtype.h"
#include "uaidentitymappingruletype.h"

// Namespace for the UA information model http://opcfoundation.org/UA/
namespace OpcUa {

class PropertyType;

/** Generated base class for a RoleType.
 *
 *  This class contains the generated base code for the object type RoleType
 *  representing an OPC UA ObjectType. This class is used to create the object type and to
 *  create and represent instances of the object type in the server address space.
 *
 *  **Variable members of the RoleType:**
 *
 *  Browse Name         | DataType                | TypeDefinition | Modelling Rule | See Also
 *  --------------------|-------------------------|----------------|----------------|---------------------------------------------------------
 *  Applications        | String                  | PropertyType   | Optional       | \ref getApplications, \ref setApplications
 *  ApplicationsExclude | Boolean                 | PropertyType   | Optional       | \ref getApplicationsExclude, \ref setApplicationsExclude
 *  Endpoints           | EndpointType            | PropertyType   | Optional       | \ref getEndpoints, \ref setEndpoints
 *  EndpointsExclude    | Boolean                 | PropertyType   | Optional       | \ref getEndpointsExclude, \ref setEndpointsExclude
 *  Identities          | IdentityMappingRuleType | PropertyType   | Mandatory      | \ref getIdentities, \ref setIdentities
 *
 */
class SERVER_CORE_EXPORT RoleTypeBase:
    public OpcUa::BaseObjectType
{
    UA_DISABLE_COPY(RoleTypeBase);
protected:
    virtual ~RoleTypeBase();
public:
    // construction / destruction
    RoleTypeBase(const UaNodeId& nodeId, UaObject* pInstanceDeclarationObject, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    RoleTypeBase(const UaNodeId& nodeId, const UaString& name, OpcUa_UInt16 browseNameNameSpaceIndex, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    RoleTypeBase(
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
    virtual UaStatus AddApplication(
        const ServiceContext& serviceContext /**<General context for the service calls containing
                                                 information like the session object,
                                                 return diagnostic mask and timeout hint.*/,
        const UaString& RuleToAdd) = 0;
    virtual UaStatus AddEndpoint(
        const ServiceContext& serviceContext /**<General context for the service calls containing
                                                 information like the session object,
                                                 return diagnostic mask and timeout hint.*/,
        const UaEndpointType& RuleToAdd) = 0;
    virtual UaStatus AddIdentity(
        const ServiceContext& serviceContext /**<General context for the service calls containing
                                                 information like the session object,
                                                 return diagnostic mask and timeout hint.*/,
        const UaIdentityMappingRuleType& RuleToAdd) = 0;
    virtual UaStatus RemoveApplication(
        const ServiceContext& serviceContext /**<General context for the service calls containing
                                                 information like the session object,
                                                 return diagnostic mask and timeout hint.*/,
        const UaString& RuleToRemove) = 0;
    virtual UaStatus RemoveEndpoint(
        const ServiceContext& serviceContext /**<General context for the service calls containing
                                                 information like the session object,
                                                 return diagnostic mask and timeout hint.*/,
        const UaEndpointType& RuleToRemove) = 0;
    virtual UaStatus RemoveIdentity(
        const ServiceContext& serviceContext /**<General context for the service calls containing
                                                 information like the session object,
                                                 return diagnostic mask and timeout hint.*/,
        const UaIdentityMappingRuleType& RuleToRemove) = 0;
#endif // SUPPORT_Method_Server_Facet

    virtual void setApplications(const UaStringArray& Applications);
    virtual void getApplications(UaStringArray& Applications) const;

    virtual void setApplicationsExclude(OpcUa_Boolean ApplicationsExclude);
    virtual OpcUa_Boolean getApplicationsExclude() const;

    virtual void setEndpoints(const UaEndpointTypes& Endpoints);
    virtual void getEndpoints(UaEndpointTypes& Endpoints) const;

    virtual void setEndpointsExclude(OpcUa_Boolean EndpointsExclude);
    virtual OpcUa_Boolean getEndpointsExclude() const;

    virtual void setIdentities(const UaIdentityMappingRuleTypes& Identities);
    virtual void getIdentities(UaIdentityMappingRuleTypes& Identities) const;

    virtual OpcUa::PropertyType* getApplicationsNode();
    virtual const OpcUa::PropertyType* getApplicationsNode() const;
    virtual OpcUa::PropertyType* getApplicationsExcludeNode();
    virtual const OpcUa::PropertyType* getApplicationsExcludeNode() const;
    virtual OpcUa::PropertyType* getEndpointsNode();
    virtual const OpcUa::PropertyType* getEndpointsNode() const;
    virtual OpcUa::PropertyType* getEndpointsExcludeNode();
    virtual const OpcUa::PropertyType* getEndpointsExcludeNode() const;
    virtual OpcUa::PropertyType* getIdentitiesNode();
    virtual const OpcUa::PropertyType* getIdentitiesNode() const;
#if SUPPORT_Method_Server_Facet
    virtual OpcUa::BaseMethod* getAddApplication();
    virtual const OpcUa::BaseMethod* getAddApplication() const;
    virtual OpcUa::BaseMethod* getAddEndpoint();
    virtual const OpcUa::BaseMethod* getAddEndpoint() const;
    virtual OpcUa::BaseMethod* getAddIdentity();
    virtual const OpcUa::BaseMethod* getAddIdentity() const;
    virtual OpcUa::BaseMethod* getRemoveApplication();
    virtual const OpcUa::BaseMethod* getRemoveApplication() const;
    virtual OpcUa::BaseMethod* getRemoveEndpoint();
    virtual const OpcUa::BaseMethod* getRemoveEndpoint() const;
    virtual OpcUa::BaseMethod* getRemoveIdentity();
    virtual const OpcUa::BaseMethod* getRemoveIdentity() const;
#endif // SUPPORT_Method_Server_Facet

    // NodeAccessInfo management
    virtual void useAccessInfoFromType();
    void useAccessInfoFromInstance(RoleTypeBase *pInstance);

protected:
    // Variable nodes
    // Variable Applications
    static OpcUa::PropertyType*  s_pApplications;
    OpcUa::PropertyType*  m_pApplications;
    // Variable ApplicationsExclude
    static OpcUa::PropertyType*  s_pApplicationsExclude;
    OpcUa::PropertyType*  m_pApplicationsExclude;
    // Variable Endpoints
    static OpcUa::PropertyType*  s_pEndpoints;
    OpcUa::PropertyType*  m_pEndpoints;
    // Variable EndpointsExclude
    static OpcUa::PropertyType*  s_pEndpointsExclude;
    OpcUa::PropertyType*  m_pEndpointsExclude;
    // Variable Identities
    static OpcUa::PropertyType*  s_pIdentities;
    OpcUa::PropertyType*  m_pIdentities;

#if SUPPORT_Method_Server_Facet
    // Method nodes
    static OpcUa::BaseMethod* s_pAddApplicationMethod;
    OpcUa::BaseMethod*  m_pAddApplicationMethod;
    static OpcUa::BaseMethod* s_pAddEndpointMethod;
    OpcUa::BaseMethod*  m_pAddEndpointMethod;
    static OpcUa::BaseMethod* s_pAddIdentityMethod;
    OpcUa::BaseMethod*  m_pAddIdentityMethod;
    static OpcUa::BaseMethod* s_pRemoveApplicationMethod;
    OpcUa::BaseMethod*  m_pRemoveApplicationMethod;
    static OpcUa::BaseMethod* s_pRemoveEndpointMethod;
    OpcUa::BaseMethod*  m_pRemoveEndpointMethod;
    static OpcUa::BaseMethod* s_pRemoveIdentityMethod;
    OpcUa::BaseMethod*  m_pRemoveIdentityMethod;
#endif // SUPPORT_Method_Server_Facet

private:
    void initialize();

private:
    static bool s_typeNodesCreated;
};

} // End namespace for the UA information model http://opcfoundation.org/UA/

#endif // #ifndef __OPCUAROLETYPEBASE_H__


