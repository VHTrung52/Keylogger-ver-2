// Server.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <WinSock2.h>
#include <thread>
#pragma warning(disable:4996)
#pragma comment(lib, "Ws2_32.lib")

void Server();
void CreateSever(SOCKET server);
void serverRecvMess(SOCKET a);

int main()
{
	Server();
}


void Server() {
	WSADATA WSAData;

	SOCKET server,client;

	SOCKADDR_IN clientAddr;

	WSAStartup(MAKEWORD(2, 0), &WSAData);

	server = socket(AF_INET, SOCK_STREAM, 0);

	CreateSever(server);

	int clientAddrSize = sizeof(clientAddr);

	client = accept(server, (SOCKADDR *)&clientAddr, &clientAddrSize);
	serverRecvMess(client);

}

void CreateSever(SOCKET server) {
	SOCKADDR_IN serverAddr;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(5555);
	bind(server, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
	listen(server, 3);

	std::cout << "Listening for incoming connections..." << std::endl;
}

void serverRecvMess(SOCKET a) {
	char buffer[100];
	while (true) {
		memset(buffer, 0, sizeof(buffer));
		if (recv(a, buffer, sizeof(buffer), 0) != -1) {
			std::cout << buffer;
		}
		else {
			closesocket(a);
			strcat(buffer, "a client has disconected");
			std::cout << buffer << std::endl;
			break;
		}

	}
}