#include "Board.hpp"
#include <iostream>

Board::Board() {
    clear();
}

void Board::clear() {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            grid[i][j] = {false, {0, 0, 0, 255}};  // Ensure all cells are unoccupied and black
        }
    }
}

bool Board::isCollision(const Piece& piece, int x, int y) const {
    const auto& shape = piece.getShape();
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (shape[i][j] != 0) {
                int boardX = x + j;
                int boardY = y + i;
                if (boardX < 0 || boardX >= WIDTH || boardY < 0 || boardY >= HEIGHT) {
                    return true;
                }
                if (boardY >= 0 && grid[boardY][boardX].occupied) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Board::placePiece(const Piece& piece, int x, int y) {
    const auto& shape = piece.getShape();
    SDL_Color color = piece.getColor(); // Get the color of the piece
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (shape[i][j] != 0) {
                int boardX = x + j;
                int boardY = y + i;
                if (boardX >= 0 && boardX < WIDTH && boardY >= 0 && boardY < HEIGHT) {
                    grid[boardY][boardX].occupied = true;
                    grid[boardY][boardX].color = color;
                }
            }
        }
    }
}

bool Board::isGameOver() const {
    for (int x = 0; x < WIDTH; ++x) {
        if (grid[0][x].occupied) {
            return true;
        }
    }
    return false;
}

int Board::clearLines() {
    int linesCleared = 0;
    for (int i = 0; i < HEIGHT; ++i) {
        bool fullLine = true;
        for (int j = 0; j < WIDTH; ++j) {
            if (!grid[i][j].occupied) {
                fullLine = false;
                break;
            }
        }
        if (fullLine) {
            for (int k = i; k > 0; --k) {
                for (int j = 0; j < WIDTH; ++j) {
                    grid[k][j] = grid[k-1][j];
                }
            }
            for (int j = 0; j < WIDTH; ++j) {
                grid[0][j] = {false, {0, 0, 0, 255}};
            }
            ++linesCleared;
        }
    }
    return linesCleared;
}

void Board::draw(Renderer& renderer, int offsetX, int offsetY) const {
    const int blockSize = 20; // Size of each block in pixels
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (grid[i][j].occupied) {
                SDL_Rect blockRect = {offsetX + j * blockSize, offsetY + i * blockSize, blockSize, blockSize};
                SDL_Color color = grid[i][j].color;
                SDL_SetRenderDrawColor(renderer.getSDLRenderer(), color.r, color.g, color.b, color.a);
                SDL_RenderFillRect(renderer.getSDLRenderer(), &blockRect);
            }
        }
    }

    SDL_SetRenderDrawColor(renderer.getSDLRenderer() , 255, 255, 255, 255);
    for(int i = 0; i < HEIGHT; i++){
        SDL_RenderDrawLine(renderer.getSDLRenderer(), offsetX, offsetY + (blockSize * i), offsetX + (WIDTH * blockSize), offsetY + (blockSize * i));
    }

    for(int i = 0; i < WIDTH; i++){
        SDL_RenderDrawLine(renderer.getSDLRenderer(), offsetX + (blockSize * i), offsetY, offsetX + (blockSize * i), offsetY + (HEIGHT*blockSize));
    }
}
