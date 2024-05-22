#include "Renderer.hpp"
#include <iostream>

Renderer::Renderer(SDL_Renderer* sdlRenderer) : sdlRenderer(sdlRenderer) {}

SDL_Renderer* Renderer::getSDLRenderer() const {
    return sdlRenderer;
}

SDL_Texture* Renderer::createTextTexture(const char* text, SDL_Color color, SDL_Rect& rect, int fontSize) const {
    TTF_Font* font = TTF_OpenFont("rubik_font/Rubik-Regular.ttf", fontSize);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return nullptr;
    }

    SDL_Surface* surface = TTF_RenderText_Blended(font, text, color);
    if (!surface) {
        std::cerr << "Failed to create surface for text: " << TTF_GetError() << std::endl;
        TTF_CloseFont(font);
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(sdlRenderer, surface);
    rect.w = surface->w;
    rect.h = surface->h;
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    return texture;
}

void Renderer::drawPiece(const Piece& piece, int x, int y) const {
    const int blockSize = 20; // Size of each block in pixels
    SDL_Rect blockRect = {0, 0, blockSize, blockSize};

    const auto& shape = piece.getShape();
    SDL_Color color = piece.getColor();
    SDL_SetRenderDrawColor(sdlRenderer, color.r, color.g, color.b, color.a);

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (shape[i][j] != 0) {
                blockRect.x = x + j * blockSize;
                blockRect.y = y + i * blockSize;
                SDL_RenderFillRect(sdlRenderer, &blockRect);
            }
        }
    }
}
