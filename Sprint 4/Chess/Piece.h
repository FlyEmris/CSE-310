#ifndef PIECE_H
#define PIECE_H

class Piece {
    public:
        enum Color {WHITE, BLACK};
        Piece(Color color) : color(color) {}
        virtual ~Piece() {}

        virtual bool isValidMove(int startX, int startY, int endX, int endY) const = 0;
        Color getColor() const { return color; }

    protected :
        Color color;
};

#endif