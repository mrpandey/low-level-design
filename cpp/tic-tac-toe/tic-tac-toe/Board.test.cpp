#include "Board.h"
#include <stdexcept>
#include <gtest/gtest.h>

TEST(BoardTests, SetGetCells){
    Piece pieceEmpty('-'), pieceX('X');
    Board board(2, pieceEmpty);
    board.SetCell(1, 1, pieceX);

    EXPECT_THROW(board.SetCell(1, 1, pieceX), logic_error);
    EXPECT_THROW(board.SetCell(1, 2, pieceEmpty), logic_error);
    EXPECT_EQ(pieceEmpty, board.GetCell(2,2));
    EXPECT_EQ(pieceX, board.GetCell(1,1));
    EXPECT_THROW(board.GetCell(2,3), out_of_range);
}

TEST(BoardTests, IsFull){
    Piece pieceEmpty('-'), pieceX('X');
    Board board(2, pieceEmpty);

    board.SetCell(2, 2, pieceX);
    EXPECT_FALSE(board.IsFull());

    board.SetCell(1, 1, pieceX);
    EXPECT_FALSE(board.IsFull());

    board.SetCell(1, 2, pieceX);
    EXPECT_FALSE(board.IsFull());

    board.SetCell(2, 1, pieceX);
    EXPECT_TRUE(board.IsFull());
}