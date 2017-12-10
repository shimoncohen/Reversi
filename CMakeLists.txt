cmake_minimum_required(VERSION 3.8)
project(advancedProgramming1)

#set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread")

add_subdirectory(lib/googletest-release-1.8.0)

include_directories(src lib/googletest-release-1.8.0/googletest/include)
include_directories(lib/googletest-release-1.8.0/googlemock/include)

set(SOURCE_FILES src/client/Board.h src/client/StandartGameLogic.cpp src/client/StandartGameLogic.h
        src/client/GameLogic.h src/client/Game.cpp src/client/Game.h src/client/Player.h
        src/client/Enum.h src/client/Point.cpp src/client/Point.h src/client/HumanPlayer.cpp
        src/client/HumanPlayer.h src/client/AIPlayer.cpp src/client/AIPlayer.h src/client/Board.cpp
        src/client/ConsolePrinter.cpp src/client/ConsolePrinter.h src/client/Printer.h
        src/client/Game.cpp src/client/Game.h src/client/ServerPlayer.cpp src/client/ServerPlayer.h
        src/server/Server.h src/server/Server.cpp)

set(TEST_FILES Tests/ClientTests.cpp src/client/Board.cpp Tests/ServerTests.cpp)

add_executable(game ${SOURCE_FILES} src/client/main.cpp)
add_executable(server ${SOURCE_FILES} src/server/main.cpp)
add_executable(tests ${SOURCE_FILES} ${TEST_FILES} Tests/gtest_main.cpp)

target_link_libraries(tests gtest gtest_main gmock)
