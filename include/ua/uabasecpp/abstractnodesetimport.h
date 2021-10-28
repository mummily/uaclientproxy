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
#ifndef _ABSTRACTNODESETIMPORT_H_
#define _ABSTRACTNODESETIMPORT_H_

#include "nodeset.h"
#include <uaarraytemplates.h>

namespace UaBase
{

/** Abstract base class for a Nodeset importer.
 *
 * Any concrete importer implementation should inherit from
 * this base class.
 */
class UABASE_EXPORT AbstractNodesetImport
{
public:
    AbstractNodesetImport();
    virtual ~AbstractNodesetImport();

    /** import interface */
    virtual UaStatus import(Nodeset& nodeset) = 0;

protected:
    /** The Nodeset to import to */
    Nodeset* m_pNodeset;
    /** Remote namespace indices to import */
    UaBooleanArray m_importNsIdx;

};

} // end namespace UaBase

#endif //_ABSTRACTNODESETIMPORT_H_
