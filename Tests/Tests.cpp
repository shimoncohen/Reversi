/*shimon cohen*/
/*315383133*/

#include "gtest/gtest.h"
#include "Game.h"
#define SIZE 4

/*
 * Test the ConsoleBoard.
 */
TEST(ReversiTests, TestingConsoleBoard__Test) {
    /*
     * Testing ConsoleBoard.
     */
    Board *board = new Board(SIZE);
    EXPECT_EQ('o', board->checkCell(2,2));
    EXPECT_NE('x', board->checkCell(2,2));
    delete board;
}

/*
 * Test the GameLogic.
 */
TEST(ReversiTests, TestingGameLogic__Test) {
    /*
     * Testing GameLogics moves.
     */
    Board *board = new Board(SIZE);
    GameLogic *gameLogic = new StandartGameLogic();
    vector<Point> correctMoves;
    Point *move = new Point(1, 2);
    correctMoves.push_back(*move);
    move = new Point(2, 1);
    correctMoves.push_back(*move);
    move = new Point(3, 4);
    correctMoves.push_back(*move);
    move = new Point(4, 3);
    correctMoves.push_back(*move);
    // check if available moves result is correct.
    vector<Point> availableMoves = gameLogic->availableMoves(*board, blackPlayer);
    int i = 0, k = 0, count = 0;
    bool equal;
    for(i = 0; i < availableMoves.size(); i++) {
        for (k = 0; k < availableMoves.size(); k++) {
            if (availableMoves[i] == correctMoves[k]) {
                count++;
            }
        }
    }
    count == correctMoves.size() ? equal = true : equal = false;
    EXPECT_TRUE(equal);

    // check if logic changes tiles correctly.
    Board *board1 = new ConsoleBoard(SIZE);
    // insert wanted board tile values.
    board1->putTile(0, 0, 'o');
    board1->putTile(0, 1, 'o');
    board1->putTile(0, 2, 'o');
    board1->putTile(1, 0, 'x');
    board1->putTile(1, 1, 'x');
    board1->putTile(1, 2, 'o');
    board1->putTile(2, 1, 'x');
    board1->putTile(2, 2, 'o');
    // play moves that bring to wanted board.
    board->putTile(1, 0, 'x');
    board->putTile(0, 0, 'o');
    board->putTile(0, 1, 'x');
    board->putTile(0, 2, 'o');
    gameLogic->changeTiles(blackPlayer, 1, 0, *board);
    gameLogic->changeTiles(whitePlayer, 0, 0, *board);
    gameLogic->changeTiles(blackPlayer, 0, 1, *board);
    gameLogic->changeTiles(whitePlayer, 0, 2, *board);
    // check if wanted board and played board are equal.
    EXPECT_TRUE(*board == *board1);
    delete board;
    delete board1;
    delete move;
    delete gameLogic;
}

/*
 * Test the AIPlayer.
 */
TEST(ReversiTests, TestingAIPlayer__Test) {
    /*
     * testing AIPlayer.
     */
    // check if AIPlayer chooses correct option in a given situation.
    Board *board = new Board(SIZE);
    GameLogic *gameLogic = new StandartGameLogic();
    vector<Point> correctMoves;
    vector<Point> availableMoves;
    Player *player = new AIPlayer(blackPlayer);
    bool equal;
    board->putTile(1, 0, 'x');
    board->putTile(0, 0, 'o');
    board->putTile(0, 1, 'x');
    board->putTile(0, 2, 'o');
    gameLogic->changeTiles(blackPlayer, 1, 0, *board);
    gameLogic->changeTiles(whitePlayer, 0, 0, *board);
    gameLogic->changeTiles(blackPlayer, 0, 1, *board);
    gameLogic->changeTiles(whitePlayer, 0, 2, *board);
    gameLogic->changeTiles(blackPlayer, 1, 3, *board);
    availableMoves = gameLogic->availableMoves(*board, whitePlayer);
    int *aiMove = player->makeMove(*gameLogic, *board, availableMoves);
    aiMove[0] == 3 && aiMove[1] == 1 ? equal = true : equal = false;
    EXPECT_TRUE(equal);
    delete aiMove;
    delete player;
    delete board;
    delete gameLogic;
}