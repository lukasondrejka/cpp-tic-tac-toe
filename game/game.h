#ifndef GAME_H
#define GAME_H

#include "board.h"

class Game;
class Server;
class Client;

class Game {
protected:
    Board gameBoard;
    Board::Symbol player;

protected:
    Game(Board::Symbol player) : player(player) {}

    virtual void run() = 0;

    void playGame() {
        Board::Move move;
        Board::Symbol currentPlayer = Board::Symbol::O;

        gameBoard.displayBoard();

        while (true) {
            if (currentPlayer == player) {
                move = gameBoard.promptMove(currentPlayer);
                sendMove(move);
            } else {
                cout << "Waiting for opponent's move...\n";
                move = receiveMove();
                gameBoard.makeMove(move, currentPlayer);
            }

            if (gameBoard.endGame()) {
                break;
            }

            currentPlayer = (currentPlayer == Board::Symbol::X) ? Board::Symbol::O : Board::Symbol::X;
        }
    }

    virtual void sendMove(const Board::Move move) = 0;
    virtual Board::Move receiveMove() = 0;
};

#endif //GAME_H
