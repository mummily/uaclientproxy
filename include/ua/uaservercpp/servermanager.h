/******************************************************************************
** servermanager.h
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
** Project: C++ OPC Server SDK core module
**
** Description: OPC server core module interface.
**
******************************************************************************/
#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include "servermanagerhelper.h"
#include "opcuatypesinternal.h"

class RoleTypeOperations;
class NodeManagerRoot;
class UaCoreServerApplication;
class UaServerApplicationCallback;

/** Main management class of the server core module
 *
 *  The class manages the central components of the server core module like NodeManagerRoot and SessionManager.
 *  The object is passed to all NodeManagers and modules during start up.
 *
 *  The class provides also an internal client API that can be used to retrieve information provided by the server.
 *  It is using the information already provided for OPC UA Clients. There are no changes required in the data
 *  integration modules implementing the interfaces like NodeManager and IOManager.
 */
class SERVER_CORE_EXPORT ServerManager
{
    UA_DISABLE_COPY(ServerManager);
public:
    /* construction. */
    ServerManager();
    /* destruction */
    virtual ~ServerManager();

    //  Start up server manager.
    UaStatus startUp( ServerConfig* pServerConfig );

    //  Shut down server manager.
    UaStatus shutDown();

    //  Returns the server configuration object.
    ServerConfig* getServerConfig();

    //  Returns the root node manager object.
    NodeManagerRoot* getNodeManagerRoot();

    //  Returns the node manager object responsible for namespace index 1 nodes.
    NodeManager* getNodeManagerNS1();

    //  Returns the OPC UA Session manager object.
    SessionManager* getSessionManager();

#if SUPPORT_Historical_Access
    // Returns history server capability object
    OpcUa::HistoryServerCapabilitiesType* getHistoryServerCapabilities();
#endif // SUPPORT_Historical_Access

    //  Returns the thread pool of the server core module.
    UaThreadPool*   getThreadPool();

#if SUPPORT_Event_Subscription_Server_Facet
    void registerDynamicEventManager(EventManager* pEventManager);
    void connectEventManagerRegisteredCallback(EventManagerRegisteredCallback* pCallback);
    void disconnectEventManagerRegisteredCallback(EventManagerRegisteredCallback* pCallback);
#endif // SUPPORT_Event_Subscription_Server_Facet

    void registerServerShutdownCallback(ServerShutDownCallback* pCallback);

    void registerApplicationControlCallback(UaApplicationControlCallback* pCallback);
    UaApplicationControlCallback* getApplicationControlCallback();
    void setServerApplication(UaCoreServerApplication* pServerApplication);

    //  Inform the server manager about the shutdown of the server.
    OpcUa_UInt32 startServerShutDown(
        OpcUa_Int32            secondsTillShutdown,
        const UaLocalizedText& shutdownReason);
    OpcUa_UInt32 startServerShutDown(
        OpcUa_Int32                 secondsTillShutdown,
        const UaLocalizedTextArray& shutdownReason);

    //  Update status information in the server object.
    void changeServerState(OpcUa_ServerState newState);
    void changeServiceLevel(OpcUa_Byte serviceLevel, OpcUa_Byte changeMask);

    // Return the internal session with root rights.
    Session* getInternalSession();

    // Internal session creation
    Session* createInternalSession(const UaString& sessionName, const UaString& localeId, UaUserIdentityToken* pUserIdentityToken);

    // Get namespace array of server
    UaStatus getNamespaceTable(UaStringArray& sNamespaces);

    // Browse functions for internal use
    UaStatus browse(const UaNodeId& startingNode, const UaNodeId& referenceTypeFilter, ContinuationPointWrapper& continuationPoint, UaReferenceDescriptions& references);
    UaStatus browse(const UaNodeId& startingNode, OpcUa_Boolean isInverse, const UaNodeId& referenceTypeFilter, OpcUa_UInt32 nodeClassMask, ContinuationPointWrapper& continuationPoint, UaReferenceDescriptions& references);
    UaStatus browse(Session* pSession, const UaNodeId& startingNode, ContinuationPointWrapper& continuationPoint, UaReferenceDescriptions& references);
    UaStatus browse(Session* pSession, const UaNodeId& startingNode, OpcUa_Boolean isInverse, const UaNodeId& referenceTypeFilter, OpcUa_UInt32 nodeClassMask, ContinuationPointWrapper& continuationPoint, UaReferenceDescriptions& references);

    // Read functions for internal use
    UaStatus read(Session* pSession, OpcUa_Double maxAge, const UaReadValueIds& nodesToRead, UaDataValues& results);
    UaStatus read(Session* pSession, OpcUa_Double maxAge, const PVariableHandleArray& variableHandles, const UaReadValueIds& nodesToRead, UaDataValues& results);

    // Write functions for internal use
    UaStatus write(Session* pSession, const UaWriteValues& nodesToWrite, UaStatusCodeArray& results);
    UaStatus write(Session* pSession, const PVariableHandleArray& variableHandles, const UaWriteValues& nodesToWrite, UaStatusCodeArray& results);

#if SUPPORT_Method_Server_Facet
    // Call function for internal use
    UaStatus call(Session* pSession, const UaNodeId& objectId, const UaNodeId& methodId, const UaVariantArray& inputArguments,
        UaStatusCodeArray& inputArgumentResults, UaVariantArray& outputArguments);
#endif // SUPPORT_Method_Server_Facet

    // Monitoring functions for internal use
    UaStatus createDataMonitoredItems(Session* pSession, DataMonitoredItemSpecArray& dataMonitoredItems);
#if SUPPORT_Event_Subscription_Server_Facet
    UaStatus createEventMonitoredItem(Session* pSession, const UaNodeId& objectToMonitor, EventCallback* pEventCallback, OpcUa_EventFilter* pEventFilter,
        OpcUa_UInt32& monitoredItemId);
    void setEventManagerInvalid(OpcUa_UInt32 monitoredItemId, OpcUa_UInt32 eventManagerIndex);
    UaStatus conditionRefresh(Session* pSession, OpcUa_UInt32 monitoredItemId);
#endif // SUPPORT_Event_Subscription_Server_Facet
    UaStatus deleteMonitoredItems(Session* pSession, const UaUInt32Array& monitoredItemIds, UaStatusCodeArray& results);

#if USE_IOManager2_Interface
    std::list<IOManager2*> getListIOManager2();
    UaStatus registerIOManager2(IOManager2* pIOManager2);
#endif // USE_IOManager2_Interface

    static void createPreTraceEvents();
    static void clearPreTraceEvents();

    UaStatus addRole(
        const UaString& sRoleName,      // IN
        const UaString& sNamespaceUri,  // IN
        RoleTypeOperations** ppRoleTypeOperations); // OUT - RoleTypeOperations

    // remove role from Management
    UaStatus removeRole(RoleTypeOperations* pRoleTypeOperations);

    // adds Role to Management and set the RoleId
    UaStatus registerRole(RoleTypeOperations* pRoleTypeOperations);
    // remove Role from Management
    UaStatus unregisterRole(RoleTypeOperations* pRoleTypeOperations);

    // get the internal Id for a well known role
    OpcUa_UInt32 getIdForWellKnownRole(OpcUa_UInt32 numericIdentifier) const;
    // get Role NodeId for internal Id
    UaNodeId getRoleNodeId(OpcUa_UInt32 roleId) const;
    // get the internal Id for Role defined by NodeId
    OpcUa_UInt32 getRoleId(const UaNodeId& roleNodeId) const;
    // assign roleIds to the SessionUserContext associated with this session
    UaStatus setRoleIds(const Session* pSession) const;

    // find role by roleId
    UaStatus getRoleByRoleId(
        const OpcUa_UInt32 roleId,                          // IN
        RoleTypeOperations** ppRoleTypeOperations) const;   // OUT - pointer to RoleTypeOperation interface

    // find role by NodeId
    UaStatus getRoleByNodeId(
        const UaNodeId& roleNodeId,                         // IN
        RoleTypeOperations** ppRoleTypeOperations) const;   // OUT - pointer to RoleTypeOperation interface

    // find role by name and uri
    UaStatus getRoleByName(
        const UaString& sRoleName,                          // IN
        const UaString& sNamespaceUri,                      // IN
        RoleTypeOperations** ppRoleTypeOperations) const;   // OUT - pointer to RoleTypeOperation interface

    UaStatus roleModified(RoleTypeOperations* pRoleTypeOperations);

protected:
    virtual SessionManager* createSessionManager();
    virtual NodeManager*    createNodeManagerNS1(const UaString& sServerUri);

private:
    /** Flag indicating if the module was started. */
    OpcUa_Boolean    m_isStarted;
    /** Flag indicating that the startup failed. */
    OpcUa_Boolean    m_isStartUpError;
    /** Server configuration object */
    ServerConfig*    m_pServerConfig;
    /** Root node manager object */
    NodeManagerRoot* m_pNodeManagerRoot;
    /** Root node manager object */
    NodeManager*     m_pNodeManagerNS1;
    /** Session manager object */
    SessionManager*  m_pSessionManager;
#if USE_IOManager2_Interface
    std::list<IOManager2*> m_listIOManager2;
#endif // USE_IOManager2_Interface
#if SUPPORT_Event_Subscription_Server_Facet
    std::list<EventManagerRegisteredCallback*> m_listEventManagerRegisteredCallbacks;
#endif // SUPPORT_Event_Subscription_Server_Facet
    std::list<ServerShutDownCallback*> m_listServerShutDownCallbacks;
    UaMutex           m_listMutex;
    // Transaction handling for internal calls
    CoreTransactions* m_pCoreTransactions;
    UaThreadPool*     m_pThreadPool;
    UaApplicationControlCallback* m_pApplicationControl;
    UaCoreServerApplication* m_pServerApplication;
    UaServerApplicationCallback* m_pServerApplicationCallback;
    /** Internal Session used for internal calls */
    Session*        m_pInternalSession;
};

#endif // SERVERMANAGER_H
