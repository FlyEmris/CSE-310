#ifndef KING_H
#define KING_H  

#include "Piece.h"

class King : public Piece {
    public:
        King(Color color) : Piece(color) {}
        bool isValidMove(int startX, int startY, int endX, int endY) const;
};

#endif