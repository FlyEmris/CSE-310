#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : public Piece {
    public:
        Knight(Color color) : Piece(color) {}
        bool isValidMove(int startX, int startY, int endX, int endY) const;
};

#endif