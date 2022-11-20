#pragma once

using namespace std;

class Piece {
    char type;

public:
    Piece(char);
    char GetPieceType() const;
    bool operator==(const Piece&) const;
    bool operator!=(const Piece&) const;
};