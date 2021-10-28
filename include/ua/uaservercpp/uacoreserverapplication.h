/******************************************************************************
** uacoreserverapplication.h
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
** Description: OPC Server Application object.
**
******************************************************************************/
#ifndef UACORESERVERAPPLICATION_H
#define UACORESERVERAPPLICATION_H

#include <uaapplication.h>
#include "uaserverapplicationmodule.h"
#include "serverconfig.h"
#include "nodemanager.h"

class UaCoreServerApplicationPrivate;
class UaServerApplicationCallback;
class UaDurableSubscriptionCallback;
class UaServer;
class CoreModule;
class ServerManager;

/** Base class for the main OPC Server management object.

  This class is a utility class managing all server SDK modules for common use cases in a simplified way.
  Enhanced users may replace this class with their own implementation to be able
  to use derived classes to overwrite SDK functionality.

  A derived class must implement the methods afterInitialize(), afterStartUp() and beforeShutdown().
  In addition the derived class must add the following code to the destructor to make sure beforeShutdown()
  is called before the object is deleted.

  @code
    if ( isStarted() != OpcUa_False )
    {
        UaLocalizedText reason("en","Application shut down");
        stop(0, reason);
    }
  @endcode

  */
class SERVER_CORE_EXPORT UaCoreServerApplication : public UaApplication
{
    UA_DISABLE_COPY(UaCoreServerApplication);
public:
    // construction / destruction
    UaCoreServerApplication();
    UaCoreServerApplication(int argc, char* argv[], bool bRunAsService, const UaString &sApplicationName);
    virtual ~UaCoreServerApplication();

    // Methods used to initialize the server
    int setServerConfig(const UaString& configurationFile, const UaString& sApplicationPath);
    int setServerConfig(const UaString& configurationFile, const UaString& sApplicationPath, const UaString& sConfigPath, const UaString& sTracePath);
    int setServerConfig(ServerConfig* pServerConfig);
    int addNodeManager(NodeManager* pNodeManager);
    int addModule(UaServerApplicationModule* pModule);
    int removeNodeManager(NodeManager* pNodeManager);
    int removeModule(UaServerApplicationModule* pModule);
    int setCallback(UaServerApplicationCallback* pUaServerApplicationCallback);
    void setSecondsTillShutdown(OpcUa_Int32 secondsTillShutdown);
    void setShutdownReason(const UaLocalizedText& shutdownReason);

    // Methods used to start and stop the server
    int start();
    int stop(OpcUa_Int32 secondsTillShutdown, const UaLocalizedText& shutdownReason);

    // Access to members
    NodeManagerConfig* getDefaultNodeManager();
    ServerManager*     getServerManager();
    ServerConfig*      getServerConfig();
    CoreModule*        getCoreModule();
    OpcUa_Boolean      isStarted();
    OpcUa_Int32        secondsTillShutdown();
    UaLocalizedText    shutdownReason();

    /** Creates a session object for the OPC server.
     *  This is the default implementation. It can be overwritten by implementing the UaServerApplicationCallback.
     *  @param sessionID            Session Id created by the server application.
     *  @param authenticationToken  Secret session Id created by the server application.
     *  @return                     A pointer to the created session.
     */
    virtual Session* createDefaultSession(OpcUa_Int32 sessionID, const UaNodeId &authenticationToken) = 0;

    virtual OpcUa_DateTime getBuildDate() const;

    UaServerApplicationCallback* getServerApplicationCallback();

protected:
    /** This method needs to be implemented by the derived class and is called to finish the initialization of the UaCoreServerApplication.
     *  This method is typically used to initialize the communication modules like the UaModule.
     *  @return Result code
     */
    virtual UaStatus afterInitialize() = 0;

    /** This method needs to be implemented by the derived class and is called to finish the start-up of the UaCoreServerApplication.
     *  This method is typically used to start up the communication modules like the UaModule.
     *  @return Result code
     */
    virtual UaStatus afterStartUp() = 0;

    /** This method needs to be implemented by the derived class and is called to start the shutdown of the UaCoreServerApplication.
     *  This method is typically used to stop the communication modules like the UaModule.
     *  @return Result code
     */
    virtual UaStatus beforeShutdown() = 0;

    virtual int main();

private:
    UaCoreServerApplicationPrivate* d;
};


/** Callback interface for the Server application object.
 This callback interface needs to be implemented if the application wants to implement user authentication.
 */
class SERVER_CORE_EXPORT UaServerApplicationCallback
{
public:
    /** Construction */
    UaServerApplicationCallback(){}
    /** Destruction */
    virtual ~UaServerApplicationCallback(){}

    /** Creates a session object for the OPC server.
     * This callback allows the application to create its own session class derived from UaSession to store
     * user specific information and to implement the user log-on and user verification.
     * @param sessionID            Session Id created by the server application.
     * @param authenticationToken  Secret session Id created by the server application.
     * @return                     A pointer to the created session.
     */
    virtual Session* createSession(OpcUa_Int32 sessionID, const UaNodeId &authenticationToken) = 0;

    /** Validates the user identity token and sets the user for the session.
     *  @param pSession             Interface to the Session context for the method call
     *  @param pUserIdentityToken   Secret session Id created by the server application.
     *  @param pServerConfig        The server configuration interface
     *  @return                     Error code.
     */
    virtual UaStatus logonSessionUser(Session* pSession, UaUserIdentityToken* pUserIdentityToken, ServerConfig* pServerConfig) = 0;

    /** Optional method used to inform the application that the configuration was loaded.
     * This callback allows the application to overwrite settings from configuration files before the server is started. This ensures
     * that hard coded settings can not be changed by entering the configuration setting into the configuration file.
     * @param pServerConfig        The server configuration interface
     */
    virtual void afterLoadConfiguration(ServerConfig* pServerConfig);

    /** Optional method used to create an application specific UaServer object used as main entry point for the UA communication.
     *  The SDK creates an instance of the UaServer class as default implementation.
     *  @return UaServer object or NULL if the SDK should use the default implementation.
     */
    virtual UaServer* createUaServer() { return NULL; }

    virtual UaDurableSubscriptionCallback* getDurableSubscriptionCallback() { return NULL; }

    /** Optional method to requests the state change, shutdown or restart of the OPC UA Server application.
     *  @return  Result of the request. If the result tis Good, the application must folwow the request. If the result is Bad, the application will not change state.
     */
    virtual UaStatus requestServerStateChange(
        Session*               pSession,            //!< [in] Session context for the client request
        OpcUa_ServerState      state,               //!< [in] The requested target state for the Server
        const UaDateTime&      estimatedReturnTime, //!< [in] Indicates the time at which the Server is expected to be available in the state RUNNING_0.
        OpcUa_UInt32           secondsTillShutdown, //!< [in] Seconds till shutdown of the server. This parameter is ignored unless the state is set to SHUTDOWN_4 or restart is set to True.
        const UaLocalizedText& shutdownReason,      //!< [in] Reason for the shutdown
        OpcUa_Boolean          restart              //!< [in] A flag indicating if the Server should be restarted after shutdown
        );

    /** Optional method providing information about an endpoint that will be opened and the certificate that will be used by the server.
     *
     *  This callbacks allows certificate checks or the creation of a certificate before it is created by the SDK.
     *  \ref UaEndpoint::pEndpointCertificateSettings() returns the certificate configuration used by the endpoint
     */
    virtual void beforeEndpointOpen(
        UaEndpoint* pEndpoint,           //!< [in] UaEndpoint that will be opened by the server
        bool        certificateAvailable //!< [in] Flag indicating if a certificate is available
        );

    /** Optional method used to inform the application that the CoreModules was started.
    * This callback allows the application to add roles that are used server wide (roles in namespace1.
    */
    virtual void afterCoreModuleStarted();

    /** Optional method used to inform the application that all NodeManagers were started.
    * This callback allows the application to add rules to existing roles e.g. assing OperatorRole to user 'john'.
    */
    virtual void afterNodeManagersStarted();

    /** Optional method used to inform the application that all Modules were started.
    */
    virtual void afterModulesStarted();

    /** Optional method used to inform the application that a Role was added.
    */
    virtual void roleAdded(RoleTypeOperations* pRoleTypeOperations);

    /** Optional method used to inform the application that a Role was modified.
    */
    virtual void roleModified(RoleTypeOperations* pRoleTypeOperations);

    /** Optional method used to inform the application that a Role was removed.
    */
    virtual void roleRemoved(RoleTypeOperations* pRoleTypeOperations);
};

/* Description */
typedef UaObjectPointerArray<UaVariantArray> EventFieldsArray;

/** Callback interface for the handling of durable subscriptions storage.
*
* This callback interface needs to be implemented if the application wants to implement durable subscriptions.
*
* The storage works like list of buffers where each buffer represents a monitored item in a durable subscription. The buffer
* is only active if the delivery of data changes is not possible to the client.
*
* If a buffer is active, it has a read pointer at the begin of the buffer and a writer pointer at the end of the buffer.
*/
class SERVER_CORE_EXPORT UaDurableSubscriptionCallback
{
public:
    /** Construction */
    UaDurableSubscriptionCallback() {}
    /** Destruction */
    virtual ~UaDurableSubscriptionCallback() {}

    /** This registration method informs the storage component about the creation of a data monitored item in a durable subscription.
    *
    * The storage stays inactive until the delivery of values to the client is interrupted.
    *  @return The handle of the durable data monitored item in the storage component. 0 is invalid and is returned if it is not
    *          possible to add more items.
    */
    virtual OpcUa_UInt32 registerDurableDataItem(
        const UaNodeId     nodeId,           //!< [in] NodeId of the monitored node
        OpcUa_UInt32       subscriptionId,   //!< [in] ID of the durable subscription the monitored item was added to
        OpcUa_Double&      samplingInterval, /**< [in/out] SamplingInterval configured for the monitoring.
                                                           The sampling interval can be adjusted to a lower rate if the rate is not
                                                           supported by the storage.*/
        OpcUa_UInt32&      queueSize)        /**< [in/out] Queue size configured for the monitored item.
                                                           The queue size can be adjusted to a lower number if the size is not
                                                           supported by the storage.*/
        = 0;

    /** This registration method informs the storage component about the creation of an event monitored item in a durable subscription.
    *
    * The storage stays inactive until the delivery of events to the client is interrupted.
    *  @return The handle of the durable event monitored item in the storage component. 0 is invalid and is returned if it is not
    *          possible to add more items.
    */
    virtual OpcUa_UInt32 registerDurableEventItem(
        const UaNodeId     nodeId,            //!< [in] NodeId of the monitored node
        OpcUa_UInt32       subscriptionId)    //!< [in] ID of the durable subscription the monitored item was added to
        = 0;

    /** Unregisters the item from the storage component after the deletion of the monitored item from the durable subscription.
    */
    virtual void unregisterDurableItem(
        OpcUa_UInt32       durableItemHandle) //!< [in] The handle of the durable monitored item in the storage component.
        = 0;

    /** Activates the item in the storage component before storeValue is called.
    *
    * The activation happens if the durable subscription is no longer able to deliver values or events to the client.
    */
    virtual void activateDurableItem(
        OpcUa_UInt32       durableItemHandle) //!< [in] The handle of the durable monitored item in the storage component.
        = 0;

    /** Deactivates the item in the storage component.
    *
    * The deactivation happens if the durable subscription has delivered all stored values and events to the client and all new values
    * and events are delivered to the client directly. This allows the storage component to clean-up all previously stored values.
    */
    virtual void deactivateDurableItem(
        OpcUa_UInt32       durableItemHandle) //!< [in] The handle of the durable monitored item in the storage component.
        = 0;

    /** Stores the value at the end of the buffer.
    */
    virtual void storeValue(
        OpcUa_UInt32       durableItemHandle, //!< [in] The handle of the durable monitored item in the storage component.
        const UaDataValue& dataValue)         //!< [in] The DataValue to store.
        = 0;

    /** Returns the stored values for the item from the beginning of the buffer.
    *
    * The method returns the requested number of stored values or the remaining ones if the number of stored values is less than
    * requested.
    *
    * If the method is called, all previously fetched stored values can be deleted or can be marked as delivered to the client.
    * @return A flag indicating if there are more values. False indicates that all remaining stored values are returned.
    */
    virtual bool getStoredValues(
        OpcUa_UInt32       durableItemHandle, //!< [in] The handle of the durable monitored item in the storage component.
        OpcUa_UInt32       requestCount,      //!< [in] The number of values requested from storage.
        UaDataValueArray&  dataValues)        //!< [out] The stored values in the order they have been received through storeValue.
        = 0;

    /** Confirms delivery of stored values to the client.
    *
    * The method is only used if stored values have be partially delivered to the client and delivery has stopped again.
    *
    * If the method is called, the indicated number of previously fetched stored values can be deleted or can be marked as delivered
    * to the client. The rest of the values returned in getStoredValues must be returned again in the next call to getStoredValues.
    */
    virtual void clearStoredValues(
        OpcUa_UInt32       durableItemHandle, //!< [in] The handle of the durable monitored item in the storage component.
        OpcUa_UInt32       clearCount)        //!< [in] The number of values delivered to the client.
        = 0;

    /** Stores the event at the end of the buffer.
    */
    virtual void storeEvent(
        OpcUa_UInt32          durableItemHandle, //!< [in] The handle of the durable monitored item in the storage component.
        const UaVariantArray& eventFields)       //!< [in] The Event (fields of the event) to store.
        = 0;

    /** Get the current event count in the buffer.
    *
    * If the number is unknown, the maxNumber passed in is returned if events are available and 0 is returned if no events are available
    */
    virtual OpcUa_UInt32 getEventCount(
        OpcUa_UInt32 durableItemHandle, //!< [in] The handle of the durable monitored item in the storage component.
        OpcUa_UInt32 maxNumber) //!< [in] The maximum number that can be handled by the caller.
        = 0;

    /** Get Events from the buffer.
    *
    * Returns the events from the buffer up to the number defined by eventCount.
    * Returned events can be deleted or can be marked as delivered to the client.
    */
    virtual void getEvents(
        OpcUa_UInt32 durableItemHandle, //!< [in] The handle of the durable monitored item in the storage component.
        OpcUa_UInt32& eventCount, //!< [in/out] The requested and returned count. If the number equals or exeeds the available events, the complete list is returned
        EventFieldsArray& events, //!< [out] The list of events in the monitored item
        bool& bMoreAvailable) //!< [out] Flag indicating if there are more events in the buffer
        = 0;
};

#endif // UACORESERVERAPPLICATION_H


