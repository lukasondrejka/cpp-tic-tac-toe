#include <iostream>

#include "game/server.h"
#include "game/client.h"

const int PORT = 10010;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "Invalid number of arguments\n";
        return 1;
    }

    if (argv[1][0] == 's' || argv[1][0] == 'S') {
        Server server(PORT, Board::Symbol::X);
        server.run();
    } else if (argv[1][0] == 'c' || argv[1][0] == 'C') {
        Client client(PORT, Board::Symbol::O);
        client.run();
    } else {
        cout << "Invalid argument\n";
        return 1;
    }

    return 0;
}
