/******************************************************************************
** opcua_alarmratevariabletype.h
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

#ifndef __OPCUA_ALARMRATEVARIABLETYPE_H__
#define __OPCUA_ALARMRATEVARIABLETYPE_H__

#include "opcua_basedatavariabletype.h"
#include "opcua_identifiers.h"

// Namespace for the UA information model http://opcfoundation.org/UA/
namespace OpcUa {

class PropertyType;

/** Implements OPC UA Variables of the type AlarmRateVariableType
 *
 *  **Variable members of the AlarmRateVariableType:**
 *
 *  Browse Name | DataType | TypeDefinition | Modelling Rule | See Also
 *  ------------|----------|----------------|----------------|---------------------------
 *  Rate        | UInt16   | PropertyType   | Mandatory      | \ref getRate, \ref setRate
 *
 */
class SERVER_CORE_EXPORT AlarmRateVariableType:
    public OpcUa::BaseDataVariableType
{
    UA_DISABLE_COPY(AlarmRateVariableType);
protected:
    virtual ~AlarmRateVariableType();
public:
    AlarmRateVariableType(
        UaNode*            pParentNode,
        UaVariable*        pInstanceDeclarationVariable,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);
    AlarmRateVariableType(
        const UaNodeId&    nodeId,
        const UaString&    name,
        OpcUa_UInt16       browseNameNameSpaceIndex,
        const UaVariant&   initialValue,
        OpcUa_Byte         accessLevel,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);
    AlarmRateVariableType(
        UaBase::Variable*  pBaseNode,
        XmlUaNodeFactoryManager*   pFactory,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);

    static void createTypes();
    static void clearStaticMembers();

    virtual UaNodeId       typeDefinitionId() const;

    virtual void setRate(OpcUa_UInt16 Rate);
    virtual OpcUa_UInt16 getRate() const;

    virtual OpcUa::PropertyType* getRateNode();
    virtual const OpcUa::PropertyType* getRateNode() const;

    // NodeAccessInfo management
    virtual void useAccessInfoFromType();
    void useAccessInfoFromInstance(AlarmRateVariableType *pInstance);

protected:
    // Variable nodes
    // Variable Rate
    static OpcUa::PropertyType*  s_pRate;
    OpcUa::PropertyType*  m_pRate;


private:
    void initialize(NodeManagerConfig* pNodeConfig);

private:
    static bool s_typeNodesCreated;
};

} // End namespace for the UA information model http://opcfoundation.org/UA/

#endif // #ifndef __OPCUA_ALARMRATEVARIABLETYPE_H__

