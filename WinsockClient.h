#pragma once
#include <string>
#include <winsock2.h>
class WinsockClient {
private:
	WSADATA wsaData;
	SOCKET clientSocket;
	sockaddr_in serverAddr;
public:
	WinsockClient(); // Constructor
	~WinsockClient();
	void connectToServer(const std::string& serverIP, int port);
	void sendMessage(const std::string& message);
	void disconnect();
};