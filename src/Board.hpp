#ifndef BOARD_HPP
#define BOARD_HPP

#include <SDL2/SDL.h>
#include "Renderer.hpp"
#include "Pieces.hpp"

class Board {
public:
    static const int WIDTH = 10;
    static const int HEIGHT = 20;

    struct Cell {
        bool occupied;
        SDL_Color color;  
    };

    Board();
    void clear();
    bool isCollision(const Piece& piece, int x, int y) const;
    void placePiece(const Piece& piece, int x, int y);
    int clearLines();
    void draw(Renderer& renderer, int offsetX, int offsetY) const;

    bool isGameOver() const;

private:
    Cell grid[HEIGHT][WIDTH];
};

#endif 
