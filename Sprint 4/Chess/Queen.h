#ifndef QUEEEN_H
#define QUEEEN_H

#include "Piece.h"

class Queen : public Piece {
    public:
        Queen(Color color) : Piece(color) {}
        bool isValidMove(int startX, int startY, int endX, int endY) const;
};

#endif