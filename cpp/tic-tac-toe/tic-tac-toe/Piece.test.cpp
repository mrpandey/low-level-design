#include "Piece.h"
#include <gtest/gtest.h>

TEST(PieceTests, GetPieceType){
    char ch = 'X';
    Piece piece(ch);
    EXPECT_EQ(ch, piece.GetPieceType());
}