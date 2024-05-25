#ifndef PAUSED_STATE_HPP
#define PAUSED_STATE_HPP

#include "GameState.hpp"
#include "Renderer.hpp"

class PausedState : public GameState {
public:
    PausedState(GameStateManager& gameStateManager, Renderer& renderer, int currentScore);
    void handleEvent(SDL_Event& event) override;
    void update() override;
    void render(Renderer& renderer) override;

private:
    Renderer& renderer;
    int pscore;
};

#endif // PAUSED_STATE_HPP
