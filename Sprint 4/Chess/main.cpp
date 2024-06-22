#include "Board.h"

int main() {
    Board chessBoard;

    // Main game loop
    while (true) {
        // Get player input
        int startX, startY, endX, endY;
        // e.g., read input

        // Attempt to move piece
        if (chessBoard.movePiece(startX, startY, endX, endY)) {
            // Move was successful
        } else {
            // Move was invalid
        }

        // Check for game over conditions
    }

    return 0;
}
