#include "WinsockClient.h"
#include <stdexcept>
#include <iostream>
#include <ws2tcpip.h> // Add this include for inet_pton
#pragma comment(lib, "ws2_32.lib")

// this class handles the Winsock client operations.

WinsockClient::WinsockClient() : clientSocket(INVALID_SOCKET), serverAddr{} { // Initialize Winsock
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) { // Check for startup errors
		throw std::runtime_error("WSAStartup failed");
	}
}

WinsockClient::~WinsockClient() { // Cleanup process. This helps to avoid memory leaks.
	disconnect();
	WSACleanup();
}

void WinsockClient::connectToServer(const std::string& serverIP, int port) { // Connecting to the server
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == INVALID_SOCKET) { // Check for socket creation errors
		int errorCode = WSAGetLastError();
		std::cerr << "Socket creation failed. Error code: " << errorCode << std::endl;
		throw std::runtime_error("Socket creation failed");
	}
	serverAddr.sin_family = AF_INET; // Set server address
	serverAddr.sin_port = htons(port); // Set server port
	if (inet_pton(AF_INET, serverIP.c_str(), &serverAddr.sin_addr) <= 0) { // Convert IPv4 and IPv6 addresses from text to binary form
		closesocket(clientSocket);
		throw std::runtime_error("Invalid address/ Address not supported");
	}
	if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) { // condition to check if the connection is successful
		int errorCode = WSAGetLastError();
		std::cerr << "Connection to server failed. Error code: " << errorCode << std::endl; closesocket(clientSocket);
		throw std::runtime_error("Connection to server failed");
	}
}

void WinsockClient::sendMessage(const std::string& message) { // method to send message to the server
	if (clientSocket == INVALID_SOCKET) {
		std::cerr << "Invalid socket. Cannot send message." << std::endl;
		throw std::runtime_error("Invalid socket");
	}

	// Send message to the server
	int result = send(clientSocket, message.c_str(), static_cast<int>(message.length()), 0);
	if (result == SOCKET_ERROR) {
		int errorCode = WSAGetLastError();
		std::cerr << "Failed to send message. Error code: " << errorCode << std::endl;
		throw std::runtime_error("Failed to send message");
	}
	std::cout << "Message sent to server: " << message << std::endl;

	// Receive response from server
	char buffer[1024] = { 0 };  // Buffer for server response
	int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
	if (bytesReceived > 0) {
		std::cout << "Server Response: " << std::string(buffer, bytesReceived) << std::endl;
	}
	else {
		std::cerr << "No response from server." << std::endl;
	}
}


void WinsockClient::disconnect() {
	if (clientSocket != INVALID_SOCKET) {
		closesocket(clientSocket);
		clientSocket = INVALID_SOCKET;
	}
}