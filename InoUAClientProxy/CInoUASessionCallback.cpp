#include "CInoUASessionCallback.h"
#include "ScopeExit.h"
#include "CInoUAClient.h"

CInoUASessionCallback::CInoUASessionCallback(CInoUAClient* pUAClient)
    : UaSessionCallback(), m_pUAClient(pUAClient)
{
}

CInoUASessionCallback::~CInoUASessionCallback()
{
}

// 描述：连接状态变更回调函数
// 时间：2021-10-20
// 备注：无
void CInoUASessionCallback::connectionStatusChanged(
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
            m_pUAClient->updateNamespaceIndexes();
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
        m_pUAClient->updateNamespaceIndexes();
        // 已注册的节点在新会话中不再有效
        m_pUAClient->registerNodes();
        break;
    }

    m_serverStatus = serverStatus;
}
