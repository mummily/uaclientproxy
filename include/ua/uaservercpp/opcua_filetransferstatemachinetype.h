/******************************************************************************
** opcua_filetransferstatemachinetype.h
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
** Project: C++ OPC Server SDK information model for namespace http://opcfoundation.org/UA/
**
** Description: OPC Unified Architecture Software Development Kit.
**
******************************************************************************/

#ifndef __OPCUA_FILETRANSFERSTATEMACHINETYPE_H__
#define __OPCUA_FILETRANSFERSTATEMACHINETYPE_H__

#include "opcua_filetransferstatemachinetypebase.h"

// Namespace for the UA information model http://opcfoundation.org/UA/
namespace OpcUa {

class SERVER_CORE_EXPORT FileTransferStateMachineType;

/** Callback interface for handling incoming FileTransferStateMachine Method calls
*/
class SERVER_CORE_EXPORT FileTransferStateMachineTypeCallback
{
public:
    FileTransferStateMachineTypeCallback() {}
    virtual ~FileTransferStateMachineTypeCallback() {}

    /**
    *  Reset is used to reset the Error state of a FileTransferStateMachineType Object.
    */
    virtual UaStatus Reset(
        const ServiceContext& serviceContext, /**<General context for the service calls containing
                                                information like the session object,
                                                return diagnostic mask and timeout hint.*/
        FileTransferStateMachineType* pStateMachine /**< Affected Object Node.*/
    ) = 0;
};

/** @brief Class implementing the UaObject interface for the FileTransferStateMachineType.
 *
 * OPC UA Objects are used to represent systems, system components, real-world objects and software
 * objects. They have the NodeClass @ref L3UaNodeClassObject. The detailed description of Objects and their attributes
 * can be found in the general description of the @ref L3UaNodeClassObject node class.
 *
 *  **Object members of the FileTransferStateMachineType:**
 *
 *  Browse Name               | TypeDefinition   | Modelling Rule | See Also
 *  --------------------------|------------------|----------------|---------
 *  ApplyWrite                | StateType        | None           | &nbsp;
 *  ApplyWriteToError         | TransitionType   | None           | &nbsp;
 *  ApplyWriteToIdle          | TransitionType   | None           | &nbsp;
 *  Error                     | StateType        | None           | &nbsp;
 *  ErrorToIdle               | TransitionType   | None           | &nbsp;
 *  Idle                      | InitialStateType | None           | &nbsp;
 *  IdleToApplyWrite          | TransitionType   | None           | &nbsp;
 *  IdleToReadPrepare         | TransitionType   | None           | &nbsp;
 *  ReadPrepare               | StateType        | None           | &nbsp;
 *  ReadPrepareToError        | TransitionType   | None           | &nbsp;
 *  ReadPrepareToReadTransfer | TransitionType   | None           | &nbsp;
 *  ReadTransfer              | StateType        | None           | &nbsp;
 *  ReadTransferToError       | TransitionType   | None           | &nbsp;
 *  ReadTransferToIdle        | TransitionType   | None           | &nbsp;
 *
 *  **Method members of the FileTransferStateMachineType:**
 *
 *  Browse Name | Modelling Rule
 *  ------------|---------------
 *  \ref Reset  | Mandatory
 *
 * Defines the StateMachine for asynchronous processing of temporary file transfers.
 *
 */
class SERVER_CORE_EXPORT FileTransferStateMachineType:
    public FileTransferStateMachineTypeBase
{
    UA_DISABLE_COPY(FileTransferStateMachineType);
protected:
    // destruction
    virtual ~FileTransferStateMachineType();
public:
    // construction
    FileTransferStateMachineType(const UaNodeId& nodeId, UaObject* pInstanceDeclarationObject, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    FileTransferStateMachineType(const UaNodeId& nodeId, const UaString& name, OpcUa_UInt16 browseNameNameSpaceIndex, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    FileTransferStateMachineType(
        UaBase::Object*    pBaseNode,
        XmlUaNodeFactoryManager*   pFactory,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);
    static void createTypes();
    static void clearStaticMembers();

    void setCallback(FileTransferStateMachineTypeCallback* pCallback);

    // UaFileTransferStateMachineType method Reset
    virtual UaStatus Reset(
        const ServiceContext& serviceContext);

protected:

private:
    FileTransferStateMachineTypeCallback* m_pCallback;
};

} // End namespace for the UA information model http://opcfoundation.org/UA/

#endif // #ifndef __OPCUAFILETRANSFERSTATEMACHINETYPE_H__

