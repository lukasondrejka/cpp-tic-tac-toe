# Tic Tac Toe

This is a simple Tic Tac Toe game implemented in C++ 
with using client-server architecture and sockets for communication.

## Setup

Linux is required to build and run the project (tested on Ubuntu).

1. Build the project with `make`

```bash
make
```

2. Run the server

```bash
./app s
```

3. Run the client (in another terminal)

```bash
./app c
```

4. Play the game

Inputs are in the format of `rowcol` where `row` and `col` are integers between 1 and 3.
For example, to place a mark in first row and third column, you should enter `13`.
After each move, the board will be printed to the console.
Game ends when one of the players wins or the board is full.
