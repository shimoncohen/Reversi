cmake_minimum_required(VERSION 3.8)
project(ex3)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES main.cpp Board.h Board.cpp StandartGameLogic.cpp StandartGameLogic.h GameLogic.h Game.cpp Game.h Player.h Enum.h Point.cpp Point.h HumanPlayer.cpp HumanPlayer.h AIPlayer.cpp AIPlayer.h)
add_executable(ex1 ${SOURCE_FILES})