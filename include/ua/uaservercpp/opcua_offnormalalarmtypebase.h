/******************************************************************************
** opcua_offnormalalarmtypebase.h
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

#ifndef __OPCUA_OFFNORMALALARMTYPEBASE_H__
#define __OPCUA_OFFNORMALALARMTYPEBASE_H__

#include "opcua_discretealarmtype.h"
#include "basenodes.h"
#include "opcua_identifiers.h"
#include "opcua_propertytype.h"

// Namespace for the UA information model http://opcfoundation.org/UA/
namespace OpcUa {

class OffNormalAlarmTypeBase;
class PropertyType;

/** Generated event data class for a OffNormalAlarmType.
 *
 *  This class contains the auto generated code for the object type OffNormalAlarmType
 *  providing UaEventData interface for the access to event data containing the current state of the
 *  condition for events sent to the client. The class is used for condition events if the condition has
 *  no nodes in the address space or for condition branches created as snapshot of the main branch.
 *
 *  **Event Fields of the OffNormalAlarmType:**
 *
 *  Browse Name | DataType | TypeDefinition | Modelling Rule | See Also
 *  ------------|----------|----------------|----------------|-----------------------------------------
 *  NormalState | NodeId   | PropertyType   | Mandatory      | \ref getNormalState, \ref setNormalState

 *  A specialization of the DiscreteAlarmType intended to represent a discrete
 *  Condition that is considered to be not normal.
 *
 *  This subtype is usually used to indicate that a discrete value is in an Alarm
 *  state, it is active as long as a non-normal value is present.
 *
 *  See also \ref Doc_OpcUa_OffNormalAlarmType for a documentation of the complete Information Model.
 */
class SERVER_CORE_EXPORT OffNormalAlarmTypeData:
    public OpcUa::DiscreteAlarmTypeData
{
    UA_DISABLE_COPY(OffNormalAlarmTypeData);
protected:
    virtual ~OffNormalAlarmTypeData();
public:
    OffNormalAlarmTypeData();
    void initializeAsBranch(OffNormalAlarmTypeBase* pCondition);
    void initializeAsBranch(OffNormalAlarmTypeData* pConditionData);
    virtual void getFieldData(OpcUa_UInt32 index, Session* pSession, OpcUa_Variant& data);
    // NormalState
    void setNormalState(const UaNodeId& NormalState);
    void setNormalStateStatus(OpcUa_StatusCode status);
    UaNodeId getNormalState();
    virtual void getNormalStateValue(Session* pSession, OpcUa_Variant& value);


private:
    void initialize();

private:
    UaObjectPointerArray<UaVariant> m_FieldValues;
};


/** Generated base class for a OffNormalAlarmType.
 *
 *  This class contains the auto generated code for the object type OffNormalAlarmType
 *  representing an OPC UA condition type. This class is used to create the condition type and to
 *  create and represent the condition object in the server address space. It provides also the UaEventData
 *  interface for the access to event data containing the current state of the condition for events sent to
 *  the client.
 *
 *  **Variable members of the OffNormalAlarmType:**
 *
 *  Browse Name | DataType | TypeDefinition | Modelling Rule | See Also
 *  ------------|----------|----------------|----------------|-----------------------------------------
 *  NormalState | NodeId   | PropertyType   | Mandatory      | \ref getNormalState, \ref setNormalState
 *
 *
 *  A specialization of the DiscreteAlarmType intended to represent a discrete
 *  Condition that is considered to be not normal.
 *
 *  This subtype is usually used to indicate that a discrete value is in an Alarm
 *  state, it is active as long as a non-normal value is present.
 *
 *  See also \ref Doc_OpcUa_OffNormalAlarmType for a documentation of the complete Information Model.
 */
class SERVER_CORE_EXPORT OffNormalAlarmTypeBase:
    public OpcUa::DiscreteAlarmType
{
    friend class OffNormalAlarmTypeData;
    UA_DISABLE_COPY(OffNormalAlarmTypeBase);
protected:
    // destruction
    virtual ~OffNormalAlarmTypeBase();
public:
    // construction
    OffNormalAlarmTypeBase(const UaNodeId& nodeId, UaObject* pInstanceDeclarationObject, NodeManagerConfig* pNodeConfig, const UaNodeId& sourceNode, const UaString& sourceName, UaMutexRefCounted* pSharedMutex = NULL);
    OffNormalAlarmTypeBase(const UaNodeId& nodeId, const UaString& name, OpcUa_UInt16 browseNameNameSpaceIndex, NodeManagerConfig* pNodeConfig, const UaNodeId& sourceNode, const UaString& sourceName, UaMutexRefCounted* pSharedMutex = NULL);
    OffNormalAlarmTypeBase(
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


    // NormalState
    virtual void setNormalState(const UaNodeId& NormalState);
    virtual UaNodeId getNormalState() const;
    virtual void setNormalStateStatus(OpcUa_StatusCode status);
    virtual void getNormalStateValue(Session* pSession, UaVariant& value);

    virtual OpcUa::PropertyType* getNormalStateNode();

    // NodeAccessInfo management
    virtual void useAccessInfoFromType();
    void useAccessInfoFromInstance(OffNormalAlarmTypeBase *pInstance);

    virtual UaStatus triggerEvent(
        const UaDateTime&   time,
        const UaDateTime&   receiveTime,
        const UaByteString& eventId);

    virtual void getOffNormalAlarmTypeOptionalFieldData(OpcUa_UInt32 index, Session* pSession, OpcUa_Variant& data);

protected:
    // Variable nodes
    // Variable NormalState
    static OpcUa::PropertyType*  s_pNormalState;
    OpcUa::PropertyType*  m_pNormalState;



private:
    void initialize();
    void createChildren();

private:
    static bool                                 s_typeNodesCreated;
    static std::map<OpcUa_UInt32, OpcUa_UInt32> s_OffNormalAlarmTypeDataFields;
    UaObjectPointerArray<UaVariant>             m_FieldValues;
};

} // End namespace for the UA information model http://opcfoundation.org/UA/

#endif // #ifndef __OPCUAOFFNORMALALARMTYPEBASE_H__

