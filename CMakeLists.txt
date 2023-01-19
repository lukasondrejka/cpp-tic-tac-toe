cmake_minimum_required(VERSION 3.18)
project(app)

set(CMAKE_CXX_STANDARD 17)

set (SOURCE_FILES
        main.cpp
        tcp_communication/tcp_communication.h
        tcp_communication/tcp_server.h
        tcp_communication/tcp_client.h
        game/board.h
        game/game.h
        game/server.h
        game/client.h
)

add_executable(app ${SOURCE_FILES})
