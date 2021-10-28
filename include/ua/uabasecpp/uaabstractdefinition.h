/******************************************************************************
** uaabstractdefinition.h
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
#ifndef UAABSTRACTDEFINITION_H
#define UAABSTRACTDEFINITION_H

#include "uadatatypedefinition.h"

class UaAbstractDefinitionPrivate;
class UaLocalizedText;

/** The class is the base class for Definitions
 */
class UABASE_EXPORT UaAbstractDefinition
{
    UA_DISABLE_COPY(UaAbstractDefinition);
    UaAbstractDefinition();
protected:
    UA_DECLARE_PRIVATE(UaAbstractDefinition)
    UaAbstractDefinition(UaAbstractDefinitionPrivate* pBody);

    virtual UaAbstractDefinitionPrivate* copyPrivate() = 0;
    void copyOnWrite();
public:
    virtual ~UaAbstractDefinition();

    virtual int childrenCount() const = 0;
    virtual void clear() = 0;
    virtual bool isNull() const;

    void setDataTypeId(const UaNodeId &nodeId);
    UaNodeId dataTypeId() const;

    void setName(const UaString &sName);
    UaString name() const;

    void setDocumentation(const UaLocalizedText &documentation);
    UaLocalizedText documentation() const;

    void setNamespace(const UaString &sNamespace);
    UaString getNamespace() const;
};

#endif // UAABSTRACTDEFINITION_H
