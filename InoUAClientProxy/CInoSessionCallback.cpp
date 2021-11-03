#include "CInoSessionCallback.h"
#include "ScopeExit.h"
#include "CInoSession.h"

CInoSessionCallback::CInoSessionCallback(CInoSession* pSession)
    : UaSessionCallback(), m_pSession(pSession)
{
}

CInoSessionCallback::~CInoSessionCallback()
{
}

// ����������״̬����ص�����
// ʱ�䣺2021-10-20
// ��ע����
void CInoSessionCallback::connectionStatusChanged(
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
        // ��ע��Ľڵ����»Ự�в�����Ч
        m_pSession->reRegisterNodes();
        break;
    }

    m_serverStatus = serverStatus;
}
