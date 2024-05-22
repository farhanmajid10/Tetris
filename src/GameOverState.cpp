#include "GameOverState.hpp"
#include "GameStateManager.hpp"
#include <string> // Ensure this is included

GameOverState::GameOverState(GameStateManager& gameStateManager, Renderer& renderer, int finalScore)
    : GameState(gameStateManager), renderer(renderer), finalScore(finalScore) {}

void GameOverState::handleEvent(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_RETURN:
                gameStateManager.changeState(GameStateManager::START_MENU_STATE);
                break;
            // Handle other events if necessary
        }
    }
}

void GameOverState::update() {
    // Update game over state if necessary
}

void GameOverState::render(Renderer& renderer) {
    SDL_SetRenderDrawColor(renderer.getSDLRenderer(), 0, 0, 0, 255); // Set render color to black
    SDL_RenderClear(renderer.getSDLRenderer());

    int windowWidth = 800;
    int windowHeight = 600;

    SDL_Color white = {255, 255, 255, 255};
    SDL_Rect rect;

    // Render "Game Over!"
    SDL_Texture* textTexture = renderer.createTextTexture("Game Over!", white, rect, 48);
    SDL_Rect dstRect = {windowWidth / 2 - rect.w / 2, windowHeight / 4 - rect.h / 2, rect.w, rect.h};
    SDL_RenderCopy(renderer.getSDLRenderer(), textTexture, nullptr, &dstRect);
    SDL_DestroyTexture(textTexture);

    // Render "Total Score: <score>"
    std::string scoreText = "Total Score: " + std::to_string(finalScore);
    textTexture = renderer.createTextTexture(scoreText.c_str(), white, rect, 24);
    dstRect = {windowWidth / 2 - rect.w / 2, windowHeight / 2 - rect.h / 2, rect.w, rect.h};
    SDL_RenderCopy(renderer.getSDLRenderer(), textTexture, nullptr, &dstRect);
    SDL_DestroyTexture(textTexture);

    SDL_RenderPresent(renderer.getSDLRenderer());
}
