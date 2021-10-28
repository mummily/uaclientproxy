/******************************************************************************
** opcua_temporaryfiletransfertype.h
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

#ifndef __OPCUA_TEMPORARYFILETRANSFERTYPE_H__
#define __OPCUA_TEMPORARYFILETRANSFERTYPE_H__

#include "opcua_temporaryfiletransfertypebase.h"

// Namespace for the UA information model http://opcfoundation.org/UA/
namespace OpcUa {


class SERVER_CORE_EXPORT TemporaryFileTransferType;

/** Callback interface for handling incoming TemporaryFileTransfer Method calls
*/
class SERVER_CORE_EXPORT TemporaryFileTransferTypeCallback
{
public:
    TemporaryFileTransferTypeCallback() {}
    virtual ~TemporaryFileTransferTypeCallback() {}

    /**
    *  Close and commit the transaction
    *
    *  CloseAndCommit is used to apply the content of the written file and to delete the temporary file
    *  after the completion of the transaction.
    *
    *  <b>Method Result Codes</b>
    *
    *  Result Code               | Description
    *  --------------------------|-----------------------------------------------------------------------
    *  Bad_UserAccessDenied      | The user does not have permission to perform the requested operation.
    */
    virtual UaStatus CloseAndCommit(
        const ServiceContext& serviceContext /**<General context for the service calls containing
                                             information like the session object,
                                             return diagnostic mask and timeout hint.*/,
        OpcUa_UInt32 FileHandle,            /**<[in]  The fileHandle used to write the file.*/
        UaNodeId& CompletionStateMachine,   /**<[out] If the processing of the file is completed asynchronous,
                                             the parameter returns the NodeId of the corresponding FileTransferStateMachineType Object.
                                             If the processing of the file is already completed, the parameter is null.
                                             If a FileTransferStateMachineType Object NodeId is returned, the processing is in progress
                                             until the TransferState changed to Idle.*/
        TemporaryFileTransferType* pFileTransfer /**< Affected Object Node.*/
    ) = 0;

    /**
    *  GenerateFileForRead is used to start the read file transaction.
    *
    *  A successful call of this Method creates a temporary FileType Object with the file content
    *  and returns the NodeId of this Object and the file handle to access the Object.
    *
    *  <b>Method Result Codes</b>
    *
    *  Result Code               | Description
    *  --------------------------|-----------------------------------------------------------------------
    *  Bad_UserAccessDenied      | The user does not have permission to perform the requested operation.
    */
    virtual UaStatus GenerateFileForRead(
        const ServiceContext& serviceContext /**<General context for the service calls containing
                                             information like the session object,
                                             return diagnostic mask and timeout hint.*/,
        const UaVariant& GenerateOptions,   /**<[in]  The optional parameter can be used to specify server specific file generation
                                             options. To allow such options, the Server shall specify a concrete DataType in the Argument
                                             Structure for this argument in the instance of the Method.
                                             If the DataType is BaseDataType, the Client passes Null for this argument.*/
        UaNodeId& FileNodeId,               /**<[out]  NodeId of the temporary file. */
        OpcUa_UInt32& FileHandle,           /**<[out]  The fileHandle of the opened TransferFile.
                                            The fileHandle can be used to access the TransferFile Methods Read and Close.*/
        UaNodeId& CompletionStateMachine,   /**<[out]  If the creation of the file is completed asynchronous, the parameter returns the NodeId
                                            of the corresponding FileTransferStateMachineType Object.
                                            If the creation of the file is already completed, the parameter is null.
                                            If a FileTransferStateMachineType Object NodeId is returned, the Read Method of the file fails until
                                            the TransferState changed to ReadTransfer.*/
        TemporaryFileTransferType* pFileTransfer /**< Affected Object Node.*/
    ) = 0;

    /**
    * GenerateFileForWrite is used to start the write file transaction.
    *
    * A successful call of this Method creates a temporary FileType Object and returns the NodeId of this Object
    * and the file handle to access the Object.
    *
    *  <b>Method Result Codes</b>
    *
    *  Result Code               | Description
    *  --------------------------|-----------------------------------------------------------------------
    *  Bad_UserAccessDenied      | The user does not have permission to perform the requested operation.
    */
    virtual UaStatus GenerateFileForWrite(
        const ServiceContext& serviceContext /**<General context for the service calls containing
                                             information like the session object,
                                             return diagnostic mask and timeout hint.*/,
        const UaVariant& GenerateOptions,   /**<[in]  The optional parameter can be used to specify server specific file generation options.
                                            To allow such options, the Server shall specify a concrete DataType in the Argument Structure for
                                            this argument in the instance of the Method.
                                            If the DataType is BaseDataType, the Client passes Null for this argument.*/
        UaNodeId& FileNodeId,               /**<[out]  NodeId of the temporary file. */
        OpcUa_UInt32& FileHandle,           /**<[out]  The fileHandle of the opened TransferFile.
                                            The fileHandle can be used to access the TransferFile Methods Write and Close.*/
        TemporaryFileTransferType* pFileTransfer /**< Affected Object Node.*/
    ) = 0;

};

/** @brief Class implementing the UaObject interface for the TemporaryFileTransferType.
 *
 * OPC UA Objects are used to represent systems, system components, real-world objects and software
 * objects. They have the NodeClass @ref L3UaNodeClassObject. The detailed description of Objects and their attributes
 * can be found in the general description of the @ref L3UaNodeClassObject node class.
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
 *  ------------------------|----------|----------------|----------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *  ClientProcessingTimeout | Duration | PropertyType   | Mandatory      | \ref TemporaryFileTransferTypeBase::getClientProcessingTimeout "getClientProcessingTimeout", \ref TemporaryFileTransferTypeBase::setClientProcessingTimeout "setClientProcessingTimeout"
 *
 *  **Method members of the TemporaryFileTransferType:**
 *
 *  Browse Name               | Modelling Rule
 *  --------------------------|---------------
 *  \ref CloseAndCommit       | Mandatory
 *  \ref GenerateFileForRead  | Mandatory
 *  \ref GenerateFileForWrite | Mandatory
 *
 * Defines a type for the representation of temporary file transfers.
 *
 * The Methods GenerateFileForRead or GenerateFileForWrite generate a temporary FileType Object that is not browsable
 * in the AddressSpace and can only be accessed with the NodeId and FileHandle returned by the Methods in the same Session.
 * This Object is used to transfer the temporary file between OPC UA Client and Server.
 *
 * The Property ClientProcessingTimeout defines the maximum time in milliseconds the Server accepts between Method calls necessary
 * to complete a file read transfer or a file write transfer transaction. This includes the Method calls to read or write the file
 * content from the virtual temporary FileType Object. If the Client exceeds the timeout between Method calls, the Server may close
 * the file and cancel the corresponding transfer transaction. Any open temporary transfer file shall be deleted if the Session used
 * to create the file is no longer valid.
 *
 * The TransferState Objects are used to expose the state of a transfer transaction in the case that the preparation of a file for
 * reading or the processing of the file after writing completes asynchronous after the corresponding Method execution.
 * If the transactions are completed when the Method is returned, the optional TransferState Objects are not available. A Server
 * may allow more than one parallel read transfer. A Server may not allow more than one write
 * transfer or a parallel read and writer transfer.
 *
 * The read file transfer transaction is started with the Method GenerateFileForRead defined by
 * the TemporaryFileTransferType. After a successful call of this Method, the Client reads the file
 * content by calling the Method Read defined by the FileType until the whole file is transferred
 * from the Server to the Client. The transaction is completed by calling the Method Close defined
 * by the FileType.
 *
 * The write file transfer transaction is started with the Method StartWriteTransfer defined by the
 * TemporaryFileTransferType. After a successful call of this Method, the Client writes the file
 * content by calling the Method Write defined by the FileType until the whole file is transferred
 * from the Client to the Server. The transaction is completed by calling the Method
 * CloseAndCommit defined by the TemporaryFileTransferType. If the Client wants to abort the operation it uses the
 * Close Method of the temporary FileType Object.
 */
class SERVER_CORE_EXPORT TemporaryFileTransferType:
    public TemporaryFileTransferTypeBase
{
    UA_DISABLE_COPY(TemporaryFileTransferType);
protected:
    // destruction
    virtual ~TemporaryFileTransferType();
public:
    // construction
    TemporaryFileTransferType(const UaNodeId& nodeId, UaObject* pInstanceDeclarationObject, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    TemporaryFileTransferType(const UaNodeId& nodeId, const UaString& name, OpcUa_UInt16 browseNameNameSpaceIndex, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    TemporaryFileTransferType(
        UaBase::Object*    pBaseNode,
        XmlUaNodeFactoryManager*   pFactory,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);
    static void createTypes();
    static void clearStaticMembers();

    void setCallback(TemporaryFileTransferTypeCallback* pCallback);
    void setGenerateFileForReadGenerateOptionsDataType(const UaNodeId& dataType, const UaLocalizedText& description);
    void setGenerateFileForWriteGenerateOptionsDataType(const UaNodeId& dataType, const UaLocalizedText& description);

    // UaTemporaryFileTransferType method CloseAndCommit
    virtual UaStatus CloseAndCommit(
        const ServiceContext& serviceContext,
        OpcUa_UInt32 FileHandle,
        UaNodeId& CompletionStateMachine);
    // UaTemporaryFileTransferType method GenerateFileForRead
    virtual UaStatus GenerateFileForRead(
        const ServiceContext& serviceContext,
        const UaVariant& GenerateOptions,
        UaNodeId& FileNodeId,
        OpcUa_UInt32& FileHandle,
        UaNodeId& CompletionStateMachine);
    // UaTemporaryFileTransferType method GenerateFileForWrite
    virtual UaStatus GenerateFileForWrite(
        const ServiceContext& serviceContext,
        const UaVariant& GenerateOptions,
        UaNodeId& FileNodeId,
        OpcUa_UInt32& FileHandle);

protected:

private:
    TemporaryFileTransferTypeCallback* m_pCallback;
};

} // End namespace for the UA information model http://opcfoundation.org/UA/

#endif // #ifndef __OPCUATEMPORARYFILETRANSFERTYPE_H__

