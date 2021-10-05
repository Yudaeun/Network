#pragma comment(lib, "ws2_32.lib");
#include "Winsock2.h"
#include <stdio.h>
#include <WS2tcpip.h>
#include <time.h>
#define MAX_BUF 5000

//21812167 유다은
//1. TCP 소켓 하나 생성
//2. 서버에게 메시지 송신
//3. 서버로부터 현재 시간 수신한 후 종료
//4. 화면에 모든 송수신 문자열을 출력할 것




int main(void) {
	WSADATA wsa;


	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		//소켓 라이브러리가 로딩이 됐는지 안 됐는지 확인
		//0아닌 값이 넘어오면 로딩이 안 된 것
		printf("Error in starting up Winsock\n");
		return -1;
	}

	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);

	if (s == INVALID_SOCKET) {
		printf("Error in socket(), Error code: %d\n", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	SOCKADDR_IN serverAddress;
	ZeroMemory(&serverAddress, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(50000);
	inet_pton(AF_INET, "192.168.154.1", &(serverAddress.sin_addr.s_addr));
	connect(s, (SOCKADDR*)&serverAddress, sizeof(serverAddress));

	char chRxBuf[MAX_BUF] = { 0 };
	recv(s, chRxBuf, MAX_BUF, 0);

	const char chTxBuf[MAX_BUF] = "Hello, TCP Time Server!";
	send(s, chTxBuf, strlen(chTxBuf), 0);

	//int iLength = sendto(s, chTxBuf, strlen(chTxBuf), 0, (SOCKADDR*)&serverAddress, sizeof(serverAddress));

	/*if (iLength == SOCKET_ERROR) {
		printf("Error in send(), Error code: %d\n", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return -1;
	}//sendto 함수에서 에러가 난 경우
	printf("Message send to the server:%s\n", chTxBuf);

	int rlen = sizeof(serverAddress);
//	int rLength = recvfrom(s, chRxBuf, MAX_BUF, 0, (SOCKADDR*)&serverAddress, &rlen);

	if (rLength == SOCKET_ERROR) {
		printf("Error in recvfrom(), Error code: %d\n", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return -1;
	}//recvfrom() 함수에서 에러가 난 경우*/

	printf("Message receive from the server: %s  \n", chRxBuf);

	closesocket(s);
	WSACleanup();
	return 0;


}