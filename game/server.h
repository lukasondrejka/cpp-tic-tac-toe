#ifndef SERVER_H
#define SERVER_H

#include "../tcp_communication/tcp_server.h"
#include "./game.h"

class Server : public TCPServer, public Game {
public:
    Server(int port, Board::Symbol player) : Game(player), TCPServer(port) {}

    void run() override {
        TCPServer::start();
        playGame();
    }

    void sendMove(const Board::Move move) override {
        Server::sendMessage(to_string(move.row) + to_string(move.col));
    }

    Board::Move receiveMove() override {
        string message = Server::receiveMessage();
        return {message[0] - '0', message[1] - '0'};
    }
};

#endif //SERVER_H
