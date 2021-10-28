/******************************************************************************
** opcua_audiovariabletype.h
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

#ifndef __OPCUA_AUDIOVARIABLETYPE_H__
#define __OPCUA_AUDIOVARIABLETYPE_H__

#include "opcua_basedatavariabletype.h"
#include "opcua_identifiers.h"

// Namespace for the UA information model http://opcfoundation.org/UA/
namespace OpcUa {

class PropertyType;

/** Implements OPC UA Variables of the type AudioVariableType
 *
 *  **Variable members of the AudioVariableType:**
 *
 *  Browse Name | DataType | TypeDefinition | Modelling Rule | See Also
 *  ------------|----------|----------------|----------------|-------------------------------------
 *  AgencyId    | String   | PropertyType   | Optional       | \ref getAgencyId, \ref setAgencyId
 *  ListId      | String   | PropertyType   | Optional       | \ref getListId, \ref setListId
 *  VersionId   | String   | PropertyType   | Optional       | \ref getVersionId, \ref setVersionId
 *
 */
class SERVER_CORE_EXPORT AudioVariableType:
    public OpcUa::BaseDataVariableType
{
    UA_DISABLE_COPY(AudioVariableType);
protected:
    virtual ~AudioVariableType();
public:
    AudioVariableType(
        UaNode*            pParentNode,
        UaVariable*        pInstanceDeclarationVariable,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);
    AudioVariableType(
        const UaNodeId&    nodeId,
        const UaString&    name,
        OpcUa_UInt16       browseNameNameSpaceIndex,
        const UaVariant&   initialValue,
        OpcUa_Byte         accessLevel,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);
    AudioVariableType(
        UaBase::Variable*  pBaseNode,
        XmlUaNodeFactoryManager*   pFactory,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);

    static void createTypes();
    static void clearStaticMembers();

    virtual UaNodeId       typeDefinitionId() const;

    virtual void setAgencyId(const UaString& AgencyId);
    virtual UaString getAgencyId() const;

    virtual void setListId(const UaString& ListId);
    virtual UaString getListId() const;

    virtual void setVersionId(const UaString& VersionId);
    virtual UaString getVersionId() const;

    virtual OpcUa::PropertyType* getAgencyIdNode();
    virtual const OpcUa::PropertyType* getAgencyIdNode() const;
    virtual OpcUa::PropertyType* getListIdNode();
    virtual const OpcUa::PropertyType* getListIdNode() const;
    virtual OpcUa::PropertyType* getVersionIdNode();
    virtual const OpcUa::PropertyType* getVersionIdNode() const;

    // NodeAccessInfo management
    virtual void useAccessInfoFromType();
    void useAccessInfoFromInstance(AudioVariableType *pInstance);

protected:
    // Variable nodes
    // Variable AgencyId
    static OpcUa::PropertyType*  s_pAgencyId;
    OpcUa::PropertyType*  m_pAgencyId;
    // Variable ListId
    static OpcUa::PropertyType*  s_pListId;
    OpcUa::PropertyType*  m_pListId;
    // Variable VersionId
    static OpcUa::PropertyType*  s_pVersionId;
    OpcUa::PropertyType*  m_pVersionId;


private:
    void initialize(NodeManagerConfig* pNodeConfig);

private:
    static bool s_typeNodesCreated;
};

} // End namespace for the UA information model http://opcfoundation.org/UA/

#endif // #ifndef __OPCUA_AUDIOVARIABLETYPE_H__

