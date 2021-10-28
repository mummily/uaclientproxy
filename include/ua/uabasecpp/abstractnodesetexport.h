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
#ifndef ABSTRACTNODESETEXPORT_H
#define ABSTRACTNODESETEXPORT_H

#include "nodeset.h"
#include <uaabstractdictionaryreader.h>

namespace UaBase
{

/** Abstract base class for a Nodeset exporter.
 *
 * This class implements the DictionaryReader Interface in terms of Nodeset operations
 * and provides convenience functions to access the TypeDictionary data.
 * Any concrete exporter implementation should inherit from
 * this base class.
 */
class UABASE_EXPORT AbstractNodesetExport :
    private UaAbstractDictionaryReader
{
public:
    AbstractNodesetExport();
    virtual ~AbstractNodesetExport();

    /** export interface */
    virtual UaStatus exportNs(const Nodeset& nodeset, const UaString &filename) = 0;

    bool loadDataTypeDictionaries(const Nodeset* pNodeset);

protected:
    UaUInt16Array nsmap;

    OpcUa_UInt16 mapIndex(OpcUa_UInt16 index);

    UaStructureDefinition structureDefinition(const UaNodeId& typeId) const;
    UaEnumDefinition enumDefinition(const UaNodeId& typeId) const;
    UaOptionSetDefinition optionSetDefinition(const UaNodeId& typeId) const;
    bool isStruct(const UaNodeId& typeId) const;
    bool isEnum(const UaNodeId& typeId) const;
    bool isOptionSet(const UaNodeId& typeId) const;

    bool createNamespaceMapping(const Nodeset &nodeset, OpcUa_UInt16 exportIdx);
    bool getMappedUris(const Nodeset &nodeset, UaStringArray &nss);
private:
    /** The Nodeset to export and load type definitions from */
    const Nodeset* m_pNodeset;

    //implementation of the TypeDictionaryReader Interface
    virtual UaStatus browse(const UaNodeId &startingNodeId, const UaNodeId &referenceTypeId, UaReferenceDescriptions &rResult) const;
    virtual UaStatus browseInverse(const UaNodeId &startingNodeId, const UaNodeId &referenceTypeId, UaReferenceDescriptions &rResult) const;
    virtual UaStatus readValue(const UaNodeId &nodeId, UaVariant &rValue) const;
    virtual UaStatus readValues(const UaNodeIdArray &nodeIds, UaDataValues &rValues) const;
    virtual UaStatus readDescriptionAttributes(const UaNodeIdArray &nodeIds, UaLocalizedTextArray &rValues) const;

    // Maps that hold type definitions after a call to loadDataTypeDictionaries()
    std::map<UaNodeId, UaStructureDefinition> m_mapStructureDefinitions;
    std::map<UaNodeId, UaEnumDefinition>      m_mapEnumDefinitions;
    std::map<UaNodeId, UaOptionSetDefinition> m_mapOptionSetDefinitions;
};

} // end namespace UaBase

#endif // ABSTRACTNODESETEXPORT_H
