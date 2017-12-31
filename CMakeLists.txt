cmake_minimum_required(VERSION 3.8)
project(advancedProgramming1)

#set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS -pthread)

add_subdirectory(lib/googletest-release-1.8.0)

include_directories(src lib/googletest-release-1.8.0/googletest/include)
include_directories(lib/googletest-release-1.8.0/googlemock/include)

set(SOURCE_FILES src/client/Board.h src/client/StandartGameLogic.cpp src/client/StandartGameLogic.h
        src/client/GameLogic.h src/client/Game.cpp src/client/Game.h src/client/Player.h
        src/client/Enum.h src/client/Point.cpp src/client/Point.h src/client/HumanPlayer.cpp
        src/client/HumanPlayer.h src/client/AIPlayer.cpp src/client/AIPlayer.h src/client/Board.cpp
        src/client/ConsolePrinter.cpp src/client/ConsolePrinter.h src/client/Printer.h
        src/client/Game.cpp src/client/Game.h src/client/ServerPlayer.cpp src/client/ServerPlayer.h)

set(TEST_FILES src/client/Tests/ClientTests.cpp src/client/Tests/ServerTests.cpp)

set(SERVER_FILES src/server/MakeMoveCommand.cpp src/server/MakeMoveCommand.h
        src/server/Command.h src/server/StartCommand.cpp
        src/server/StartCommand.h src/server/CommandsManager.cpp src/server/CommandsManager.h
        src/server/Game.cpp src/server/Game.h src/server/Server.cpp src/server/Server.h src/server/CloseGameCommand.cpp src/server/CloseGameCommand.h src/server/JoinGameCommand.cpp src/server/JoinGameCommand.h src/server/GetGameListCommand.cpp src/server/GetGameListCommand.h src/server/Handler.cpp src/server/Handler.h)

add_executable(game ${SOURCE_FILES} src/client/main.cpp)
add_executable(server ${SERVER_FILES} src/server/main.cpp)
add_executable(tests ${SOURCE_FILES} ${TEST_FILES} src/client/Tests/gtest_main.cpp)

target_link_libraries(tests gtest gtest_main gmock)
