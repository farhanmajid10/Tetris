#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include "GameStateManager.hpp"

class Game {
public:
    Game();
    ~Game();
    void run();
    bool getIsRunning() const;

private:
    bool isRunning;
    SDL_Window* window;
    SDL_Renderer* sdlRenderer;
    Renderer renderer;
    GameStateManager gameStateManager;
};

#endif // GAME_HPP
