#include <iostream>
#include <algorithm>
#include <stdexcept>
#include "Board.h"

Board::Board(){}

Board::Board(int size, Piece piece = Piece('-')): size(size) {
    empty_cell_count = size*size;
    board = vector<vector<Piece>>(size, vector<Piece>(size, piece));
}

void Board::Print()
{
    for (int i = 0; i < size; i++)
    {
        cout << board[i][0].GetPieceType();
        for (int j = 1; j < size; j++)
        {
            cout << " " << board[i][j].GetPieceType();
        }
        cout << endl;
    }
}

void Board::SetCell(int x, int y, const Piece& piece){
    x--;
    y--;
    if(min(x,y)<0 || max(x,y)>=size || board[x][y].GetPieceType() != '-' || piece.GetPieceType() == '-'){
        throw logic_error("Invalid Move");
    }
    board[x][y] = piece;
    empty_cell_count--;
}

Piece Board::GetCell(int x, int y){
    x--;
    y--;
    if(min(x,y)<0 || max(x,y)>=size){
        throw out_of_range("Cell Coords Out Of Range");
    }
    return board[x][y];
}

bool Board::IsFull(){
    if(!empty_cell_count) return true;
    return false;
}

int Board::GetSize(){
    return size;
}