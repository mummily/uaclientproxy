/******************************************************************************
** opcua_discrepancyalarmtype.h
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

#ifndef __OPCUA_DISCREPANCYALARMTYPE_H__
#define __OPCUA_DISCREPANCYALARMTYPE_H__

#include "opcua_alarmconditiontype.h"
#include "basenodes.h"
#include "opcua_identifiers.h"
#include "opcua_propertytype.h"

// Namespace for the UA information model http://opcfoundation.org/UA/
namespace OpcUa {

class DiscrepancyAlarmType;
class PropertyType;

/** Generated event data class for a DiscrepancyAlarmType.
 *
 *  This class contains the auto generated code for the object type DiscrepancyAlarmType
 *  providing UaEventData interface for the access to event data containing the current state of the
 *  condition for events sent to the client. The class is used for condition events if the condition has
 *  no nodes in the address space or for condition branches created as snapshot of the main branch.
 *
 *  **Event Fields of the DiscrepancyAlarmType:**
 *
 *  Browse Name     | DataType | TypeDefinition | Modelling Rule | See Also
 *  ----------------|----------|----------------|----------------|-------------------------------------------------
 *  ExpectedTime    | Duration | PropertyType   | Mandatory      | \ref getExpectedTime, \ref setExpectedTime
 *  TargetValueNode | NodeId   | PropertyType   | Mandatory      | \ref getTargetValueNode, \ref setTargetValueNode
 *  Tolerance       | Double   | PropertyType   | Optional       | \ref getTolerance, \ref setTolerance

 */
class SERVER_CORE_EXPORT DiscrepancyAlarmTypeData:
    public OpcUa::AlarmConditionTypeData
{
    UA_DISABLE_COPY(DiscrepancyAlarmTypeData);
protected:
    virtual ~DiscrepancyAlarmTypeData();
public:
    DiscrepancyAlarmTypeData();
    void initializeAsBranch(DiscrepancyAlarmType* pCondition);
    void initializeAsBranch(DiscrepancyAlarmTypeData* pConditionData);
    virtual void getFieldData(OpcUa_UInt32 index, Session* pSession, OpcUa_Variant& data);
    // ExpectedTime
    void setExpectedTime(OpcUa_Double ExpectedTime);
    void setExpectedTimeStatus(OpcUa_StatusCode status);
    OpcUa_Double getExpectedTime();
    virtual void getExpectedTimeValue(Session* pSession, OpcUa_Variant& value);
    // TargetValueNode
    void setTargetValueNode(const UaNodeId& TargetValueNode);
    void setTargetValueNodeStatus(OpcUa_StatusCode status);
    UaNodeId getTargetValueNode();
    virtual void getTargetValueNodeValue(Session* pSession, OpcUa_Variant& value);
    // Tolerance
    void setTolerance(OpcUa_Double Tolerance);
    void setToleranceStatus(OpcUa_StatusCode status);
    OpcUa_Double getTolerance();
    virtual void getToleranceValue(Session* pSession, OpcUa_Variant& value);


private:
    void initialize();

private:
    UaObjectPointerArray<UaVariant> m_FieldValues;
};


/** @brief Class implementing the UaObject interface for the DiscrepancyAlarmType.
 *
 * OPC UA Objects are used to represent systems, system components, real-world objects and software
 * objects. They have the NodeClass @ref L3UaNodeClassObject. The detailed description of Objects and their attributes
 * can be found in the general description of the @ref L3UaNodeClassObject node class.
 *
 *  **Variable members of the DiscrepancyAlarmType:**
 *
 *  Browse Name     | DataType | TypeDefinition | Modelling Rule | See Also
 *  ----------------|----------|----------------|----------------|-----------------------------------------------------------------------------------------------------------------------------------------------
 *  ExpectedTime    | Duration | PropertyType   | Mandatory      | \ref DiscrepancyAlarmType::getExpectedTime "getExpectedTime", \ref DiscrepancyAlarmType::setExpectedTime "setExpectedTime"
 *  TargetValueNode | NodeId   | PropertyType   | Mandatory      | \ref DiscrepancyAlarmType::getTargetValueNode "getTargetValueNode", \ref DiscrepancyAlarmType::setTargetValueNode "setTargetValueNode"
 *  Tolerance       | Double   | PropertyType   | Optional       | \ref DiscrepancyAlarmType::getTolerance "getTolerance", \ref DiscrepancyAlarmType::setTolerance "setTolerance"
 *
 */
class SERVER_CORE_EXPORT DiscrepancyAlarmType:
    public OpcUa::AlarmConditionType
{
    friend class DiscrepancyAlarmTypeData;
    UA_DISABLE_COPY(DiscrepancyAlarmType);
protected:
    // destruction
    virtual ~DiscrepancyAlarmType();
public:
    // construction
    DiscrepancyAlarmType(const UaNodeId& nodeId, UaObject* pInstanceDeclarationObject, NodeManagerConfig* pNodeConfig, const UaNodeId& sourceNode, const UaString& sourceName, UaMutexRefCounted* pSharedMutex = NULL);
    DiscrepancyAlarmType(const UaNodeId& nodeId, const UaString& name, OpcUa_UInt16 browseNameNameSpaceIndex, NodeManagerConfig* pNodeConfig, const UaNodeId& sourceNode, const UaString& sourceName, UaMutexRefCounted* pSharedMutex = NULL);
    DiscrepancyAlarmType(
        UaBase::Object*    pBaseNode,
        XmlUaNodeFactoryManager*   pFactory,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);

    static void createTypes();
    static void clearStaticMembers();
    virtual UaNodeId typeDefinitionId() const;
    static void registerEventFields();
    static OpcUa_UInt32 registerOptionalEventFields(const UaString& fieldName);
    virtual void getFieldData(OpcUa_UInt32 index, Session* pSession, OpcUa_Variant& data);
    void clearFieldData();
    UaNodeId createBranch();


    // ExpectedTime
    virtual void setExpectedTime(OpcUa_Double ExpectedTime);
    virtual OpcUa_Double getExpectedTime() const;
    virtual void setExpectedTimeStatus(OpcUa_StatusCode status);
    virtual void getExpectedTimeValue(Session* pSession, UaVariant& value);
    // TargetValueNode
    virtual void setTargetValueNode(const UaNodeId& TargetValueNode);
    virtual UaNodeId getTargetValueNode() const;
    virtual void setTargetValueNodeStatus(OpcUa_StatusCode status);
    virtual void getTargetValueNodeValue(Session* pSession, UaVariant& value);
    // Tolerance
    virtual void setTolerance(OpcUa_Double Tolerance);
    virtual OpcUa_Double getTolerance() const;
    virtual void setToleranceStatus(OpcUa_StatusCode status);
    virtual void getToleranceValue(Session* pSession, UaVariant& value);

    virtual OpcUa::PropertyType* getExpectedTimeNode();
    virtual const OpcUa::PropertyType* getExpectedTimeNode() const;
    virtual OpcUa::PropertyType* getTargetValueNodeNode();
    virtual const OpcUa::PropertyType* getTargetValueNodeNode() const;
    virtual OpcUa::PropertyType* getToleranceNode();
    virtual const OpcUa::PropertyType* getToleranceNode() const;

    // NodeAccessInfo management
    virtual void useAccessInfoFromType();
    void useAccessInfoFromInstance(DiscrepancyAlarmType *pInstance);

    virtual UaStatus triggerEvent(
        const UaDateTime&   time,
        const UaDateTime&   receiveTime,
        const UaByteString& eventId);

    virtual void getDiscrepancyAlarmTypeOptionalFieldData(OpcUa_UInt32 index, Session* pSession, OpcUa_Variant& data);

protected:
    // Variable nodes
    // Variable ExpectedTime
    static OpcUa::PropertyType*  s_pExpectedTime;
    OpcUa::PropertyType*  m_pExpectedTime;
    // Variable TargetValueNode
    static OpcUa::PropertyType*  s_pTargetValueNode;
    OpcUa::PropertyType*  m_pTargetValueNode;
    // Variable Tolerance
    static OpcUa::PropertyType*  s_pTolerance;
    OpcUa::PropertyType*  m_pTolerance;



private:
    void initialize();
    void createChildren();

private:
    static bool                                 s_typeNodesCreated;
    static std::map<OpcUa_UInt32, OpcUa_UInt32> s_DiscrepancyAlarmTypeDataFields;
    UaObjectPointerArray<UaVariant>             m_FieldValues;
};

} // End namespace for the UA information model http://opcfoundation.org/UA/

#endif // #ifndef __OPCUADISCREPANCYALARMTYPE_H__

