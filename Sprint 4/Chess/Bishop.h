#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

class Bishop : public Piece {
    public:
        Bishop(Color color) : Piece(color) {}
        bool isValidMove(int startX, int startY, int endX, int endY) const;
};

#endif