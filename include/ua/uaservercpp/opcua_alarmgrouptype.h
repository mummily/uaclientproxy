/******************************************************************************
** opcua_alarmgrouptype.h
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

#ifndef __OPCUA_ALARMGROUPTYPE_H__
#define __OPCUA_ALARMGROUPTYPE_H__

#include "opcua_foldertype.h"
#include "basenodes.h"
#include "opcua_identifiers.h"
#include "opcua_propertytype.h"
#include "uaargument.h"
#include "uatimezonedatatype.h"

// Namespace for the UA information model http://opcfoundation.org/UA/
namespace OpcUa {

class AlarmConditionType;
class ConditionVariableType;
class PropertyType;
class TwoStateVariableType;

/** @brief Class implementing the UaObject interface for the AlarmGroupType.
 *
 * OPC UA Objects are used to represent systems, system components, real-world objects and software
 * objects. They have the NodeClass @ref L3UaNodeClassObject. The detailed description of Objects and their attributes
 * can be found in the general description of the @ref L3UaNodeClassObject node class.
 *
 *  **Object members of the AlarmGroupType:**
 *
 *  Browse Name                | TypeDefinition     | Modelling Rule      | See Also
 *  ---------------------------|--------------------|---------------------|---------
 *  \<AlarmConditionInstance\> | AlarmConditionType | OptionalPlaceholder | &nbsp;
 *
 */
class SERVER_CORE_EXPORT AlarmGroupType:
    public OpcUa::FolderType
{
    UA_DISABLE_COPY(AlarmGroupType);
protected:
    virtual ~AlarmGroupType();
public:
    // construction / destruction
    AlarmGroupType(const UaNodeId& nodeId, UaObject* pInstanceDeclarationObject, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    AlarmGroupType(const UaNodeId& nodeId, const UaString& name, OpcUa_UInt16 browseNameNameSpaceIndex, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    AlarmGroupType(
        UaBase::Object*    pBaseNode,
        XmlUaNodeFactoryManager*   pFactory,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);
    static void createTypes();
    static void clearStaticMembers();

    virtual UaNodeId       typeDefinitionId() const;


// Add placeholders
    virtual UaStatus addAlarmConditionInstance_Placeholder(OpcUa::AlarmConditionType *pAlarmConditionInstance_Placeholder);

    // NodeAccessInfo management
    virtual void useAccessInfoFromType();
    void useAccessInfoFromInstance(AlarmGroupType *pInstance);

protected:
    // Object nodes
    // Object AlarmConditionInstance_Placeholder
    static OpcUa::AlarmConditionType*  s_pAlarmConditionInstance_Placeholder;



private:
    void initialize();

private:
    static bool s_typeNodesCreated;
};

} // End namespace for the UA information model http://opcfoundation.org/UA/

#endif // #ifndef __OPCUAALARMGROUPTYPE_H__


