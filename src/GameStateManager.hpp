#ifndef GAME_STATE_MANAGER_HPP
#define GAME_STATE_MANAGER_HPP

#include <memory>
#include <stack>
#include "GameState.hpp"
#include "Renderer.hpp"
#include "Game.hpp"

class Game;
class GameStateManager {
public:
    enum State {
        START_MENU_STATE,
        MAIN_GAME_STATE,
        PAUSED_STATE,
        GAME_OVER_STATE
    };

    GameStateManager(Renderer& renderer, Game &game);

    void changeState(State newState, int finalScore = 0);
    void pushState(State newState, int currentScore = 0);
    void popState();

    void handleEvent(SDL_Event& event);
    void update();
    void render();

    Renderer* getRenderer();
    //void endgame();

private:
    std::unique_ptr<GameState> createState(State state, int finalScore = 0);

    std::stack<std::unique_ptr<GameState>> stateStack;
    GameState* currentState;
    Renderer& renderer;
    Game& game;
};

#endif // GAME_STATE_MANAGER_HPP
