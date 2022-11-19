#pragma once

using namespace std;

class Piece {
    char type;

public:
    Piece(char);
    char GetPieceType() const;
    bool operator==(const Piece&);
    bool operator!=(const Piece&);
};