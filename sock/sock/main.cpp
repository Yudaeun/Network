#include <WinSock2.h>
#include <stdio.h>
#include <WS2tcpip.h>

int main() {
	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) { //WSAStartup=WindowsSocketAPI
		//���϶��̺귯���� �ε��� �ƴ��� �� �ƴ��� Ȯ��
		//0�ƴ� ���� �Ѿ���� �ε��� �� �� ���̴�.
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

//������Ʈ->�Ӽ�->��Ŀ->�Է�->�߰����Ӽ�->ws2_32.lib �߰�