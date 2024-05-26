#ifndef GAME_OVER_STATE_HPP
#define GAME_OVER_STATE_HPP

#include "GameState.hpp"
#include "Renderer.hpp"
#include "Game.hpp"
#include "HighScores.hpp"

class GameOverState : public GameState {
public:
    GameOverState(GameStateManager& gameStateManager, Renderer& renderer, int finalScore, Game &game);
    void handleEvent(SDL_Event& event) override;
    void update() override;
    void render(Renderer& renderer) override;

private:
    Renderer& renderer;
    int finalScore;
    Game &game;
};

#endif // GAME_OVER_STATE_HPP
