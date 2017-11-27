

#include "gtest/gtest.h"
#include "BoardTest.h"
#include "AIPlayerTest.h"
#include "StandartGameLogicTest.h"

TEST(TestMe, miniTest) {
    /*
     * Testing ConsoleBoard.
     */
    Board *board = new ConsoleBoard(4);
    EXPECT_EQ('o', board->checkCell(2,2));
    EXPECT_NE('x', board->checkCell(2,2));
    Board *board1 = new ConsoleBoard(4);
    board1->putTile(0, 0, 'o');
    board1->putTile(1, 0, 'x');
    board1->putTile(1, 1, 'o');
    board1->putTile(1, 2, 'o');
    board1->putTile(1, 3, 'o');
    board1->putTile(2, 1, 'x');
    board1->putTile(2, 2, 'x');
    board1->putTile(2, 3, 'x');

    /*
     * Testing GameLogics moves.
     */
    GameLogic *gameLogic = new StandartGameLogic();
    vector<Point> *correctMoves = new vector<Point>();
    Point *move = new Point(1, 2);
    correctMoves->push_back(*move);
    move = new Point(2, 1);
    correctMoves->push_back(*move);
    move = new Point(3, 4);
    correctMoves->push_back(*move);
    move = new Point(4, 3);
    correctMoves->push_back(*move);
    vector<Point> availableMoves = gameLogic->availableMoves(*board, blackPlayer);
    board->putTile(1, 0, 'x');
    board->putTile(0, 0, 'o');
    board->putTile(1, 3, 'o');
    board->putTile(2, 3, 'x');
    gameLogic->changeTiles(blackPlayer, 1, 0, *board);
    gameLogic->changeTiles(whitePlayer, 0, 0, *board);
    gameLogic->changeTiles(blackPlayer, 2, 3, *board);
    gameLogic->changeTiles(whitePlayer, 1, 3, *board);
    EXPECT_TRUE(*board == *board1);

    /*
     * testing AIPlayer.
     */


//    Player *player = new AIPlayer(blackPlayer);
//    Player *player2 = new AIPlayer(whitePlayer);



    delete board;
    delete board1;
    delete gameLogic;
}