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
#ifndef _ABSTRACTNODESETBROWSEIMPORT_H_
#define _ABSTRACTNODESETBROWSEIMPORT_H_

#include "abstractnodesetimport.h"

namespace UaBase
{

/** Abstract base class for a Nodeset Browse/Read importer.
 *
 * This class implements the basic algorithm to recursively browse an addressspace
 * from a given starting node (e.g. the root folder).
 * Importer implementations that retrieve addressspace data through
 * browse/read service calls inherit from this class.
 * Concrete implementations just have to provide the two pure virtual methods browseList and read.
 */
class UABASE_EXPORT AbstractNodesetBrowseImport :
        public AbstractNodesetImport
{
public:
        AbstractNodesetBrowseImport();
        virtual ~AbstractNodesetBrowseImport();

        virtual UaStatus import(Nodeset &nodeset);
        virtual UaStatus import(Nodeset &nodeset, const UaStringArray &nsUris);
        virtual UaStatus import(Nodeset &nodeset, const UaString &nsUri);
        virtual UaStatus import(Nodeset &nodeset, const UaUInt16Array &namespaceIndices);
        virtual UaStatus import(Nodeset &nodeset, const OpcUa_UInt16 namespaceIndex);

protected:
        virtual bool browseList(const UaNodeIdArray& nodeIds, UaBrowseResults &targetNodes) = 0;
        virtual bool read(BaseNode* (nodesToRead)[], UaDataValues &attributes) = 0;
        virtual UaStringArray readNamespaceTable() = 0;

        /* TODO: check for operational limits */
        OpcUa_UInt32 m_maxNodesToProcess;
        OpcUa_UInt32 m_maxNodesToRead;
private:
        UaStatus browseRecursive(Nodeset &nodeset, bool restrictNamespaces = false, bool restrictHierarchy = false);
        bool setAttributes(BaseNode *pNode[], const UaDataValues& values);
};

} // end namespace UaBase
#endif //_ABSTRACTNODESETBROWSEIMPORT_H_
