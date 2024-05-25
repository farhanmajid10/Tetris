#include "PausedState.hpp"
#include "GameStateManager.hpp"
#include <iostream>
#include <string>

PausedState::PausedState(GameStateManager& gameStateManager, Renderer& renderer, int currentScore)
    : GameState(gameStateManager), renderer(renderer), pscore(currentScore) {}

void PausedState::handleEvent(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_LEFT:
                gameStateManager.popState(); // Resume the game
                break;
            case SDLK_RIGHT:
                gameStateManager.changeState(GameStateManager::MAIN_GAME_STATE); // Restart the game
                break;
            case SDLK_UP:
                gameStateManager.changeState(GameStateManager::GAME_OVER_STATE, pscore); // Quit to GameOver menu
                break;
        }
    }
}

void PausedState::update() {
    
}

void PausedState::render(Renderer& renderer) {
    SDL_SetRenderDrawColor(renderer.getSDLRenderer(), 0, 0, 0, 255); // render color: black
    SDL_RenderClear(renderer.getSDLRenderer());

    int windowWidth = 800;
    int windowHeight = 600;

    SDL_Color white = {255, 255, 255, 255};
    SDL_Rect rect;

    //Paused
    SDL_Texture* textTexture = renderer.createTextTexture("Paused", white, rect, 48);
    SDL_Rect dstRect = {windowWidth / 2 - rect.w / 2, windowHeight / 4 - rect.h / 2, rect.w, rect.h};
    SDL_RenderCopy(renderer.getSDLRenderer(), textTexture, nullptr, &dstRect);
    SDL_DestroyTexture(textTexture);
 
    //Press LEFT to Resume
    textTexture = renderer.createTextTexture("Press LEFT to Resume", white, rect, 24);
    dstRect = {windowWidth / 2 - rect.w / 2, windowHeight / 2 - rect.h / 2, rect.w, rect.h};
    SDL_RenderCopy(renderer.getSDLRenderer(), textTexture, nullptr, &dstRect);
    SDL_DestroyTexture(textTexture);

    // Press RIGHT to Restart
    textTexture = renderer.createTextTexture("Press RIGHT to Restart", white, rect, 24);
    dstRect = {windowWidth / 2 - rect.w / 2, windowHeight / 2 - rect.h / 2 + 40, rect.w, rect.h};
    SDL_RenderCopy(renderer.getSDLRenderer(), textTexture, nullptr, &dstRect);
    SDL_DestroyTexture(textTexture);

    //Press UP to Quit
    textTexture = renderer.createTextTexture("Press UP to Quit", white, rect, 24);
    dstRect = {windowWidth / 2 - rect.w / 2, windowHeight / 2 - rect.h / 2 + 80, rect.w, rect.h};
    SDL_RenderCopy(renderer.getSDLRenderer(), textTexture, nullptr, &dstRect);
    SDL_DestroyTexture(textTexture);

    SDL_RenderPresent(renderer.getSDLRenderer());
}
