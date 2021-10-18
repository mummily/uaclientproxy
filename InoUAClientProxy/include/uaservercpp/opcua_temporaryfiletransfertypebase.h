/******************************************************************************
** opcua_temporaryfiletransfertypebase.h
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

#ifndef __OPCUA_TEMPORARYFILETRANSFERTYPEBASE_H__
#define __OPCUA_TEMPORARYFILETRANSFERTYPEBASE_H__

#include "opcua_baseobjecttype.h"
#include "basenodes.h"
#include "opcua_identifiers.h"
#include "opcua_propertytype.h"
#include "uaargument.h"

// Namespace for the UA information model http://opcfoundation.org/UA/
namespace OpcUa {

class FileTransferStateMachineType;
class FiniteStateVariableType;
class PropertyType;

/** Generated base class for a TemporaryFileTransferType.
 *
 *  This class contains the generated base code for the object type TemporaryFileTransferType
 *  representing an OPC UA ObjectType. This class is used to create the object type and to
 *  create and represent instances of the object type in the server address space.
 *
 *  **Object members of the TemporaryFileTransferType:**
 *
 *  Browse Name       | TypeDefinition               | Modelling Rule      | See Also
 *  ------------------|------------------------------|---------------------|---------
 *  \<TransferState\> | FileTransferStateMachineType | OptionalPlaceholder | &nbsp;
 *
 *  **Variable members of the TemporaryFileTransferType:**
 *
 *  Browse Name             | DataType | TypeDefinition | Modelling Rule | See Also
 *  ------------------------|----------|----------------|----------------|-----------------------------------------------------------------
 *  ClientProcessingTimeout | Duration | PropertyType   | Mandatory      | \ref getClientProcessingTimeout, \ref setClientProcessingTimeout
 *
 */
class SERVER_CORE_EXPORT TemporaryFileTransferTypeBase:
    public OpcUa::BaseObjectType
{
    UA_DISABLE_COPY(TemporaryFileTransferTypeBase);
protected:
    virtual ~TemporaryFileTransferTypeBase();
public:
    // construction / destruction
    TemporaryFileTransferTypeBase(const UaNodeId& nodeId, UaObject* pInstanceDeclarationObject, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    TemporaryFileTransferTypeBase(const UaNodeId& nodeId, const UaString& name, OpcUa_UInt16 browseNameNameSpaceIndex, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    TemporaryFileTransferTypeBase(
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

    virtual UaStatus CloseAndCommit(
        const ServiceContext& serviceContext /**<General context for the service calls containing
                                                 information like the session object,
                                                 return diagnostic mask and timeout hint.*/,
        OpcUa_UInt32 FileHandle,
        UaNodeId& CompletionStateMachine) = 0;
    virtual UaStatus GenerateFileForRead(
        const ServiceContext& serviceContext /**<General context for the service calls containing
                                                 information like the session object,
                                                 return diagnostic mask and timeout hint.*/,
        const UaVariant& GenerateOptions,
        UaNodeId& FileNodeId,
        OpcUa_UInt32& FileHandle,
        UaNodeId& CompletionStateMachine) = 0;
    virtual UaStatus GenerateFileForWrite(
        const ServiceContext& serviceContext /**<General context for the service calls containing
                                                 information like the session object,
                                                 return diagnostic mask and timeout hint.*/,
        const UaVariant& GenerateOptions,
        UaNodeId& FileNodeId,
        OpcUa_UInt32& FileHandle) = 0;

    virtual void setClientProcessingTimeout(OpcUa_Double ClientProcessingTimeout);
    virtual OpcUa_Double getClientProcessingTimeout() const;

    virtual OpcUa::PropertyType* getClientProcessingTimeoutNode();
    virtual const OpcUa::PropertyType* getClientProcessingTimeoutNode() const;
    virtual OpcUa::BaseMethod* getCloseAndCommit();
    virtual const OpcUa::BaseMethod* getCloseAndCommit() const;
    virtual OpcUa::BaseMethod* getGenerateFileForRead();
    virtual const OpcUa::BaseMethod* getGenerateFileForRead() const;
    virtual OpcUa::BaseMethod* getGenerateFileForWrite();
    virtual const OpcUa::BaseMethod* getGenerateFileForWrite() const;

// Add placeholders
    virtual UaStatus addTransferState_Placeholder(OpcUa::FileTransferStateMachineType *pTransferState_Placeholder);

    // NodeAccessInfo management
    virtual void useAccessInfoFromType();
    void useAccessInfoFromInstance(TemporaryFileTransferTypeBase *pInstance);

protected:
    // Object nodes
    // Object TransferState_Placeholder
    static OpcUa::FileTransferStateMachineType*  s_pTransferState_Placeholder;

    // Variable nodes
    // Variable ClientProcessingTimeout
    static OpcUa::PropertyType*  s_pClientProcessingTimeout;
    OpcUa::PropertyType*  m_pClientProcessingTimeout;


    // Method nodes
    static OpcUa::BaseMethod* s_pCloseAndCommitMethod;
    OpcUa::BaseMethod*  m_pCloseAndCommitMethod;
    static OpcUa::BaseMethod* s_pGenerateFileForReadMethod;
    OpcUa::BaseMethod*  m_pGenerateFileForReadMethod;
    static OpcUa::BaseMethod* s_pGenerateFileForWriteMethod;
    OpcUa::BaseMethod*  m_pGenerateFileForWriteMethod;

    // Special handling for input arguments for
    UaPropertyMethodArgument* m_pInputArgumentPropertyGenerateFileForRead;
    UaPropertyMethodArgument* m_pInputArgumentPropertyGenerateFileForWrite;

private:
    void initialize();

private:
    static bool s_typeNodesCreated;
};

} // End namespace for the UA information model http://opcfoundation.org/UA/

#endif // #ifndef __OPCUATEMPORARYFILETRANSFERTYPEBASE_H__


