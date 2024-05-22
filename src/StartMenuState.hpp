#ifndef START_MENU_STATE_HPP
#define START_MENU_STATE_HPP

#include "GameState.hpp"
#include "Renderer.hpp"
#include<iostream>

class StartMenuState : public GameState {
public:
    StartMenuState(GameStateManager& gameStateManager, Renderer& renderer);
    void handleEvent(SDL_Event& event) override;
    void update() override;
    void render(Renderer& renderer) override;

private:
    Renderer& renderer;
};

#endif // START_MENU_STATE_HPP
