#include <WinSock2.h>
#include <stdio.h>
#include <WS2tcpip.h>

int main() {
	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) { //WSAStartup=WindowsSocketAPI
		//소켓라이브러리가 로딩이 됐는지 안 됐는지 확인
		//0아닌 값이 넘어오면 로딩이 안 된 것이다.
		printf("Error in starting up Winsock\n");
		return -1;
	}
	

	SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);
	SOCKADDR_IN myAddress;
	ZeroMemory(&myAddress, sizeof(myAddress));
	myAddress.sin_family = AF_INET;
	myAddress.sin_port = 50000;
	inet_pton(AF_INET, "165.229.125.60", &(myAddress.sin_addr.s_addr));
	bind(s, (SOCKADDR*)&myAddress, sizeof(myAddress));
	closesocket(s);
	WSACleanup();
	return 0;
}

//프로젝트->속성->링커->입력->추가종속성->ws2_32.lib 추가