#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "Renderer.hpp"

class GameStateManager;

class GameState {
public:
    GameState(GameStateManager& gameStateManager);
    virtual ~GameState() = default;

    virtual void handleEvent(SDL_Event& event) = 0;
    virtual void update() = 0;
    virtual void render(Renderer& renderer) = 0;

protected:
    GameStateManager& gameStateManager;
};

inline GameState::GameState(GameStateManager& gameStateManager)
    : gameStateManager(gameStateManager) {}

#endif // GAME_STATE_HPP
