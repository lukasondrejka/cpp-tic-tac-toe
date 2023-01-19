#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>

using namespace std;

class Board {
public:
    static const int SIZE = 3;

    enum class Symbol : char {
        NONE = ' ',
        X = 'X',
        O = 'O'
    };

    struct Move {
        int row;
        int col;
    };

    using GameBoard = Symbol[SIZE][SIZE];

private:
    GameBoard board;
    string horizontalLine;

public:
    Board() {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                board[i][j] = Symbol::NONE;
            }
        }

        horizontalLine = string(4 * SIZE + 1, '-');
    }

    void displayBoard() const {
        string s;

        s += "\n" + horizontalLine + "\n";

        for (int i = 0; i < SIZE; ++i) {
            s += "| ";
            for (int j = 0; j < SIZE; ++j) {
                s += string(1, static_cast<char>(board[i][j]));
                s += " | ";
            }
            s += "\n";
        }

        s += horizontalLine + "\n\n";

        cout << s;
    }

    bool makeMove(Move move, Symbol player) {
        move.row--;
        move.col--;

        if (move.row < 0 || move.row >= SIZE || move.col < 0 || move.col >= SIZE) {
            return false;
        }

        if (board[move.row][move.col] == Symbol::X || board[move.row][move.col] == Symbol::O) {
            return false;
        }

        board[move.row][move.col] = player;

        displayBoard();

        return true;
    }

    Move promptMove(Symbol player) {
        Move move = {0, 0};

        if (isBoardFull())
            return move;

        string input;
        while (true) {
            cout << "Player " << static_cast<char>(player) << ", enter your move (row and col): ";
            cin >> input;
            move = {input[0] - '0', input[1] - '0'};

            if (makeMove(move, player)) {
                break;
            }

            cout << "Invalid move, try again\n";
        }

        return move;
    }

    bool endGame() {
        if (isWin(Symbol::X)) {
            cout << "Player X wins!\n";
            return true;
        }

        if (isWin(Symbol::O)) {
            cout << "Player O wins!\n";
            return true;
        }

        if (isBoardFull()) {
            cout << "It's a draw!\n";
            return true;
        }

        return false;
    }

private:
    bool isBoardFull() const {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (board[i][j] == Symbol::NONE) {
                    return false;
                }
            }
        }
        return true;
    }

    bool isWin(Symbol player) const {
        for (int i = 0; i < SIZE; ++i) {
            bool rowWin = true;
            bool colWin = true;
            bool diagWin1 = true;
            bool diagWin2 = true;

            for (int j = 0; j < SIZE; ++j) {
                if (board[i][j] != player) {
                    rowWin = false;
                }

                if (board[j][i] != player) {
                    colWin = false;
                }

                if (board[j][j] != player) {
                    diagWin1 = false;
                }

                if (board[j][SIZE - j - 1] != player) {
                    diagWin2 = false;
                }
            }

            if (rowWin || colWin || diagWin1 || diagWin2) {
                return true;
            }
        }

        return false;
    }
};

#endif //BOARD_H
