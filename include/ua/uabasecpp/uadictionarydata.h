/******************************************************************************
** Copyright (c) 2016-2018 Unified Automation GmbH. All rights reserved.
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
#ifndef UADICTIONARYDATA_H
#define UADICTIONARYDATA_H

#include <map>
#include <uastructuredefinition.h>
#include <uaenumdefinition.h>

class UaDictionaryDatas;
class UaXmlDocument;

class UaDictionaryData
{
    friend class UaDictionaryDatas;
public:
    UaDictionaryData(const UaString &sNamespaceUri);
    void addStructureDefinition(const UaStructureDefinition &definition);
    void addEnumDefinition(const UaEnumDefinition &definition);
    void removeStructureDefinition(const UaStructureDefinition &definition);

    UaString namespaceUri() const;
    UaStructureDefinition structureDefinition(const UaString &sName) const;
    UaEnumDefinition enumDefinition(const UaString &sName) const;

private:
    UaString m_sNamespaceUri;
    std::map<UaString, UaStructureDefinition> m_structureDefinitions;
    std::map<UaString, UaEnumDefinition> m_enumDefinitions;
};

class UaDictionaryDatas
{
public:
    UaDictionaryDatas();
    ~UaDictionaryDatas();
    void addDictionary(const UaNodeId &dictionaryId, UaDictionaryData *pDictionaryData);
    UaDictionaryData* dictionaryData(const UaNodeId &dictionaryId) const;
    UaDictionaryData* dictionaryData(const UaString &sNamespaceUri) const;
    UaStructureDefinition structureDefinition(
        const UaString &sNamespaceUri,
        const UaString &sTypeName) const;
    UaEnumDefinition enumDefinition(
        const UaString &sNamespaceUri,
        const UaString &sTypeName) const;

    void toStructureMap(std::map<UaNodeId, UaStructureDefinition> &rMapStructures) const;

private:
    bool m_bHaveDoubleUsedNamespaceUris;
    std::map<UaNodeId, UaDictionaryData*> m_dictionaries;
};


#endif
