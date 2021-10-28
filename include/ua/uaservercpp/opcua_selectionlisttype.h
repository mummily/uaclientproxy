/******************************************************************************
** opcua_selectionlisttype.h
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

#ifndef __OPCUA_SELECTIONLISTTYPE_H__
#define __OPCUA_SELECTIONLISTTYPE_H__

#include "opcua_basedatavariabletype.h"
#include "opcua_identifiers.h"

// Namespace for the UA information model http://opcfoundation.org/UA/
namespace OpcUa {

class PropertyType;

/** Implements OPC UA Variables of the type SelectionListType
 *
 *  **Variable members of the SelectionListType:**
 *
 *  Browse Name           | DataType      | TypeDefinition | Modelling Rule | See Also
 *  ----------------------|---------------|----------------|----------------|-------------------------------------------------------------
 *  RestrictToList        | Boolean       | PropertyType   | Optional       | \ref getRestrictToList, \ref setRestrictToList
 *  SelectionDescriptions | LocalizedText | PropertyType   | Optional       | \ref getSelectionDescriptions, \ref setSelectionDescriptions
 *  Selections            | BaseDataType  | PropertyType   | Mandatory      | \ref getSelections, \ref setSelections
 *
 */
class SERVER_CORE_EXPORT SelectionListType:
    public OpcUa::BaseDataVariableType
{
    UA_DISABLE_COPY(SelectionListType);
protected:
    virtual ~SelectionListType();
public:
    SelectionListType(
        UaNode*            pParentNode,
        UaVariable*        pInstanceDeclarationVariable,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);
    SelectionListType(
        const UaNodeId&    nodeId,
        const UaString&    name,
        OpcUa_UInt16       browseNameNameSpaceIndex,
        const UaVariant&   initialValue,
        OpcUa_Byte         accessLevel,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);
    SelectionListType(
        UaBase::Variable*  pBaseNode,
        XmlUaNodeFactoryManager*   pFactory,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);

    static void createTypes();
    static void clearStaticMembers();

    virtual UaNodeId       typeDefinitionId() const;

    virtual void setRestrictToList(OpcUa_Boolean RestrictToList);
    virtual OpcUa_Boolean getRestrictToList() const;

    virtual void setSelectionDescriptions(const UaLocalizedTextArray& SelectionDescriptions);
    virtual void getSelectionDescriptions(UaLocalizedTextArray& SelectionDescriptions) const;

    virtual void setSelections(const UaVariantArray& Selections);
    virtual void getSelections(UaVariantArray& Selections) const;

    virtual OpcUa::PropertyType* getRestrictToListNode();
    virtual const OpcUa::PropertyType* getRestrictToListNode() const;
    virtual OpcUa::PropertyType* getSelectionDescriptionsNode();
    virtual const OpcUa::PropertyType* getSelectionDescriptionsNode() const;
    virtual OpcUa::PropertyType* getSelectionsNode();
    virtual const OpcUa::PropertyType* getSelectionsNode() const;

    // NodeAccessInfo management
    virtual void useAccessInfoFromType();
    void useAccessInfoFromInstance(SelectionListType *pInstance);

protected:
    // Variable nodes
    // Variable RestrictToList
    static OpcUa::PropertyType*  s_pRestrictToList;
    OpcUa::PropertyType*  m_pRestrictToList;
    // Variable SelectionDescriptions
    static OpcUa::PropertyType*  s_pSelectionDescriptions;
    OpcUa::PropertyType*  m_pSelectionDescriptions;
    // Variable Selections
    static OpcUa::PropertyType*  s_pSelections;
    OpcUa::PropertyType*  m_pSelections;


private:
    void initialize(NodeManagerConfig* pNodeConfig);

private:
    static bool s_typeNodesCreated;
};

} // End namespace for the UA information model http://opcfoundation.org/UA/

#endif // #ifndef __OPCUA_SELECTIONLISTTYPE_H__

