#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include "tcp_communication.h"

class TCPServer : public TCPCommunication {
private:
    int serverSocket;

public:
    TCPServer(int port) : TCPCommunication(port), serverSocket(-1) {}

    ~TCPServer() {
        close(serverSocket);
        close(clientSocket);
    }

    virtual void start() {
        struct sockaddr_in serverAddress{}, clientAddress{};
        socklen_t clientAddressLength = sizeof(clientAddress);

        // Create socket
        serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket == -1) {
            perror("Error creating socket");
            exit(EXIT_FAILURE);
        }

        // Set up server address struct
        memset(&serverAddress, 0, sizeof(serverAddress));
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = INADDR_ANY;
        serverAddress.sin_port = htons(port);

        // Bind the socket
        if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
            perror("Error binding socket");
            exit(EXIT_FAILURE);
        }

        // Listen for connections
        if (listen(serverSocket, 1) == -1) {
            perror("Error listening for connections");
            exit(EXIT_FAILURE);
        }

        cout << "Server waiting for client connection...\n";

        // Accept a connection
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);
        if (clientSocket == -1) {
            perror("Error accepting connection");
            exit(EXIT_FAILURE);
        }

        cout << "Client connected\n";
    }
};

#endif //TCP_SERVER_H
