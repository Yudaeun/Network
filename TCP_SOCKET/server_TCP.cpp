#pragma comment(lib, "ws2_32.lib");
#include "Winsock2.h"
#include <stdio.h>
#include <WS2tcpip.h>
#include <time.h>

#define MAX_BUF 5000
//21812167 ������
//1. TCP������ �ϳ� ����
//2. Ŭ���̾�Ʈ�� ������ ��ٸ�
//3. Ŭ���̾�Ʈ�� �����Ͽ� �޽����� ������ 
//4. ���� �ð����� ����
//5. ȭ�鿡 ��� �ۼ��� ���ڿ��� ����ϰ� ���α׷��� ������ ������� �ʰ� ���� Ŭ���̾�Ʈ�� ��ٷ��� ��

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

	while(1){
	
	SOCKADDR_IN clientAddress;
	int iAddressLength = sizeof(clientAddress);

	SOCKET t = accept(s, (SOCKADDR*)&clientAddress, &iAddressLength);
	const char chTxBuf[MAX_BUF] = "Hi, Client. Current time is ...";
	send(t, chTxBuf, strlen(chTxBuf), 0);

	char chRxBuf[MAX_BUF] = { 0 };
	int iLength = recv(t, chRxBuf, MAX_BUF, 0);

	//int chTxBuf1 = tm.tm_hour;
	//int chTxBuf2 = tm.tm_min;

	/* while (1) {
		printf("Waiting...\n");
		int iLength = recvfrom(s, chRxBuf, MAX_BUF, 0, (SOCKADDR*)&clientAddress, &iAddressLength);
		if (iLength == SOCKET_ERROR) {
			printf("Error in recvfrom(), Error code: %d\n", WSAGetLastError());
			closesocket(s);
			WSACleanup();
			return -1;
		}*/
		printf("Message receive from the Client: %s\n", chRxBuf);

		/*int rLength = sendto(s, chTxBuf, strlen(chTxBuf), 0, (SOCKADDR*)&clientAddress, sizeof(clientAddress));


		if (rLength == SOCKET_ERROR) {
			printf("Error in sendto(), Error code: %d\n", WSAGetLastError());
			closesocket(s);
			WSACleanup();
			return -1;
		}*/
		printf("Message send to the Client: %s\n", chTxBuf);

	}


	closesocket(s);
	WSACleanup();
	return 0;
}