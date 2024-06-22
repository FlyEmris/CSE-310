#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"

class Board {
    public:
        Board();
        bool movePiece(int startX, int startY, int endX, int endY);

    private:
    Piece* board[8][8];
    Piece* getPieceAt(int x, int y) const;
};

#endif