#ifndef PIECES_HPP
#define PIECES_HPP

#include <SDL2/SDL.h>

class Piece {
public:
    using ShapeArray = int[4][4];

    Piece();
    const ShapeArray& getShape() const;
    int getWidth() const;
    int getHeight() const;
    SDL_Color getColor() const;  // Add this method

    void rotate();
    void setShape(const ShapeArray& newshape);
    void setColor(SDL_Color newColor);

private:
    ShapeArray shape;
    SDL_Color color;  // Ensure this member exists
    int x, y;
};

#endif // PIECES_HPP
