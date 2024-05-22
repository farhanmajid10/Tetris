#include "Pieces.hpp"
#include <algorithm>
#include <cstdlib>

const Piece::ShapeArray I_SHAPE = {
    {0, 0, 0, 0},
    {1, 1, 1, 1},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};

const Piece::ShapeArray O_SHAPE = {
    {0, 1, 1, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};

const Piece::ShapeArray T_SHAPE = {
    {0, 1, 0, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};

const Piece::ShapeArray S_SHAPE = {
    {0, 1, 1, 0},
    {1, 1, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};

const Piece::ShapeArray Z_SHAPE = {
    {1, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};

const Piece::ShapeArray J_SHAPE = {
    {1, 0, 0, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};

const Piece::ShapeArray L_SHAPE = {
    {0, 0, 1, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};

Piece::Piece() {
    int shapeType = std::rand() % 7;
    switch(shapeType){
        case 0: setShape(I_SHAPE);
                setColor({0, 255, 255, 255}); // Cyan
                break;
        case 1: setShape(O_SHAPE);
                setColor({255, 255, 0, 255}); // Yellow
                break;
        case 2: setShape(T_SHAPE);
                setColor({128, 0, 128, 255}); // Purple
                break;
        case 3: setShape(S_SHAPE);
                setColor({0, 255, 0, 255}); // Green
                break;
        case 4: setShape(Z_SHAPE);
                setColor({255, 0, 0, 255}); // Red
                break;
        case 5: setShape(J_SHAPE);
                setColor({0, 0, 255, 255}); // Blue
                break;
        case 6: setShape(L_SHAPE);
                setColor({255, 165, 0, 255}); // Orange
                break;
    }
    x = 0;
    y = 0;
}

void Piece::setShape(const Piece::ShapeArray& newshape) {
    std::copy(&newshape[0][0], &newshape[0][0] + 4*4, &shape[0][0]);
}

void Piece::setColor(SDL_Color newColor) {
    color = newColor;
}

SDL_Color Piece::getColor() const {  // Add this method
    return color;
}

void Piece::rotate() {
    int temp[4][4];
    std::copy(&shape[0][0], &shape[0][0] + 4*4, &temp[0][0]);
    for(int i = 0; i < 4; i++ ){
        for(int j = 0; j < 4; j++){
            shape[j][3-i] = temp[i][j];
        }
    }
}

const Piece::ShapeArray& Piece::getShape() const {
    return shape;
}

int Piece::getWidth() const {
    int maxWidth = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (shape[i][j] != 0) {
                maxWidth = std::max(maxWidth, j + 1);
            }
        }
    }
    return maxWidth;
}

int Piece::getHeight() const {
    int maxHeight = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (shape[i][j] != 0) {
                maxHeight = std::max(maxHeight, i + 1);
            }
        }
    }
    return maxHeight;
}
