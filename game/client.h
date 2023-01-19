#ifndef CLIENT_H
#define CLIENT_H

#include "../tcp_communication/tcp_client.h"
#include "./game.h"

class Client : public TCPClient, public Game {
public:
    Client(int port, Board::Symbol player) : Game(player), TCPClient(port, "127.0.0.1") {}

    ~Client() {}

    void run() override {
        TCPClient::start();
        playGame();
    }

    void sendMove(const Board::Move move) override {
        Client::sendMessage(to_string(move.row) + to_string(move.col));
    }

    Board::Move receiveMove() override {
        string message = Client::receiveMessage();
        return {message[0] - '0', message[1] - '0'};
    }
};

#endif //CLIENT_H
