cmake_minimum_required(VERSION 3.8)
project(ex3)

#set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread")

add_subdirectory(lib/googletest-release-1.8.0)

include_directories(src lib/googletest-release-1.8.0/googletest/include)
include_directories(lib/googletest-release-1.8.0/googlemock/include)

set(SOURCE_FILES src/Board.h src/StandartGameLogic.cpp src/StandartGameLogic.h src/GameLogic.h
        src/Game.cpp src/Game.h src/Player.h src/Enum.h src/Point.cpp src/Point.h src/HumanPlayer.cpp
        src/HumanPlayer.h src/AIPlayer.cpp src/AIPlayer.h src/Board.cpp)

set(TEST_FILES Tests/Tests.cpp Tests/BoardTest.h Tests/AIPlayerTest.h Tests/StandartGameLogicTest.h src/Board.cpp)

add_executable(game ${SOURCE_FILES} src/main.cpp)
add_executable(tests ${SOURCE_FILES} ${TEST_FILES} Tests/gtest_main.cpp)

target_link_libraries(tests gtest gtest_main gmock)
