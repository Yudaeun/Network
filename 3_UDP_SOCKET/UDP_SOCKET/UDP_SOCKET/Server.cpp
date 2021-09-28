#pragma comment(lib, "ws2_32.lib");
#include "Winsock2.h"
#include <stdio.h>
#include <WS2tcpip.h>
#include <time.h>

#define MAX_BUF 5000
//21812167 유다은

int main() {
	WSADATA wsa;
	time_t t = time(NULL);
	struct tm tm;
	localtime_s(&tm, &t);

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		//소켓라이브러리가 로딩이 됐는지 안 됐는지 확인한다.
		//0아닌 값이 넘어오면 로딩이 안 된 것이다.
		printf("Error in starting up Winsock\n");
		return -1;
	}

	SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);
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
	} //bind()에서 오류가 난 경우

	SOCKADDR_IN clientAddress;
	int iAddressLength = sizeof(clientAddress);
	char chRxBuf[MAX_BUF] = { 0 };
	char chTxBuf[MAX_BUF] = "Hi, Client. Current time is";
	int chTxBuf1 = tm.tm_hour;
	int chTxBuf2 = tm.tm_sec;

	while (1) {
		printf("Waiting...\n");
		int iLength = recvfrom(s, chRxBuf, MAX_BUF, 0, (SOCKADDR*)&clientAddress, &iAddressLength);
		if (iLength == SOCKET_ERROR) {
			printf("Error in recvfrom(), Error code: %d\n", WSAGetLastError());
			closesocket(s);
			WSACleanup();
			return -1;
		}
		printf("Message receive from the Client: %s\n", chRxBuf);

		int rLength = sendto(s, chTxBuf, strlen(chTxBuf), 0, (SOCKADDR*)&clientAddress, sizeof(clientAddress));
		if (rLength == SOCKET_ERROR) {
			printf("Error in sendto(), Error code: %d\n", WSAGetLastError());
			closesocket(s);
			WSACleanup();
			return -1;
		}
		printf("Message send to the Client: %s\n", chTxBuf);

	}


	closesocket(s);
	WSACleanup();
	return 0;
}