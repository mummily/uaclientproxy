/******************************************************************************
** opcua_filetransferstatemachinetypebase.h
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

#ifndef __OPCUA_FILETRANSFERSTATEMACHINETYPEBASE_H__
#define __OPCUA_FILETRANSFERSTATEMACHINETYPEBASE_H__

#include "opcua_finitestatemachinetype.h"
#include "basenodes.h"
#include "opcua_identifiers.h"
#include "opcua_propertytype.h"

// Namespace for the UA information model http://opcfoundation.org/UA/
namespace OpcUa {

class InitialStateType;
class PropertyType;
class StateType;
class TransitionType;

/** Generated base class for a FileTransferStateMachineType.
 *
 *  This class contains the generated base code for the object type FileTransferStateMachineType
 *  representing an OPC UA ObjectType. This class is used to create the object type and to
 *  create and represent instances of the object type in the server address space.
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
 */
class SERVER_CORE_EXPORT FileTransferStateMachineTypeBase:
    public OpcUa::FiniteStateMachineType
{
    UA_DISABLE_COPY(FileTransferStateMachineTypeBase);
protected:
    virtual ~FileTransferStateMachineTypeBase();
public:
    enum FileTransferState
    {
        ApplyWrite,
        Error,
        Idle,
        ReadPrepare,
        ReadTransfer
    };

    // construction / destruction
    FileTransferStateMachineTypeBase(const UaNodeId& nodeId, UaObject* pInstanceDeclarationObject, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    FileTransferStateMachineTypeBase(const UaNodeId& nodeId, const UaString& name, OpcUa_UInt16 browseNameNameSpaceIndex, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    FileTransferStateMachineTypeBase(
        UaBase::Object*    pBaseNode,
        XmlUaNodeFactoryManager*   pFactory,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);
    static void createTypes();
    static void clearStaticMembers();

    virtual UaNodeId       typeDefinitionId() const;


    //- Interface MethodManager -----------------------------------------------------------
    /** Call method of an UA object. */
    virtual UaStatus beginCall(
        MethodManagerCallback* pCallback,
        const ServiceContext&  serviceContext,
        OpcUa_UInt32           callbackHandle,
        MethodHandle*          pMethodHandle,
        const UaVariantArray&  inputArguments);
    virtual UaStatus call(
        const ServiceContext&  serviceContext,
        MethodHandle*          pMethodHandle,
        const UaVariantArray&  inputArguments,
        UaVariantArray&        outputArguments,
        UaStatusCodeArray&     inputArgumentResults,
        UaDiagnosticInfos&     inputArgumentDiag);
    //- Interface MethodManager -----------------------------------------------------------

    virtual UaStatus Reset(
        const ServiceContext& serviceContext /**<General context for the service calls containing
                                                 information like the session object,
                                                 return diagnostic mask and timeout hint.*/) = 0;

    virtual OpcUa::BaseMethod* getReset();
    virtual const OpcUa::BaseMethod* getReset() const;

    UaStatus setFileTransferState(FileTransferState state);
    FileTransferState getFileTransferState();
    // NodeAccessInfo management
    virtual void useAccessInfoFromType();
    void useAccessInfoFromInstance(FileTransferStateMachineTypeBase *pInstance);

protected:
    // Object nodes
    // Object ApplyWrite
    static OpcUa::StateType*  s_pApplyWrite;
    // Object ApplyWriteToError
    static OpcUa::TransitionType*  s_pApplyWriteToError;
    // Object ApplyWriteToIdle
    static OpcUa::TransitionType*  s_pApplyWriteToIdle;
    // Object Error
    static OpcUa::StateType*  s_pError;
    // Object ErrorToIdle
    static OpcUa::TransitionType*  s_pErrorToIdle;
    // Object Idle
    static OpcUa::InitialStateType*  s_pIdle;
    // Object IdleToApplyWrite
    static OpcUa::TransitionType*  s_pIdleToApplyWrite;
    // Object IdleToReadPrepare
    static OpcUa::TransitionType*  s_pIdleToReadPrepare;
    // Object ReadPrepare
    static OpcUa::StateType*  s_pReadPrepare;
    // Object ReadPrepareToError
    static OpcUa::TransitionType*  s_pReadPrepareToError;
    // Object ReadPrepareToReadTransfer
    static OpcUa::TransitionType*  s_pReadPrepareToReadTransfer;
    // Object ReadTransfer
    static OpcUa::StateType*  s_pReadTransfer;
    // Object ReadTransferToError
    static OpcUa::TransitionType*  s_pReadTransferToError;
    // Object ReadTransferToIdle
    static OpcUa::TransitionType*  s_pReadTransferToIdle;


    // Method nodes
    static OpcUa::BaseMethod* s_pResetMethod;
    OpcUa::BaseMethod*  m_pResetMethod;


private:
    void initialize();

private:
    static bool s_typeNodesCreated;
};

} // End namespace for the UA information model http://opcfoundation.org/UA/

#endif // #ifndef __OPCUAFILETRANSFERSTATEMACHINETYPEBASE_H__


