#pragma once
#include<vector>
#include "Piece.h"

using namespace std;

class Board {
    int size;
    int empty_cell_count;
    vector<vector<Piece> > board;

public:
    Board();
    Board(int, Piece);
    void Print();
    void SetCell(int, int, const Piece&);
    Piece GetCell(int, int);
    bool IsFull();
    int GetSize();
};