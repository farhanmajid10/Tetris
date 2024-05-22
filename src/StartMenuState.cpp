#include "StartMenuState.hpp"
#include "GameStateManager.hpp"

StartMenuState::StartMenuState(GameStateManager& gameStateManager, Renderer& renderer)
    : GameState(gameStateManager), renderer(renderer) {}

void StartMenuState::handleEvent(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_RETURN:
                std::cout << "Enter pressed, transitioning to MAIN_GAME_STATE" << std::endl;
                gameStateManager.changeState(GameStateManager::MAIN_GAME_STATE, 0);
                break;
            // Handle other events
        }
    }
}

void StartMenuState::update() {
    // Update code here
}

void StartMenuState::render(Renderer& renderer) {
    int windowWidth = 800;
    int windowHeight = 600;

    SDL_Color white = {255, 255, 255, 255};
    SDL_Rect rect;

    // Render "Tetris"
    SDL_Texture* textTexture = renderer.createTextTexture("Tetris", white, rect, 48);
    SDL_Rect dstRect = {windowWidth / 2 - rect.w / 2, windowHeight / 4 - rect.h / 2, rect.w, rect.h};
    SDL_RenderCopy(renderer.getSDLRenderer(), textTexture, nullptr, &dstRect);
    SDL_DestroyTexture(textTexture);

    // Render "Use Arrow Keys to Move"
    textTexture = renderer.createTextTexture("Use Arrow Keys to Move", white, rect, 24);
    dstRect = {windowWidth / 2 - rect.w / 2, windowHeight / 2 - rect.h / 2, rect.w, rect.h};
    SDL_RenderCopy(renderer.getSDLRenderer(), textTexture, nullptr, &dstRect);
    SDL_DestroyTexture(textTexture);

    // Render "Up to Rotate"
    textTexture = renderer.createTextTexture("Up to Rotate", white, rect, 24);
    dstRect = {windowWidth / 2 - rect.w / 2, windowHeight / 2 - rect.h / 2 + 40, rect.w, rect.h};
    SDL_RenderCopy(renderer.getSDLRenderer(), textTexture, nullptr, &dstRect);
    SDL_DestroyTexture(textTexture);

    // Render "Down to Speed Up"
    textTexture = renderer.createTextTexture("Down to Speed Up", white, rect, 24);
    dstRect = {windowWidth / 2 - rect.w / 2, windowHeight / 2 - rect.h / 2 + 80, rect.w, rect.h};
    SDL_RenderCopy(renderer.getSDLRenderer(), textTexture, nullptr, &dstRect);
    SDL_DestroyTexture(textTexture);

    // Render "Press Enter to Start"
    textTexture = renderer.createTextTexture("Press Enter to Start", white, rect, 24);
    dstRect = {windowWidth / 2 - rect.w / 2, windowHeight / 2 - rect.h / 2 + 120, rect.w, rect.h};
    SDL_RenderCopy(renderer.getSDLRenderer(), textTexture, nullptr, &dstRect);
    SDL_DestroyTexture(textTexture);
}
