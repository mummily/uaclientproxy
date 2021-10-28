/******************************************************************************
** uaabstractdefinitionprivate.h
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
#ifndef UAABSTRACTDEFINITIONPRIVATE_H
#define UAABSTRACTDEFINITIONPRIVATE_H

#include "uanodeid.h"
#include "uastring.h"
#include "ualocalizedtext.h"
#include <uaatomic.h>

#define UA_DD(Class) Class##Private * const d = (Class##Private*)d_func()

/** The class describes an abstract definition.
 *
 * This is the base class for ...
 */
class UaAbstractDefinitionPrivate
{
public:
    UaAbstractDefinitionPrivate();
    UaAbstractDefinitionPrivate(bool bStatic);
    UaAbstractDefinitionPrivate(const UaAbstractDefinitionPrivate &other);
    virtual ~UaAbstractDefinitionPrivate();

    int addRef();
    int release();
    inline int refCount() { return m_iRefCnt; }

private:
    int                         m_iRefCnt;

public:
    UaNodeId                    m_dataTypeId;
    UaString                    m_name;
    UaString                    m_namespace;
    UaLocalizedText             m_documentation;
};

#endif // UAABSTRACTDEFINITIONPRIVATE_H
