#include "InoSessionCallback.h"
#include "ScopeExit.h"
#include "InoSession.h"

InoSessionCallback::InoSessionCallback(InoSession* pSession)
    : UaSessionCallback(), m_pSession(pSession)
{
}

InoSessionCallback::~InoSessionCallback()
{
}

// 描述：连接状态变更回调函数
// 时间：2021-10-20
// 备注：无
void InoSessionCallback::connectionStatusChanged(
    OpcUa_UInt32             clientConnectionId,
    UaClient::ServerStatus   serverStatus)
{
    OpcUa_ReferenceParameter(clientConnectionId);

    printf("-------------------------------------------------------------\n");
    SCOPE_EXIT(
        printf("-------------------------------------------------------------\n");
    );

    switch (serverStatus)
    {
    case UaClient::Disconnected:
        printf("Connection status changed to Disconnected\n");
        break;
    case UaClient::Connected:
        printf("Connection status changed to Connected\n");
        if (m_serverStatus != UaClient::NewSessionCreated)
        {
            m_pSession->updateNamespaceIndexes();
        }
        break;
    case UaClient::ConnectionWarningWatchdogTimeout:
        printf("Connection status changed to ConnectionWarningWatchdogTimeout\n");
        break;
    case UaClient::ConnectionErrorApiReconnect:
        printf("Connection status changed to ConnectionErrorApiReconnect\n");
        break;
    case UaClient::ServerShutdown:
        printf("Connection status changed to ServerShutdown\n");
        break;
    case UaClient::NewSessionCreated:
        printf("Connection status changed to NewSessionCreated\n");
        m_pSession->updateNamespaceIndexes();
        // 已注册的节点在新会话中不再有效
        m_pSession->reRegisterNodes();
        break;
    }

    m_serverStatus = serverStatus;
}
