/******************************************************************************
** opcua_alarmmetricstypebase.h
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

#ifndef __OPCUA_ALARMMETRICSTYPEBASE_H__
#define __OPCUA_ALARMMETRICSTYPEBASE_H__

#include "opcua_baseobjecttype.h"
#include "basenodes.h"
#include "opcua_identifiers.h"
#include "opcua_propertytype.h"

// Namespace for the UA information model http://opcfoundation.org/UA/
namespace OpcUa {

class AlarmRateVariableType;
class PropertyType;

/** Generated base class for a AlarmMetricsType.
 *
 *  This class contains the generated base code for the object type AlarmMetricsType
 *  representing an OPC UA ObjectType. This class is used to create the object type and to
 *  create and represent instances of the object type in the server address space.
 *
 *  **Variable members of the AlarmMetricsType:**
 *
 *  Browse Name         | DataType | TypeDefinition        | Modelling Rule | See Also
 *  --------------------|----------|-----------------------|----------------|---------------------------------------------------------
 *  AlarmCount          | UInt32   | PropertyType          | Mandatory      | \ref getAlarmCount, \ref setAlarmCount
 *  AverageAlarmRate    | Double   | AlarmRateVariableType | Mandatory      | \ref getAverageAlarmRate, \ref setAverageAlarmRate
 *  CurrentAlarmRate    | Double   | AlarmRateVariableType | Mandatory      | \ref getCurrentAlarmRate, \ref setCurrentAlarmRate
 *  MaximumActiveState  | Duration | PropertyType          | Mandatory      | \ref getMaximumActiveState, \ref setMaximumActiveState
 *  MaximumAlarmRate    | Double   | AlarmRateVariableType | Mandatory      | \ref getMaximumAlarmRate, \ref setMaximumAlarmRate
 *  MaximumReAlarmCount | UInt32   | PropertyType          | Mandatory      | \ref getMaximumReAlarmCount, \ref setMaximumReAlarmCount
 *  MaximumUnAck        | Duration | PropertyType          | Mandatory      | \ref getMaximumUnAck, \ref setMaximumUnAck
 *  StartTime           | UtcTime  | PropertyType          | Mandatory      | \ref getStartTime, \ref setStartTime
 *
 */
class SERVER_CORE_EXPORT AlarmMetricsTypeBase:
    public OpcUa::BaseObjectType
{
    UA_DISABLE_COPY(AlarmMetricsTypeBase);
protected:
    virtual ~AlarmMetricsTypeBase();
public:
    // construction / destruction
    AlarmMetricsTypeBase(const UaNodeId& nodeId, UaObject* pInstanceDeclarationObject, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    AlarmMetricsTypeBase(const UaNodeId& nodeId, const UaString& name, OpcUa_UInt16 browseNameNameSpaceIndex, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    AlarmMetricsTypeBase(
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

    virtual UaStatus Reset(
        const ServiceContext& serviceContext /**<General context for the service calls containing
                                                 information like the session object,
                                                 return diagnostic mask and timeout hint.*/) = 0;

    virtual void setAlarmCount(OpcUa_UInt32 AlarmCount);
    virtual OpcUa_UInt32 getAlarmCount() const;

    virtual void setAverageAlarmRate(OpcUa_Double AverageAlarmRate);
    virtual OpcUa_Double getAverageAlarmRate() const;

    virtual void setCurrentAlarmRate(OpcUa_Double CurrentAlarmRate);
    virtual OpcUa_Double getCurrentAlarmRate() const;

    virtual void setMaximumActiveState(OpcUa_Double MaximumActiveState);
    virtual OpcUa_Double getMaximumActiveState() const;

    virtual void setMaximumAlarmRate(OpcUa_Double MaximumAlarmRate);
    virtual OpcUa_Double getMaximumAlarmRate() const;

    virtual void setMaximumReAlarmCount(OpcUa_UInt32 MaximumReAlarmCount);
    virtual OpcUa_UInt32 getMaximumReAlarmCount() const;

    virtual void setMaximumUnAck(OpcUa_Double MaximumUnAck);
    virtual OpcUa_Double getMaximumUnAck() const;

    virtual void setStartTime(const UaDateTime& StartTime);
    virtual UaDateTime getStartTime() const;

    virtual OpcUa::PropertyType* getAlarmCountNode();
    virtual const OpcUa::PropertyType* getAlarmCountNode() const;
    virtual OpcUa::AlarmRateVariableType* getAverageAlarmRateNode();
    virtual const OpcUa::AlarmRateVariableType* getAverageAlarmRateNode() const;
    virtual OpcUa::AlarmRateVariableType* getCurrentAlarmRateNode();
    virtual const OpcUa::AlarmRateVariableType* getCurrentAlarmRateNode() const;
    virtual OpcUa::PropertyType* getMaximumActiveStateNode();
    virtual const OpcUa::PropertyType* getMaximumActiveStateNode() const;
    virtual OpcUa::AlarmRateVariableType* getMaximumAlarmRateNode();
    virtual const OpcUa::AlarmRateVariableType* getMaximumAlarmRateNode() const;
    virtual OpcUa::PropertyType* getMaximumReAlarmCountNode();
    virtual const OpcUa::PropertyType* getMaximumReAlarmCountNode() const;
    virtual OpcUa::PropertyType* getMaximumUnAckNode();
    virtual const OpcUa::PropertyType* getMaximumUnAckNode() const;
    virtual OpcUa::PropertyType* getStartTimeNode();
    virtual const OpcUa::PropertyType* getStartTimeNode() const;
    virtual OpcUa::BaseMethod* getReset();
    virtual const OpcUa::BaseMethod* getReset() const;

    // NodeAccessInfo management
    virtual void useAccessInfoFromType();
    void useAccessInfoFromInstance(AlarmMetricsTypeBase *pInstance);

protected:
    // Variable nodes
    // Variable AlarmCount
    static OpcUa::PropertyType*  s_pAlarmCount;
    OpcUa::PropertyType*  m_pAlarmCount;
    // Variable AverageAlarmRate
    static OpcUa::AlarmRateVariableType*  s_pAverageAlarmRate;
    OpcUa::AlarmRateVariableType*  m_pAverageAlarmRate;
    // Variable CurrentAlarmRate
    static OpcUa::AlarmRateVariableType*  s_pCurrentAlarmRate;
    OpcUa::AlarmRateVariableType*  m_pCurrentAlarmRate;
    // Variable MaximumActiveState
    static OpcUa::PropertyType*  s_pMaximumActiveState;
    OpcUa::PropertyType*  m_pMaximumActiveState;
    // Variable MaximumAlarmRate
    static OpcUa::AlarmRateVariableType*  s_pMaximumAlarmRate;
    OpcUa::AlarmRateVariableType*  m_pMaximumAlarmRate;
    // Variable MaximumReAlarmCount
    static OpcUa::PropertyType*  s_pMaximumReAlarmCount;
    OpcUa::PropertyType*  m_pMaximumReAlarmCount;
    // Variable MaximumUnAck
    static OpcUa::PropertyType*  s_pMaximumUnAck;
    OpcUa::PropertyType*  m_pMaximumUnAck;
    // Variable StartTime
    static OpcUa::PropertyType*  s_pStartTime;
    OpcUa::PropertyType*  m_pStartTime;


    // Method nodes
    static OpcUa::BaseMethod* s_pResetMethod;
    OpcUa::BaseMethod*  m_pResetMethod;


private:
    void initialize();

private:
    static bool s_typeNodesCreated;
};

} // End namespace for the UA information model http://opcfoundation.org/UA/

#endif // #ifndef __OPCUAALARMMETRICSTYPEBASE_H__


