/******************************************************************************
** opcua_alarmmetricstype.h
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

#ifndef __OPCUA_ALARMMETRICSTYPE_H__
#define __OPCUA_ALARMMETRICSTYPE_H__

#include "opcua_alarmmetricstypebase.h"

// Namespace for the UA information model http://opcfoundation.org/UA/
namespace OpcUa {

/** @brief Class implementing the UaObject interface for the AlarmMetricsType.
 *
 * OPC UA Objects are used to represent systems, system components, real-world objects and software
 * objects. They have the NodeClass @ref L3UaNodeClassObject. The detailed description of Objects and their attributes
 * can be found in the general description of the @ref L3UaNodeClassObject node class.
 *
 *  **Variable members of the AlarmMetricsType:**
 *
 *  Browse Name         | DataType | TypeDefinition        | Modelling Rule | See Also
 *  --------------------|----------|-----------------------|----------------|-------------------------------------------------------------------------------------------------------------------------------------------------------
 *  AlarmCount          | UInt32   | PropertyType          | Mandatory      | \ref AlarmMetricsTypeBase::getAlarmCount "getAlarmCount", \ref AlarmMetricsTypeBase::setAlarmCount "setAlarmCount"
 *  AverageAlarmRate    | Double   | AlarmRateVariableType | Mandatory      | \ref AlarmMetricsTypeBase::getAverageAlarmRate "getAverageAlarmRate", \ref AlarmMetricsTypeBase::setAverageAlarmRate "setAverageAlarmRate"
 *  CurrentAlarmRate    | Double   | AlarmRateVariableType | Mandatory      | \ref AlarmMetricsTypeBase::getCurrentAlarmRate "getCurrentAlarmRate", \ref AlarmMetricsTypeBase::setCurrentAlarmRate "setCurrentAlarmRate"
 *  MaximumActiveState  | Duration | PropertyType          | Mandatory      | \ref AlarmMetricsTypeBase::getMaximumActiveState "getMaximumActiveState", \ref AlarmMetricsTypeBase::setMaximumActiveState "setMaximumActiveState"
 *  MaximumAlarmRate    | Double   | AlarmRateVariableType | Mandatory      | \ref AlarmMetricsTypeBase::getMaximumAlarmRate "getMaximumAlarmRate", \ref AlarmMetricsTypeBase::setMaximumAlarmRate "setMaximumAlarmRate"
 *  MaximumReAlarmCount | UInt32   | PropertyType          | Mandatory      | \ref AlarmMetricsTypeBase::getMaximumReAlarmCount "getMaximumReAlarmCount", \ref AlarmMetricsTypeBase::setMaximumReAlarmCount "setMaximumReAlarmCount"
 *  MaximumUnAck        | Duration | PropertyType          | Mandatory      | \ref AlarmMetricsTypeBase::getMaximumUnAck "getMaximumUnAck", \ref AlarmMetricsTypeBase::setMaximumUnAck "setMaximumUnAck"
 *  StartTime           | UtcTime  | PropertyType          | Mandatory      | \ref AlarmMetricsTypeBase::getStartTime "getStartTime", \ref AlarmMetricsTypeBase::setStartTime "setStartTime"
 *
 *  **Method members of the AlarmMetricsType:**
 *
 *  Browse Name | Modelling Rule
 *  ------------|---------------
 *  \ref Reset  | Mandatory
 *
 */
class SERVER_CORE_EXPORT AlarmMetricsType:
    public AlarmMetricsTypeBase
{
    UA_DISABLE_COPY(AlarmMetricsType);
protected:
    // destruction
    virtual ~AlarmMetricsType();
public:
    // construction
    AlarmMetricsType(const UaNodeId& nodeId, UaObject* pInstanceDeclarationObject, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    AlarmMetricsType(const UaNodeId& nodeId, const UaString& name, OpcUa_UInt16 browseNameNameSpaceIndex, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    AlarmMetricsType(
        UaBase::Object*    pBaseNode,
        XmlUaNodeFactoryManager*   pFactory,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);
    static void createTypes();
    static void clearStaticMembers();

    // UaAlarmMetricsType method Reset
    virtual UaStatus Reset(
        const ServiceContext& serviceContext);

protected:

private:
};

} // End namespace for the UA information model http://opcfoundation.org/UA/

#endif // #ifndef __OPCUAALARMMETRICSTYPE_H__

