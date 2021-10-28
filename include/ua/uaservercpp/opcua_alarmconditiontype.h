/******************************************************************************
** opcua_alarmconditiontype.h
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
#ifndef __OPCUA_ALARMCONDITIONTYPE_H__
#define __OPCUA_ALARMCONDITIONTYPE_H__

#include "opcua_acknowledgeableconditiontype.h"
#include "opcua_identifiers.h"
#include "opcua_alarmconditiontypebase.h"

// Namespace for the UA information model http://opcfoundation.org/UA/
namespace OpcUa {


/** @brief Class implementing the UaObject interface for the AlarmConditionType.
 *
 * OPC UA Objects are used to represent systems, system components, real-world objects and software
 * objects. They have the NodeClass @ref L3UaNodeClassObject. The detailed description of Objects and their attributes
 * can be found in the general description of the @ref L3UaNodeClassObject node class.
 *
 *  **Object members of the AlarmConditionType:**
 *
 *  Browse Name    | TypeDefinition          | Modelling Rule      | See Also
 *  ---------------|-------------------------|---------------------|-----------------------------------------------------------------
 *  \<AlarmGroup\> | AlarmGroupType          | OptionalPlaceholder | &nbsp;
 *  FirstInGroup   | AlarmGroupType          | Optional            | \ref AlarmConditionTypeBase::getFirstInGroup "getFirstInGroup"
 *  ShelvingState  | ShelvedStateMachineType | Optional            | \ref AlarmConditionTypeBase::getShelvingState "getShelvingState"
 *
 *  **Variable members of the AlarmConditionType:**
 *
 *  Browse Name         | DataType      | TypeDefinition       | Modelling Rule | See Also
 *  --------------------|---------------|----------------------|----------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------
 *  ActiveState         | LocalizedText | TwoStateVariableType | Mandatory      | \ref AlarmConditionTypeBase::getActiveState "getActiveState", \ref AlarmConditionTypeBase::setActiveState "setActiveState"
 *  AudibleEnabled      | Boolean       | PropertyType         | Optional       | \ref AlarmConditionTypeBase::getAudibleEnabled "getAudibleEnabled", \ref AlarmConditionTypeBase::setAudibleEnabled "setAudibleEnabled"
 *  AudibleSound        | AudioDataType | AudioVariableType    | Optional       | \ref AlarmConditionTypeBase::getAudibleSound "getAudibleSound", \ref AlarmConditionTypeBase::setAudibleSound "setAudibleSound"
 *  EnabledState        | LocalizedText | TwoStateVariableType | Mandatory      | \ref AlarmConditionTypeBase::getEnabledState "getEnabledState", \ref AlarmConditionTypeBase::setEnabledState "setEnabledState"
 *  FirstInGroupFlag    | Boolean       | PropertyType         | Optional       | \ref AlarmConditionTypeBase::getFirstInGroupFlag "getFirstInGroupFlag", \ref AlarmConditionTypeBase::setFirstInGroupFlag "setFirstInGroupFlag"
 *  InputNode           | NodeId        | PropertyType         | Mandatory      | \ref AlarmConditionTypeBase::getInputNode "getInputNode", \ref AlarmConditionTypeBase::setInputNode "setInputNode"
 *  LatchedState        | LocalizedText | TwoStateVariableType | Optional       | \ref AlarmConditionTypeBase::getLatchedState "getLatchedState", \ref AlarmConditionTypeBase::setLatchedState "setLatchedState"
 *  MaxTimeShelved      | Duration      | PropertyType         | Optional       | \ref AlarmConditionTypeBase::getMaxTimeShelved "getMaxTimeShelved", \ref AlarmConditionTypeBase::setMaxTimeShelved "setMaxTimeShelved"
 *  OffDelay            | Duration      | PropertyType         | Optional       | \ref AlarmConditionTypeBase::getOffDelay "getOffDelay", \ref AlarmConditionTypeBase::setOffDelay "setOffDelay"
 *  OnDelay             | Duration      | PropertyType         | Optional       | \ref AlarmConditionTypeBase::getOnDelay "getOnDelay", \ref AlarmConditionTypeBase::setOnDelay "setOnDelay"
 *  OutOfServiceState   | LocalizedText | TwoStateVariableType | Optional       | \ref AlarmConditionTypeBase::getOutOfServiceState "getOutOfServiceState", \ref AlarmConditionTypeBase::setOutOfServiceState "setOutOfServiceState"
 *  ReAlarmRepeatCount  | Int16         | PropertyType         | Optional       | \ref AlarmConditionTypeBase::getReAlarmRepeatCount "getReAlarmRepeatCount", \ref AlarmConditionTypeBase::setReAlarmRepeatCount "setReAlarmRepeatCount"
 *  ReAlarmTime         | Duration      | PropertyType         | Optional       | \ref AlarmConditionTypeBase::getReAlarmTime "getReAlarmTime", \ref AlarmConditionTypeBase::setReAlarmTime "setReAlarmTime"
 *  SilenceState        | LocalizedText | TwoStateVariableType | Optional       | \ref AlarmConditionTypeBase::getSilenceState "getSilenceState", \ref AlarmConditionTypeBase::setSilenceState "setSilenceState"
 *  SuppressedOrShelved | Boolean       | PropertyType         | Mandatory      | \ref AlarmConditionTypeBase::getSuppressedOrShelved "getSuppressedOrShelved", \ref AlarmConditionTypeBase::setSuppressedOrShelved "setSuppressedOrShelved"
 *  SuppressedState     | LocalizedText | TwoStateVariableType | Optional       | \ref AlarmConditionTypeBase::getSuppressedState "getSuppressedState", \ref AlarmConditionTypeBase::setSuppressedState "setSuppressedState"
 *
 *  **Method members of the AlarmConditionType:**
 *
 *  Browse Name            | Modelling Rule
 *  -----------------------|---------------
 *  \ref PlaceInService    | Optional
 *  \ref RemoveFromService | Optional
 *  \ref Reset             | Optional
 *  \ref Silence           | Optional
 *  \ref Suppress          | Optional
 *  \ref Unsuppress        | Optional
 *
 *  An abstract type that extends the AcknowledgeableConditionType by introducing
 *  an ActiveState, SuppressedState and ShelvingState.
 *
 *  The AlarmConditionType inherits all Properties of the
 *  AcknowledgeableConditionType. The following states are substates of the TRUE
 *  EnabledState.
 *
 *  See also \ref Doc_OpcUa_AlarmConditionType for a documentation of the complete Information Model.
 */
class SERVER_CORE_EXPORT AlarmConditionType:
    public AlarmConditionTypeBase
{
    UA_DISABLE_COPY(AlarmConditionType);
protected:
    // destruction
    virtual ~AlarmConditionType();
public:
    // construction
    AlarmConditionType(const UaNodeId& nodeId, UaObject* pInstanceDeclarationObject, NodeManagerConfig* pNodeConfig, const UaNodeId& sourceNode, const UaString& sourceName, UaMutexRefCounted* pSharedMutex = NULL);
    AlarmConditionType(const UaNodeId& nodeId, const UaString& name, OpcUa_UInt16 browseNameNameSpaceIndex, NodeManagerConfig* pNodeConfig, const UaNodeId& sourceNode, const UaString& sourceName, UaMutexRefCounted* pSharedMutex = NULL);
    AlarmConditionType(
        UaBase::Object*    pBaseNode,
        XmlUaNodeFactoryManager*   pFactory,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);

    static void addActiveStateLocale(const UaLocalizedText& falseName, const UaLocalizedText& trueName);
    static void addSuppressedStateLocale(const UaLocalizedText& falseName, const UaLocalizedText& trueName);
    static void addOutOfServiceStateLocale(const UaLocalizedText& falseName, const UaLocalizedText& trueName);
    static void addSilenceStateLocale(const UaLocalizedText& falseName, const UaLocalizedText& trueName);
    static void addLatchedStateLocale(const UaLocalizedText& falseName, const UaLocalizedText& trueName);

    void setShelvedState(ShelvedStateMachineType::ShelvedState state);
    ShelvedStateMachineType::ShelvedState getShelvedState();

    virtual void getEnabledState_EffectiveDisplayNameValue(Session* pSession, OpcUa_Variant& value);
    static void createTypes();
    static void clearStaticMembers();

    // Overwrite base class to add initialization
    virtual void setSuppressedState(OpcUa_Boolean suppressedState);
    virtual void createShelvedStateMachine();
    virtual void setActiveState(OpcUa_Boolean activeState);
    virtual void setSilenceState(OpcUa_Boolean silenceState);
    virtual void setOutOfServiceState(OpcUa_Boolean outOfServiceState);
    virtual void setLatchedState(OpcUa_Boolean latchedState);

    // UaAlarmConditionType method PlaceInService
    virtual UaStatus PlaceInService(
        const ServiceContext& serviceContext);
    // UaAlarmConditionType method RemoveFromService
    virtual UaStatus RemoveFromService(
        const ServiceContext& serviceContext);
    // UaAlarmConditionType method Reset
    virtual UaStatus Reset(
        const ServiceContext& serviceContext);
    // UaAlarmConditionType method Silence
    virtual UaStatus Silence(
        const ServiceContext& serviceContext);
    // UaAlarmConditionType method Suppress
    virtual UaStatus Suppress(
        const ServiceContext& serviceContext);
    // UaAlarmConditionType method Unsuppress
    virtual UaStatus Unsuppress(
        const ServiceContext& serviceContext);

protected:
    static TwoStateDisplayNames* s_pActiveStateDisplayNames;

private:
    void initialize();

private:
    static bool                  s_typeNodesCreated;
    static TwoStateDisplayNames* s_pSuppressedStateDisplayNames;
    static TwoStateDisplayNames* s_pOutOfServiceStateDisplayNames;
    static TwoStateDisplayNames* s_pSilenceStateDisplayNames;
    static TwoStateDisplayNames* s_pLatchedStateDisplayNames;
};

} // End namespace for the UA information model http://opcfoundation.org/UA/

#endif // #ifndef __OPCUAALARMCONDITIONTYPE_H__

