#ifndef TCP_COMMUNICATION_H
#define TCP_COMMUNICATION_H

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

class TCPCommunication {
protected:
    static const int BUFFER_SIZE = 256;
    int port;
    int clientSocket;

protected:
    TCPCommunication(int port) : port(port), clientSocket(-1) {}

    virtual ~TCPCommunication()
    {
        close(clientSocket);
    }

    virtual void start() = 0;

    virtual void run() = 0;

    void sendMessage(string message) const
    {
        if (message.size() >= BUFFER_SIZE) {
            cerr << "Message too long" << endl;
            exit(EXIT_FAILURE);
        }
        ssize_t bytesSent = send(clientSocket, message.c_str(), message.size(), 0);
        if (bytesSent == -1) {
            perror("Error sending message");
            exit(EXIT_FAILURE);
        }
    }

    string receiveMessage() const
    {
        char buffer[BUFFER_SIZE];
        ssize_t bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
        if (bytesReceived == -1) {
            perror("Error receiving message");
            exit(EXIT_FAILURE);
        }
        return string(buffer, bytesReceived);
    }
};

#endif //TCP_COMMUNICATION_H
