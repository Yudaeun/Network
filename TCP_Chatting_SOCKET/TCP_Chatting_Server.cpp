#pragma comment(lib, "ws2_32.lib");
#include "Winsock2.h"
#include <stdio.h>
#include <WS2tcpip.h>
#include <time.h>

#define MAX_BUF 5000
#define MAX_CLIENT 100
//21812167 ������
//1. TCP������ �ϳ� ����
//2. Ŭ���̾�Ʈ�� ������ ��ٸ�
//3. Ŭ���̾�Ʈ�� �����Ͽ� �޽����� ������ 
//4. ���� �ð����� ����
//5. ȭ�鿡 ��� �ۼ��� ���ڿ��� ����ϰ� ���α׷��� ������ ������� �ʰ� ���� Ŭ���̾�Ʈ�� ��ٷ��� ��


SOCKET client[MAX_CLIENT]; 
//��� Ŭ���̾�Ʈ�� ������ ��Ƶα� ���� ���������迭: MAX_CLEINT�� �ִ�� ������ ����� Ŭ���̾�Ʈ�� ����

DWORD WINAPI thread_for_client(LPVOID pParam) {
	int idx = (int)pParam;
	SOCKET t = client[idx];

	char chRxBuf[MAX_BUF] = { 0 };
	while (1) {
		int iLength = recv(t, chRxBuf, MAX_BUF - 1, 0); //Ŭ���̾�Ʈ�κ��� �޽����� ����
		chRxBuf[iLength] = NULL;

		for (int i = 0; i < MAX_CLIENT; i++) {
			if ((client[i] != 0) && (client[i] != t)) { //�� ��ȭ������״� ���� �Ȱ��� ���� ���� �ʿ䰡 �����Ƿ� t�� �ƴϾ�� ��
				send(client[i], chRxBuf, strlen(chRxBuf), 0); //Ŭ���̾�Ʈ�κ��� �޴� �޽����� �����ؼ� send��
			}

		}	printf("Message recv from the Client: %s\n", chRxBuf);
	}
	client[idx] = 0;
	closesocket(t);
	return 0;
}
int main() {
	WSADATA wsa;
	time_t t = time(NULL);
	struct tm tm;
	localtime_s(&tm, &t);

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		//���϶��̺귯���� �ε��� �ƴ��� �� �ƴ��� Ȯ���Ѵ�.
		//0�ƴ� ���� �Ѿ���� �ε��� �� �� ���̴�.
		printf("Error in starting up Winsock\n");
		return -1;
	}

	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET) {
		printf("Error in socket(), Error code: %d\n", WSAGetLastError());
		WSACleanup();
		return -1;
	}
	SOCKADDR_IN myAddress;
	ZeroMemory(&myAddress, sizeof(myAddress));
	myAddress.sin_family = AF_INET;
	myAddress.sin_port = htons(50000);
	myAddress.sin_addr.s_addr = INADDR_ANY;

	if (bind(s, (SOCKADDR*)&myAddress, sizeof(myAddress)) == SOCKET_ERROR) {
		printf("Error in bind(), Error code: %d\n", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return -1;
	} //bind()���� ������ �� ���

	listen(s, 5);

	while (1) {

		SOCKADDR_IN clientAddress;
		int iAddressLength = sizeof(clientAddress);

		SOCKET t = accept(s, (SOCKADDR*)&clientAddress, &iAddressLength);

		int idx = -1;
		for (int i = 0; i < MAX_CLIENT; i++) {
			if (client[i] == 0) {
				idx = i;
				break;
			}
		}
		if (idx >= 0) {
			client[idx] = t;
			CreateThread(NULL, 0, thread_for_client, (LPVOID)idx, 0, NULL);
		}

	


	}


	closesocket(s);
	WSACleanup();
	return 0;
}