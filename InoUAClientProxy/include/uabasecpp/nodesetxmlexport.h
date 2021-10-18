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
#ifndef _NODESETXMLEXPORT_H_
#define _NODESETXMLEXPORT_H_

#include "abstractnodesetexport.h"

class UaXmlDocument;

namespace UaBase
{

/** Exporter class of a Nodeset to xml file.
 * This class implements the interface AbstractNodesetExport to export a Nodeset to xml file.
 */
class UABASE_EXPORT NodesetXmlExport :
        public AbstractNodesetExport
{
public:
    NodesetXmlExport();
    ~NodesetXmlExport();

    virtual inline UaStatus exportNs(const Nodeset &nodeset, const UaString &filename) { return exportNs(nodeset, filename, 0); }
    virtual UaStatus exportNs(const Nodeset &nodeset, const UaString &filename, OpcUa_UInt16 exportNsIdx);
    virtual UaStatus exportNsAll(const Nodeset &nodeset, const UaString &filename);

private:
    UaString m_fileName;
    UaXmlDocument* m_pXmlDocument;
    bool writeNsUris(const Nodeset &nodeset, OpcUa_UInt16 exportNsIdx);
    bool writeServerUris();
    bool writeModels();
    bool writeAliases();
    bool writeExtensions();
    bool writeLastModified();
    bool writeNode(const BaseNode *pNode, OpcUa_UInt16 ns, bool bAllNamespaces = false);
    bool write_UADataType(const DataType *pNode);
    bool write_UAObject(const Object *pNode);
    bool write_UAObjectType(const ObjectType *pNode);
    bool write_UAMethod(const Method *pNode);
    bool write_UAView(const View *pNode);
    bool write_UAReferenceType(const ReferenceType *pNode);
    bool write_UAVariableType(const VariableType *pNode);
    bool write_UAVariable(const Variable *pNode);
    bool write_UANode(const BaseNode *pNode);
    bool write_structDefinition(const UaStructureDefinition &definition);
    bool write_enumDefinition(const UaEnumDefinition &definition);
    bool write_optionSetDefinition(const UaOptionSetDefinition &definition);
    bool write_UAVariant(const UaVariant& value, const UaNodeId &nodeId);
    bool write_UAExtensionObject(UaExtensionObject &extensionObject);
};

} // end namespace UaBase
#endif // _NODESETXMLEXPORT_H_
