#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include "tcp_communication.h"

class TCPClient : public TCPCommunication {
private:
    string ipAddress;

public:
    TCPClient(int port, string ipAddress) : TCPCommunication(port), ipAddress(ipAddress) {}

    ~TCPClient() {
        close(clientSocket);
    }

    void start() {
        struct sockaddr_in serverAddress{};

        // Create socket
        clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (clientSocket == -1) {
            perror("Error creating socket");
            exit(EXIT_FAILURE);
        }

        // Set up server address struct
        memset(&serverAddress, 0, sizeof(serverAddress));
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = inet_addr(ipAddress.c_str());
        serverAddress.sin_port = htons(port);

        // Connect to the server
        if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
            perror("Error connecting to server");
            exit(EXIT_FAILURE);
        }

        cout << "Connected to the server\n";
    }
};

#endif //TCP_CLIENT_H
