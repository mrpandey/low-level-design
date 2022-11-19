#include "Piece.h"

Piece::Piece(char type): type(type) {}

char Piece::GetPieceType() const{
    return type;
}

bool Piece::operator==(const Piece& piece){
    if(type == piece.GetPieceType()) return true;
    return false;
}

bool Piece::operator!=(const Piece &piece){
    if(type != piece.GetPieceType()) return true;
    return false;
}