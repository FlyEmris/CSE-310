#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Rook : public Piece {
    public:
        Rook(Color color) : Piece(color) {}
        bool isValidMove(int startX, int startY, int endX, int endY) const;
};

#endif