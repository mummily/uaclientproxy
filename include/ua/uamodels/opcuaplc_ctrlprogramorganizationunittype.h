/******************************************************************************
** opcuaplc_ctrlprogramorganizationunittype.h
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
** Project: C++ OPC Server SDK information model for namespace http://PLCopen.org/OpcUa/IEC61131-3/
**
** Description: OPC Unified Architecture Software Development Kit.
**
******************************************************************************/

#ifndef __OPCUAPLC_CTRLPROGRAMORGANIZATIONUNITTYPE_H__
#define __OPCUAPLC_CTRLPROGRAMORGANIZATIONUNITTYPE_H__

#include "opcuaplc_ctrlprogramorganizationunittypebase.h"

// Namespace for the UA information model http://PLCopen.org/OpcUa/IEC61131-3/
namespace OpcUaPlc {


/** @brief Class implementing the UaObject interface for the CtrlProgramOrganizationUnitType.
 *
 * OPC UA Objects are used to represent systems, system components, real-world objects and software
 * objects. They have the NodeClass @ref L3UaNodeClassObject. The detailed description of Objects and their attributes
 * can be found in the general description of the @ref L3UaNodeClassObject node class.
 *
 *  **Variable members of the CtrlProgramOrganizationUnitType:**
 *
 *  Browse Name | DataType   | TypeDefinition       | Modelling Rule | See Also
 *  ------------|------------|----------------------|----------------|-------------------------------------------------------------------------------------------------------------------------
 *  Body        | XmlElement | BaseDataVariableType | Optional       | \ref CtrlProgramOrganizationUnitTypeBase::getBody "getBody", \ref CtrlProgramOrganizationUnitTypeBase::setBody "setBody"
 *
 */
class UAMODELS_EXPORT CtrlProgramOrganizationUnitType:
    public CtrlProgramOrganizationUnitTypeBase
{
    UA_DISABLE_COPY(CtrlProgramOrganizationUnitType);
protected:
    // destruction
    virtual ~CtrlProgramOrganizationUnitType();
public:
    // construction
    CtrlProgramOrganizationUnitType(const UaNodeId& nodeId, UaObject* pInstanceDeclarationObject, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    CtrlProgramOrganizationUnitType(const UaNodeId& nodeId, const UaString& name, OpcUa_UInt16 browseNameNameSpaceIndex, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    CtrlProgramOrganizationUnitType(
        UaBase::Object*    pBaseNode,
        XmlUaNodeFactoryManager*   pFactory,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);
    static void createTypes();
    static void clearStaticMembers();


protected:

private:
};

} // End namespace for the UA information model http://PLCopen.org/OpcUa/IEC61131-3/

#endif // #ifndef __OPCUAPLCCTRLPROGRAMORGANIZATIONUNITTYPE_H__
