#include "Board.h"

Board::Board() {
    // Initialize the board with pieces
    
}

bool Board::movePiece(int startX, int startY, int endX, int endY) {
    Piece* piece = getPieceAt(startX, startY);
    if (piece && piece->isValidMove(startX, startY, endX, endY)) {
        // Perform the move
        return true;
    }
    return false;
}

Piece* Board::getPieceAt(int x, int y) const {
    return board[x][y];
}
