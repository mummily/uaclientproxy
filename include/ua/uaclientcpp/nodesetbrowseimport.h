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
** Project: C++ OPC Client SDK
**
******************************************************************************/
#ifndef _NODESETBROWSEIMPORT_H_
#define _NODESETBROWSEIMPORT_H_

#include "abstractnodesetbrowseimport.h"
#include "uasession.h"

namespace UaClientSdk
{

/** OPC UA client based implementation for the Nodeset Browse/Read importer.
*
* This class allows the creation of a node model (UaBase::Nodeset) from browsing and reading
* the address space of the connected OPC UA Server.
*
* The imported model can be exported to a UANodeSet XML file by using the class UaBase::NodesetXmlExport.
*
* @code
* UaClientSdk::NodesetBrowseImport nodesetBrowseImport(m_pSession);
* UaBase::Nodeset nodeset;
* UaBase::NodesetXmlExport nodesetXmlExport;
*
* // Import namespace with index 2 from server
* nodesetBrowseImport.import(nodeset, 2);
*
* // Store namespace in UANodeSet XML file
* nodesetXmlExport.exportNs(nodeset, "ExportNodeset.xml", 2);
* @endcode
*/
class UACLIENT_EXPORT NodesetBrowseImport :
    public UaBase::AbstractNodesetBrowseImport
{
public:
    NodesetBrowseImport(UaSession *pSession);
    ~NodesetBrowseImport();

protected:
    virtual bool browseList(const UaNodeIdArray& nodeIds, UaBrowseResults &targetNodes);
    bool browseListNext(UaBrowseResults &targetNodes);
    virtual bool read(UaBase::BaseNode* nodes[], UaDataValues &attributes);
    virtual UaStringArray readNamespaceTable();
    UaReadValueIds getAttributes(UaBase::BaseNode *nodeIds[]) const;

private:
    // Config for connection
    UaSession* m_pSession;
    ServiceSettings m_generalServiceSettings;
    BrowseContext m_generalBrowseContext;
    const static OpcUa_UInt32 m_browseResultMask = (OpcUa_BrowseResultMask_ReferenceTypeId |
                                                    OpcUa_BrowseResultMask_IsForward       |
                                                    OpcUa_BrowseResultMask_NodeClass       |
                                                    OpcUa_BrowseResultMask_BrowseName       );//=>0xF


    bool extractCPs(const UaBrowseResults &targetNodes, UaBooleanArray &resultHasCP, UaByteStringArray &continuationPoints) const;
};

} // end namespace UaClientSdk

#endif //_NODESETBROWSEIMPORT_H_
