#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Pieces.hpp"

class Renderer {
public:
    Renderer(SDL_Renderer* sdlRenderer);
    SDL_Renderer* getSDLRenderer() const;
    SDL_Texture* createTextTexture(const char* text, SDL_Color color, SDL_Rect& rect, int fontSize) const;
    void drawPiece(const Piece& piece, int x, int y) const;

private:
    SDL_Renderer* sdlRenderer;
};

#endif // RENDERER_HPP
