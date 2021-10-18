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
#ifndef _NODESETXMLIMPORT_H_
#define _NODESETXMLIMPORT_H_

#include "abstractnodesetimport.h"
#include <uanodesetxmlparser.h>

namespace UaBase
{

/** Importer class to create a Nodeset from an xml file.
 *  This class implements the interface AbstractNodesetImport to import a Nodeset from an xml file.
 *  Uses UaNodesetXmlParser to parse xml data and create BaseNodes
 */
class UABASE_EXPORT NodesetXmlImport
    :   public AbstractNodesetImport,
        private UaNodesetXmlParser
{
public:
        NodesetXmlImport(UaStringArray sFileNames);
        NodesetXmlImport(UaString sFileName);
        ~NodesetXmlImport();
        virtual UaStatus import(Nodeset &nodeset);

        /** add a file to import from; TODO: add sanity checks */
        inline bool addFilename(UaString sFileName)
            { m_sFilenames.resize(m_sFilenames.length() + 1);
              sFileName.copyTo(&m_sFilenames[m_sFilenames.length()-1]);
              return true; }

        /** clear list of files to import from */
        inline void clearFilenames() { m_sFilenames.clear(); }
private:
        UaStringArray m_sFilenames;

};

} // end namespace UaBase
#endif //_NODESETXMLIMPORT_H_
