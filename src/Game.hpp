#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include "GameStateManager.hpp"
#include "HighScores.hpp"

class GameStateManager;
class Renderer;

class Game {
public:
    Game();
    ~Game();
    void run();
    bool getIsRunning() const;
    void quitgame();
    HighScores& getHighScores();  // Add this method

private:
    bool isRunning;
    SDL_Window* window;
    SDL_Renderer* sdlRenderer;
    Renderer* renderer;
    GameStateManager* gameStateManager;
    HighScores highScores;  // Make sure this is initialized and used
};

#endif // GAME_HPP
