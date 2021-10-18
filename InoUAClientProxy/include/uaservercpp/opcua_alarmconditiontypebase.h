/******************************************************************************
** opcua_alarmconditiontypebase.h
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

#ifndef __OPCUA_ALARMCONDITIONTYPEBASE_H__
#define __OPCUA_ALARMCONDITIONTYPEBASE_H__

#include "opcua_acknowledgeableconditiontype.h"
#include "basenodes.h"
#include "opcua_identifiers.h"
#include "opcua_propertytype.h"
#include "opcua_twostatevariabletype.h"
#include "uaargument.h"
#include "opcua_shelvedstatemachinetype.h"

// Namespace for the UA information model http://opcfoundation.org/UA/
namespace OpcUa {

class AlarmConditionTypeBase;
class AlarmGroupType;
class AudioVariableType;
class FiniteStateVariableType;
class FiniteTransitionVariableType;
class PropertyType;
class TwoStateVariableType;

/** Generated event data class for a AlarmConditionType.
 *
 *  This class contains the auto generated code for the object type AlarmConditionType
 *  providing UaEventData interface for the access to event data containing the current state of the
 *  condition for events sent to the client. The class is used for condition events if the condition has
 *  no nodes in the address space or for condition branches created as snapshot of the main branch.
 *
 *  **Event Fields of the AlarmConditionType:**
 *
 *  Browse Name         | DataType      | TypeDefinition       | Modelling Rule | See Also
 *  --------------------|---------------|----------------------|----------------|---------------------------------------------------------
 *  ActiveState         | LocalizedText | TwoStateVariableType | Mandatory      | \ref getActiveState, \ref setActiveState
 *  AudibleEnabled      | Boolean       | PropertyType         | Optional       | \ref getAudibleEnabled, \ref setAudibleEnabled
 *  AudibleSound        | AudioDataType | AudioVariableType    | Optional       | \ref getAudibleSound, \ref setAudibleSound
 *  FirstInGroupFlag    | Boolean       | PropertyType         | Optional       | \ref getFirstInGroupFlag, \ref setFirstInGroupFlag
 *  InputNode           | NodeId        | PropertyType         | Mandatory      | \ref getInputNode, \ref setInputNode
 *  LatchedState        | LocalizedText | TwoStateVariableType | Optional       | \ref getLatchedState, \ref setLatchedState
 *  MaxTimeShelved      | Duration      | PropertyType         | Optional       | \ref getMaxTimeShelved, \ref setMaxTimeShelved
 *  OffDelay            | Duration      | PropertyType         | Optional       | \ref getOffDelay, \ref setOffDelay
 *  OnDelay             | Duration      | PropertyType         | Optional       | \ref getOnDelay, \ref setOnDelay
 *  OutOfServiceState   | LocalizedText | TwoStateVariableType | Optional       | \ref getOutOfServiceState, \ref setOutOfServiceState
 *  ReAlarmRepeatCount  | Int16         | PropertyType         | Optional       | \ref getReAlarmRepeatCount, \ref setReAlarmRepeatCount
 *  ReAlarmTime         | Duration      | PropertyType         | Optional       | \ref getReAlarmTime, \ref setReAlarmTime
 *  SilenceState        | LocalizedText | TwoStateVariableType | Optional       | \ref getSilenceState, \ref setSilenceState
 *  SuppressedOrShelved | Boolean       | PropertyType         | Mandatory      | \ref getSuppressedOrShelved, \ref setSuppressedOrShelved
 *  SuppressedState     | LocalizedText | TwoStateVariableType | Optional       | \ref getSuppressedState, \ref setSuppressedState

 *  An abstract type that extends the AcknowledgeableConditionType by introducing
 *  an ActiveState, SuppressedState and ShelvingState.
 *
 *  The AlarmConditionType inherits all Properties of the
 *  AcknowledgeableConditionType. The following states are substates of the TRUE
 *  EnabledState.
 *
 *  See also \ref Doc_OpcUa_AlarmConditionType for a documentation of the complete Information Model.
 */
class SERVER_CORE_EXPORT AlarmConditionTypeData:
    public OpcUa::AcknowledgeableConditionTypeData
{
    UA_DISABLE_COPY(AlarmConditionTypeData);
protected:
    virtual ~AlarmConditionTypeData();
public:
    AlarmConditionTypeData();
    void initializeAsBranch(AlarmConditionTypeBase* pCondition);
    void initializeAsBranch(AlarmConditionTypeData* pConditionData);
    virtual void getFieldData(OpcUa_UInt32 index, Session* pSession, OpcUa_Variant& data);
    // ActiveState
    virtual void getActiveStateValue(Session* pSession, OpcUa_Variant& value);
    void setActiveState(OpcUa_Boolean activeState);
    void setActiveStateStatus(OpcUa_StatusCode status);
    OpcUa_Boolean getActiveState();
    void setActiveState_EffectiveDisplayName(const UaLocalizedText& EffectiveDisplayName);
    void setActiveState_EffectiveDisplayNameStatus(OpcUa_StatusCode status);
    UaLocalizedText getActiveState_EffectiveDisplayName();
    virtual void getActiveState_EffectiveDisplayNameValue(Session* pSession, OpcUa_Variant& value);
    void setActiveState_EffectiveTransitionTime(const UaDateTime& EffectiveTransitionTime);
    void setActiveState_EffectiveTransitionTimeStatus(OpcUa_StatusCode status);
    UaDateTime getActiveState_EffectiveTransitionTime();
    virtual void getActiveState_EffectiveTransitionTimeValue(Session* pSession, OpcUa_Variant& value);
    virtual void getActiveState_IdValue(Session* pSession, OpcUa_Variant& value);
    void setActiveState_TransitionTime(const UaDateTime& TransitionTime);
    void setActiveState_TransitionTimeStatus(OpcUa_StatusCode status);
    UaDateTime getActiveState_TransitionTime();
    virtual void getActiveState_TransitionTimeValue(Session* pSession, OpcUa_Variant& value);
    // AudibleEnabled
    void setAudibleEnabled(OpcUa_Boolean AudibleEnabled);
    void setAudibleEnabledStatus(OpcUa_StatusCode status);
    OpcUa_Boolean getAudibleEnabled();
    virtual void getAudibleEnabledValue(Session* pSession, OpcUa_Variant& value);
    // AudibleSound
    void setAudibleSound(UaByteString& AudibleSound);
    void setAudibleSoundStatus(OpcUa_StatusCode status);
    UaByteString getAudibleSound();
    virtual void getAudibleSoundValue(Session* pSession, OpcUa_Variant& value);
    // EnabledState already defined by base class
    // FirstInGroup
    // FirstInGroupFlag
    void setFirstInGroupFlag(OpcUa_Boolean FirstInGroupFlag);
    void setFirstInGroupFlagStatus(OpcUa_StatusCode status);
    OpcUa_Boolean getFirstInGroupFlag();
    virtual void getFirstInGroupFlagValue(Session* pSession, OpcUa_Variant& value);
    // InputNode
    void setInputNode(const UaNodeId& InputNode);
    void setInputNodeStatus(OpcUa_StatusCode status);
    UaNodeId getInputNode();
    virtual void getInputNodeValue(Session* pSession, OpcUa_Variant& value);
    // LatchedState
    virtual void getLatchedStateValue(Session* pSession, OpcUa_Variant& value);
    void setLatchedState(OpcUa_Boolean latchedState);
    void setLatchedStateStatus(OpcUa_StatusCode status);
    OpcUa_Boolean getLatchedState();
    virtual void getLatchedState_IdValue(Session* pSession, OpcUa_Variant& value);
    void setLatchedState_TransitionTime(const UaDateTime& TransitionTime);
    void setLatchedState_TransitionTimeStatus(OpcUa_StatusCode status);
    UaDateTime getLatchedState_TransitionTime();
    virtual void getLatchedState_TransitionTimeValue(Session* pSession, OpcUa_Variant& value);
    // MaxTimeShelved
    void setMaxTimeShelved(OpcUa_Double MaxTimeShelved);
    void setMaxTimeShelvedStatus(OpcUa_StatusCode status);
    OpcUa_Double getMaxTimeShelved();
    virtual void getMaxTimeShelvedValue(Session* pSession, OpcUa_Variant& value);
    // OffDelay
    void setOffDelay(OpcUa_Double OffDelay);
    void setOffDelayStatus(OpcUa_StatusCode status);
    OpcUa_Double getOffDelay();
    virtual void getOffDelayValue(Session* pSession, OpcUa_Variant& value);
    // OnDelay
    void setOnDelay(OpcUa_Double OnDelay);
    void setOnDelayStatus(OpcUa_StatusCode status);
    OpcUa_Double getOnDelay();
    virtual void getOnDelayValue(Session* pSession, OpcUa_Variant& value);
    // OutOfServiceState
    virtual void getOutOfServiceStateValue(Session* pSession, OpcUa_Variant& value);
    void setOutOfServiceState(OpcUa_Boolean outOfServiceState);
    void setOutOfServiceStateStatus(OpcUa_StatusCode status);
    OpcUa_Boolean getOutOfServiceState();
    virtual void getOutOfServiceState_IdValue(Session* pSession, OpcUa_Variant& value);
    void setOutOfServiceState_TransitionTime(const UaDateTime& TransitionTime);
    void setOutOfServiceState_TransitionTimeStatus(OpcUa_StatusCode status);
    UaDateTime getOutOfServiceState_TransitionTime();
    virtual void getOutOfServiceState_TransitionTimeValue(Session* pSession, OpcUa_Variant& value);
    // ReAlarmRepeatCount
    void setReAlarmRepeatCount(OpcUa_Int16 ReAlarmRepeatCount);
    void setReAlarmRepeatCountStatus(OpcUa_StatusCode status);
    OpcUa_Int16 getReAlarmRepeatCount();
    virtual void getReAlarmRepeatCountValue(Session* pSession, OpcUa_Variant& value);
    // ReAlarmTime
    void setReAlarmTime(OpcUa_Double ReAlarmTime);
    void setReAlarmTimeStatus(OpcUa_StatusCode status);
    OpcUa_Double getReAlarmTime();
    virtual void getReAlarmTimeValue(Session* pSession, OpcUa_Variant& value);
    // ShelvingState
// Addition to generated code begin (Added and removed methods)
    void setShelvedState(ShelvedStateMachineType::ShelvedState state);
    ShelvedStateMachineType::ShelvedState getShelvedState();
    UaLocalizedText getShelvingState_CurrentState();
    virtual void getShelvingState_CurrentStateValue(Session* pSession, OpcUa_Variant& value);
    UaNodeId getShelvingState_CurrentState_Id();
    virtual void getShelvingState_CurrentState_IdValue(Session* pSession, OpcUa_Variant& value);
    UaLocalizedText getShelvingState_LastTransition();
    virtual void getShelvingState_LastTransitionValue(Session* pSession, OpcUa_Variant& value);
    UaNodeId getShelvingState_LastTransition_Id();
    virtual void getShelvingState_LastTransition_IdValue(Session* pSession, OpcUa_Variant& value);
    UaDateTime getShelvingState_LastTransition_TransitionTime();
    virtual void getShelvingState_LastTransition_TransitionTimeValue(Session* pSession, OpcUa_Variant& value);
    void setShelvingState_UnshelveTime(OpcUa_Double UnshelveTime);
    OpcUa_Double getShelvingState_UnshelveTime();
    virtual void getShelvingState_UnshelveTimeValue(Session* pSession, OpcUa_Variant& value);
// Addition to generated code end
    // SilenceState
    virtual void getSilenceStateValue(Session* pSession, OpcUa_Variant& value);
    void setSilenceState(OpcUa_Boolean silenceState);
    void setSilenceStateStatus(OpcUa_StatusCode status);
    OpcUa_Boolean getSilenceState();
    virtual void getSilenceState_IdValue(Session* pSession, OpcUa_Variant& value);
    void setSilenceState_TransitionTime(const UaDateTime& TransitionTime);
    void setSilenceState_TransitionTimeStatus(OpcUa_StatusCode status);
    UaDateTime getSilenceState_TransitionTime();
    virtual void getSilenceState_TransitionTimeValue(Session* pSession, OpcUa_Variant& value);
    // SuppressedOrShelved
    void setSuppressedOrShelved(OpcUa_Boolean SuppressedOrShelved);
    void setSuppressedOrShelvedStatus(OpcUa_StatusCode status);
    OpcUa_Boolean getSuppressedOrShelved();
    virtual void getSuppressedOrShelvedValue(Session* pSession, OpcUa_Variant& value);
    // SuppressedState
    virtual void getSuppressedStateValue(Session* pSession, OpcUa_Variant& value);
    void setSuppressedState(OpcUa_Boolean suppressedState);
    void setSuppressedStateStatus(OpcUa_StatusCode status);
    OpcUa_Boolean getSuppressedState();
    virtual void getSuppressedState_IdValue(Session* pSession, OpcUa_Variant& value);
    void setSuppressedState_TransitionTime(const UaDateTime& TransitionTime);
    void setSuppressedState_TransitionTimeStatus(OpcUa_StatusCode status);
    UaDateTime getSuppressedState_TransitionTime();
    virtual void getSuppressedState_TransitionTimeValue(Session* pSession, OpcUa_Variant& value);


private:
    void initialize();

private:
    UaObjectPointerArray<UaVariant> m_FieldValues;
// Addition to generated code begin
    ShelvedStateMachineType::ShelvedState m_state;
// Addition to generated code end
};


/** Generated base class for a AlarmConditionType.
 *
 *  This class contains the auto generated code for the object type AlarmConditionType
 *  representing an OPC UA condition type. This class is used to create the condition type and to
 *  create and represent the condition object in the server address space. It provides also the UaEventData
 *  interface for the access to event data containing the current state of the condition for events sent to
 *  the client.
 *
 *  **Object members of the AlarmConditionType:**
 *
 *  Browse Name    | TypeDefinition          | Modelling Rule      | See Also
 *  ---------------|-------------------------|---------------------|----------------------
 *  \<AlarmGroup\> | AlarmGroupType          | OptionalPlaceholder | &nbsp;
 *  FirstInGroup   | AlarmGroupType          | Optional            | \ref getFirstInGroup
 *  ShelvingState  | ShelvedStateMachineType | Optional            | \ref getShelvingState
 *
 *  **Variable members of the AlarmConditionType:**
 *
 *  Browse Name         | DataType      | TypeDefinition       | Modelling Rule | See Also
 *  --------------------|---------------|----------------------|----------------|---------------------------------------------------------
 *  ActiveState         | LocalizedText | TwoStateVariableType | Mandatory      | \ref getActiveState, \ref setActiveState
 *  AudibleEnabled      | Boolean       | PropertyType         | Optional       | \ref getAudibleEnabled, \ref setAudibleEnabled
 *  AudibleSound        | AudioDataType | AudioVariableType    | Optional       | \ref getAudibleSound, \ref setAudibleSound
 *  FirstInGroupFlag    | Boolean       | PropertyType         | Optional       | \ref getFirstInGroupFlag, \ref setFirstInGroupFlag
 *  InputNode           | NodeId        | PropertyType         | Mandatory      | \ref getInputNode, \ref setInputNode
 *  LatchedState        | LocalizedText | TwoStateVariableType | Optional       | \ref getLatchedState, \ref setLatchedState
 *  MaxTimeShelved      | Duration      | PropertyType         | Optional       | \ref getMaxTimeShelved, \ref setMaxTimeShelved
 *  OffDelay            | Duration      | PropertyType         | Optional       | \ref getOffDelay, \ref setOffDelay
 *  OnDelay             | Duration      | PropertyType         | Optional       | \ref getOnDelay, \ref setOnDelay
 *  OutOfServiceState   | LocalizedText | TwoStateVariableType | Optional       | \ref getOutOfServiceState, \ref setOutOfServiceState
 *  ReAlarmRepeatCount  | Int16         | PropertyType         | Optional       | \ref getReAlarmRepeatCount, \ref setReAlarmRepeatCount
 *  ReAlarmTime         | Duration      | PropertyType         | Optional       | \ref getReAlarmTime, \ref setReAlarmTime
 *  SilenceState        | LocalizedText | TwoStateVariableType | Optional       | \ref getSilenceState, \ref setSilenceState
 *  SuppressedOrShelved | Boolean       | PropertyType         | Mandatory      | \ref getSuppressedOrShelved, \ref setSuppressedOrShelved
 *  SuppressedState     | LocalizedText | TwoStateVariableType | Optional       | \ref getSuppressedState, \ref setSuppressedState
 *
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
class SERVER_CORE_EXPORT AlarmConditionTypeBase:
    public OpcUa::AcknowledgeableConditionType
{
    friend class AlarmConditionTypeData;
    UA_DISABLE_COPY(AlarmConditionTypeBase);
protected:
    // destruction
    virtual ~AlarmConditionTypeBase();
public:
    // construction
    AlarmConditionTypeBase(const UaNodeId& nodeId, UaObject* pInstanceDeclarationObject, NodeManagerConfig* pNodeConfig, const UaNodeId& sourceNode, const UaString& sourceName, UaMutexRefCounted* pSharedMutex = NULL);
    AlarmConditionTypeBase(const UaNodeId& nodeId, const UaString& name, OpcUa_UInt16 browseNameNameSpaceIndex, NodeManagerConfig* pNodeConfig, const UaNodeId& sourceNode, const UaString& sourceName, UaMutexRefCounted* pSharedMutex = NULL);
    AlarmConditionTypeBase(
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

    virtual UaStatus PlaceInService(
        const ServiceContext& serviceContext /**<General context for the service calls containing
                                                 information like the session object,
                                                 return diagnostic mask and timeout hint.*/) = 0;
    virtual UaStatus RemoveFromService(
        const ServiceContext& serviceContext /**<General context for the service calls containing
                                                 information like the session object,
                                                 return diagnostic mask and timeout hint.*/) = 0;
    virtual UaStatus Reset(
        const ServiceContext& serviceContext /**<General context for the service calls containing
                                                 information like the session object,
                                                 return diagnostic mask and timeout hint.*/) = 0;
    virtual UaStatus Silence(
        const ServiceContext& serviceContext /**<General context for the service calls containing
                                                 information like the session object,
                                                 return diagnostic mask and timeout hint.*/) = 0;
    virtual UaStatus Suppress(
        const ServiceContext& serviceContext /**<General context for the service calls containing
                                                 information like the session object,
                                                 return diagnostic mask and timeout hint.*/) = 0;
    virtual UaStatus Unsuppress(
        const ServiceContext& serviceContext /**<General context for the service calls containing
                                                 information like the session object,
                                                 return diagnostic mask and timeout hint.*/) = 0;

    // ActiveState
    virtual void setActiveState(OpcUa_Boolean activeState);
    virtual OpcUa_Boolean getActiveStateBool();
    virtual UaLocalizedText getActiveState();
    virtual void setActiveStateStatus(OpcUa_StatusCode status);
    virtual void getActiveStateValue(Session* pSession, UaVariant& value);
    virtual void getActiveState_EffectiveDisplayNameValue(Session* pSession, OpcUa_Variant& value);
    // AudibleEnabled
    virtual void setAudibleEnabled(OpcUa_Boolean AudibleEnabled);
    virtual OpcUa_Boolean getAudibleEnabled() const;
    virtual void setAudibleEnabledStatus(OpcUa_StatusCode status);
    virtual void getAudibleEnabledValue(Session* pSession, UaVariant& value);
    // AudibleSound
    virtual void setAudibleSound(UaByteString& AudibleSound);
    virtual UaByteString getAudibleSound() const;
    virtual void setAudibleSoundStatus(OpcUa_StatusCode status);
    virtual void getAudibleSoundValue(Session* pSession, UaVariant& value);
    // EnabledState
    // Already defined by base class
    // FirstInGroupFlag
    virtual void setFirstInGroupFlag(OpcUa_Boolean FirstInGroupFlag);
    virtual OpcUa_Boolean getFirstInGroupFlag() const;
    virtual void setFirstInGroupFlagStatus(OpcUa_StatusCode status);
    virtual void getFirstInGroupFlagValue(Session* pSession, UaVariant& value);
    // InputNode
    virtual void setInputNode(const UaNodeId& InputNode);
    virtual UaNodeId getInputNode() const;
    virtual void setInputNodeStatus(OpcUa_StatusCode status);
    virtual void getInputNodeValue(Session* pSession, UaVariant& value);
    // LatchedState
    virtual void setLatchedState(OpcUa_Boolean latchedState);
    virtual OpcUa_Boolean getLatchedStateBool();
    virtual UaLocalizedText getLatchedState();
    virtual void setLatchedStateStatus(OpcUa_StatusCode status);
    virtual void getLatchedStateValue(Session* pSession, UaVariant& value);
    // MaxTimeShelved
    virtual void setMaxTimeShelved(OpcUa_Double MaxTimeShelved);
    virtual OpcUa_Double getMaxTimeShelved() const;
    virtual void setMaxTimeShelvedStatus(OpcUa_StatusCode status);
    virtual void getMaxTimeShelvedValue(Session* pSession, UaVariant& value);
    // OffDelay
    virtual void setOffDelay(OpcUa_Double OffDelay);
    virtual OpcUa_Double getOffDelay() const;
    virtual void setOffDelayStatus(OpcUa_StatusCode status);
    virtual void getOffDelayValue(Session* pSession, UaVariant& value);
    // OnDelay
    virtual void setOnDelay(OpcUa_Double OnDelay);
    virtual OpcUa_Double getOnDelay() const;
    virtual void setOnDelayStatus(OpcUa_StatusCode status);
    virtual void getOnDelayValue(Session* pSession, UaVariant& value);
    // OutOfServiceState
    virtual void setOutOfServiceState(OpcUa_Boolean outOfServiceState);
    virtual OpcUa_Boolean getOutOfServiceStateBool();
    virtual UaLocalizedText getOutOfServiceState();
    virtual void setOutOfServiceStateStatus(OpcUa_StatusCode status);
    virtual void getOutOfServiceStateValue(Session* pSession, UaVariant& value);
    // ReAlarmRepeatCount
    virtual void setReAlarmRepeatCount(OpcUa_Int16 ReAlarmRepeatCount);
    virtual OpcUa_Int16 getReAlarmRepeatCount() const;
    virtual void setReAlarmRepeatCountStatus(OpcUa_StatusCode status);
    virtual void getReAlarmRepeatCountValue(Session* pSession, UaVariant& value);
    // ReAlarmTime
    virtual void setReAlarmTime(OpcUa_Double ReAlarmTime);
    virtual OpcUa_Double getReAlarmTime() const;
    virtual void setReAlarmTimeStatus(OpcUa_StatusCode status);
    virtual void getReAlarmTimeValue(Session* pSession, UaVariant& value);
    // SilenceState
    virtual void setSilenceState(OpcUa_Boolean silenceState);
    virtual OpcUa_Boolean getSilenceStateBool();
    virtual UaLocalizedText getSilenceState();
    virtual void setSilenceStateStatus(OpcUa_StatusCode status);
    virtual void getSilenceStateValue(Session* pSession, UaVariant& value);
    // SuppressedOrShelved
    virtual void setSuppressedOrShelved(OpcUa_Boolean SuppressedOrShelved);
    virtual OpcUa_Boolean getSuppressedOrShelved() const;
    virtual void setSuppressedOrShelvedStatus(OpcUa_StatusCode status);
    virtual void getSuppressedOrShelvedValue(Session* pSession, UaVariant& value);
    // SuppressedState
    virtual void setSuppressedState(OpcUa_Boolean suppressedState);
    virtual OpcUa_Boolean getSuppressedStateBool();
    virtual UaLocalizedText getSuppressedState();
    virtual void setSuppressedStateStatus(OpcUa_StatusCode status);
    virtual void getSuppressedStateValue(Session* pSession, UaVariant& value);

    virtual OpcUa::TwoStateVariableType* getActiveStateNode();
    virtual const OpcUa::TwoStateVariableType* getActiveStateNode() const;
    virtual OpcUa::PropertyType* getAudibleEnabledNode();
    virtual const OpcUa::PropertyType* getAudibleEnabledNode() const;
    virtual OpcUa::AudioVariableType* getAudibleSoundNode();
    virtual const OpcUa::AudioVariableType* getAudibleSoundNode() const;
    virtual OpcUa::AlarmGroupType* getFirstInGroup();
    virtual const OpcUa::AlarmGroupType* getFirstInGroup() const;
    virtual OpcUa::PropertyType* getFirstInGroupFlagNode();
    virtual const OpcUa::PropertyType* getFirstInGroupFlagNode() const;
    virtual OpcUa::PropertyType* getInputNodeNode();
    virtual const OpcUa::PropertyType* getInputNodeNode() const;
    virtual OpcUa::TwoStateVariableType* getLatchedStateNode();
    virtual const OpcUa::TwoStateVariableType* getLatchedStateNode() const;
    virtual OpcUa::PropertyType* getMaxTimeShelvedNode();
    virtual const OpcUa::PropertyType* getMaxTimeShelvedNode() const;
    virtual OpcUa::PropertyType* getOffDelayNode();
    virtual const OpcUa::PropertyType* getOffDelayNode() const;
    virtual OpcUa::PropertyType* getOnDelayNode();
    virtual const OpcUa::PropertyType* getOnDelayNode() const;
    virtual OpcUa::TwoStateVariableType* getOutOfServiceStateNode();
    virtual const OpcUa::TwoStateVariableType* getOutOfServiceStateNode() const;
    virtual OpcUa::PropertyType* getReAlarmRepeatCountNode();
    virtual const OpcUa::PropertyType* getReAlarmRepeatCountNode() const;
    virtual OpcUa::PropertyType* getReAlarmTimeNode();
    virtual const OpcUa::PropertyType* getReAlarmTimeNode() const;
    virtual OpcUa::ShelvedStateMachineType* getShelvingState();
    virtual const OpcUa::ShelvedStateMachineType* getShelvingState() const;
    virtual OpcUa::TwoStateVariableType* getSilenceStateNode();
    virtual const OpcUa::TwoStateVariableType* getSilenceStateNode() const;
    virtual OpcUa::PropertyType* getSuppressedOrShelvedNode();
    virtual const OpcUa::PropertyType* getSuppressedOrShelvedNode() const;
    virtual OpcUa::TwoStateVariableType* getSuppressedStateNode();
    virtual const OpcUa::TwoStateVariableType* getSuppressedStateNode() const;

    // NodeAccessInfo management
    virtual void useAccessInfoFromType();
    void useAccessInfoFromInstance(AlarmConditionTypeBase *pInstance);

    virtual UaStatus triggerEvent(
        const UaDateTime&   time,
        const UaDateTime&   receiveTime,
        const UaByteString& eventId);

    virtual void getAlarmConditionTypeOptionalFieldData(OpcUa_UInt32 index, Session* pSession, OpcUa_Variant& data);

protected:
    // Object nodes
    // Object AlarmGroup_Placeholder
    static OpcUa::AlarmGroupType*  s_pAlarmGroup_Placeholder;
    // Object FirstInGroup
    static OpcUa::AlarmGroupType*  s_pFirstInGroup;
    OpcUa::AlarmGroupType*  m_pFirstInGroup;
    // Object ShelvingState
    static OpcUa::ShelvedStateMachineType*  s_pShelvingState;
    OpcUa::ShelvedStateMachineType*  m_pShelvingState;

    // Variable nodes
    // Variable ActiveState
    static OpcUa::TwoStateVariableType*  s_pActiveState;
    OpcUa::TwoStateVariableType*  m_pActiveState;
    // Variable AudibleEnabled
    static OpcUa::PropertyType*  s_pAudibleEnabled;
    OpcUa::PropertyType*  m_pAudibleEnabled;
    // Variable AudibleSound
    static OpcUa::AudioVariableType*  s_pAudibleSound;
    OpcUa::AudioVariableType*  m_pAudibleSound;
    // Variable EnabledState
    static OpcUa::TwoStateVariableType*  s_pEnabledState;
    // EnabledState defined by base type
    // Variable FirstInGroupFlag
    static OpcUa::PropertyType*  s_pFirstInGroupFlag;
    OpcUa::PropertyType*  m_pFirstInGroupFlag;
    // Variable InputNode
    static OpcUa::PropertyType*  s_pInputNode;
    OpcUa::PropertyType*  m_pInputNode;
    // Variable LatchedState
    static OpcUa::TwoStateVariableType*  s_pLatchedState;
    OpcUa::TwoStateVariableType*  m_pLatchedState;
    // Variable MaxTimeShelved
    static OpcUa::PropertyType*  s_pMaxTimeShelved;
    OpcUa::PropertyType*  m_pMaxTimeShelved;
    // Variable OffDelay
    static OpcUa::PropertyType*  s_pOffDelay;
    OpcUa::PropertyType*  m_pOffDelay;
    // Variable OnDelay
    static OpcUa::PropertyType*  s_pOnDelay;
    OpcUa::PropertyType*  m_pOnDelay;
    // Variable OutOfServiceState
    static OpcUa::TwoStateVariableType*  s_pOutOfServiceState;
    OpcUa::TwoStateVariableType*  m_pOutOfServiceState;
    // Variable ReAlarmRepeatCount
    static OpcUa::PropertyType*  s_pReAlarmRepeatCount;
    OpcUa::PropertyType*  m_pReAlarmRepeatCount;
    // Variable ReAlarmTime
    static OpcUa::PropertyType*  s_pReAlarmTime;
    OpcUa::PropertyType*  m_pReAlarmTime;
    // Variable SilenceState
    static OpcUa::TwoStateVariableType*  s_pSilenceState;
    OpcUa::TwoStateVariableType*  m_pSilenceState;
    // Variable SuppressedOrShelved
    static OpcUa::PropertyType*  s_pSuppressedOrShelved;
    OpcUa::PropertyType*  m_pSuppressedOrShelved;
    // Variable SuppressedState
    static OpcUa::TwoStateVariableType*  s_pSuppressedState;
    OpcUa::TwoStateVariableType*  m_pSuppressedState;


    // Method PlaceInService
    static OpcUa::BaseMethod* s_pPlaceInServiceMethod;
    // Method RemoveFromService
    static OpcUa::BaseMethod* s_pRemoveFromServiceMethod;
    // Method Reset
    static OpcUa::BaseMethod* s_pResetMethod;
    // Method Silence
    static OpcUa::BaseMethod* s_pSilenceMethod;
    // Method Suppress
    static OpcUa::BaseMethod* s_pSuppressMethod;
    // Method Unsuppress
    static OpcUa::BaseMethod* s_pUnsuppressMethod;

private:
    void initialize();
    void createChildren();

private:
    static bool                                 s_typeNodesCreated;
    static std::map<OpcUa_UInt32, OpcUa_UInt32> s_AlarmConditionTypeDataFields;
    UaObjectPointerArray<UaVariant>             m_FieldValues;
};

} // End namespace for the UA information model http://opcfoundation.org/UA/

#endif // #ifndef __OPCUAALARMCONDITIONTYPEBASE_H__

