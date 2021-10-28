/******************************************************************************
** uaoptionsetdefinition.h
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
** Project: C++ OPC SDK base module
**
******************************************************************************/
#ifndef UAOPTIONSETDEFINITION_H
#define UAOPTIONSETDEFINITION_H

#include "uaabstractdefinition.h"

class UaLocalizedText;
class UaLocalizedTextArray;

/** The class describes an OptionSet.
 *
 * You can access the values by index..
 *
 */
class UABASE_EXPORT UaOptionSetDefinition : public UaAbstractDefinition
{
public:
    UaOptionSetDefinition();
    UaOptionSetDefinition(const UaOptionSetDefinition &other);
    UaOptionSetDefinition(const OpcUa_EnumDefinition *other, const UaNodeId &typeId);

    enum BaseType
    {
        BaseType_Byte,
        BaseType_UInt16,
        BaseType_UInt32,
        BaseType_UInt64,
        BaseType_OptionSet
    };

    UaOptionSetDefinition& operator=(const UaOptionSetDefinition &other);

    bool operator==(const UaOptionSetDefinition &other) const;
    bool operator!=(const UaOptionSetDefinition &other) const;

    // UaAbstractDefinition interface
    virtual int childrenCount() const;
    virtual void clear();

    BaseType baseType() const;
    void setBaseType(BaseType baseType);
    UaLocalizedText child(int i) const;
    void addChild(const UaLocalizedText &newChild);
    UaLocalizedTextArray children() const;
    void setChildren(const UaLocalizedTextArray &children);
    bool hasValidBits() const;

    void setBinaryEncodingId(const UaNodeId &nodeId);
    UaNodeId binaryEncodingId() const;
    void setXmlEncodingId(const UaNodeId &nodeId);
    UaNodeId xmlEncodingId() const;

    UaStructureDefinition structureDefinition() const;

protected:
    virtual UaAbstractDefinitionPrivate* copyPrivate();
};

#endif
