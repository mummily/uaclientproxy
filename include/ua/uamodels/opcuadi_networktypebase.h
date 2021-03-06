/******************************************************************************
** opcuadi_networktypebase.h
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
** Project: C++ OPC Server SDK information model for namespace http://opcfoundation.org/UA/DI/
**
** Description: OPC Unified Architecture Software Development Kit.
**
******************************************************************************/

#ifndef __OPCUADI_NETWORKTYPEBASE_H__
#define __OPCUADI_NETWORKTYPEBASE_H__

#include "opcua_baseobjecttype.h"
#include "opcuadi_datatypes.h"
#include "basenodes.h"
#include "opcua_propertytype.h"
#include "opcuadi_identifiers.h"
#include "opcuadi_instancefactory_devices.h"
#include "uaargument.h"

// Namespace for the UA information model http://opcfoundation.org/UA/DI/
namespace OpcUaDi {

class ConnectionPointType;
class FunctionalGroupType;
class LockingServicesType;
class ProtocolType;

/** Generated base class for a NetworkType.
 *
 *  This class contains the generated base code for the object type NetworkType
 *  representing an OPC UA ObjectType. This class is used to create the object type and to
 *  create and represent instances of the object type in the server address space.
 *
 *  **Object members of the NetworkType:**
 *
 *  Browse Name           | TypeDefinition      | Modelling Rule       | See Also
 *  ----------------------|---------------------|----------------------|-------------
 *  \<CPIdentifier\>      | ConnectionPointType | OptionalPlaceholder  | &nbsp;
 *  \<ProfileIdentifier\> | ProtocolType        | MandatoryPlaceholder | &nbsp;
 *  Lock                  | LockingServicesType | Optional             | \ref getLock
 *
 */
class UAMODELS_EXPORT NetworkTypeBase:
    public OpcUa::BaseObjectType
{
    UA_DISABLE_COPY(NetworkTypeBase);
protected:
    virtual ~NetworkTypeBase();
public:
    // construction / destruction
    NetworkTypeBase(const UaNodeId& nodeId, UaObject* pInstanceDeclarationObject, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    NetworkTypeBase(const UaNodeId& nodeId, const UaString& name, OpcUa_UInt16 browseNameNameSpaceIndex, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    NetworkTypeBase(
        UaBase::Object*    pBaseNode,
        XmlUaNodeFactoryManager*   pFactory,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);
    static void createTypes();
    static void clearStaticMembers();

    virtual UaNodeId       typeDefinitionId() const;


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


    virtual OpcUaDi::LockingServicesType* getLock();

// Add placeholders
    virtual UaStatus addCP(OpcUaDi::ConnectionPointType *pCP);
    virtual UaStatus addProfile(OpcUaDi::ProtocolType *pProfile);

    // NodeAccessInfo management
    virtual void useAccessInfoFromType();
    void useAccessInfoFromInstance(NetworkTypeBase *pInstance);

protected:
    // Object nodes
    // Object CPIdentifier
    static OpcUaDi::ConnectionPointType*  s_pCPIdentifier;
    // Object ProfileIdentifier
    static OpcUaDi::ProtocolType*  s_pProfileIdentifier;
    // Object Lock
    static OpcUaDi::LockingServicesType*  s_pLock;
    OpcUaDi::LockingServicesType*  m_pLock;



private:
    void initialize();

private:
    static bool s_typeNodesCreated;
};

} // End namespace for the UA information model http://opcfoundation.org/UA/DI/

#endif // #ifndef __OPCUADINETWORKTYPEBASE_H__


