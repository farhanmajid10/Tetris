#include "GameStateManager.hpp"
#include "StartMenuState.hpp"
#include "PlayingState.hpp"
#include "PausedState.hpp"
#include "GameOverState.hpp"
#include "Game.hpp"

GameStateManager::GameStateManager(Renderer& renderer, Game &game) : currentState(nullptr), renderer(renderer), game(game) {}

void GameStateManager::changeState(State newState, int finalScore) {
    if (!stateStack.empty()) {
        stateStack.pop();
    }
    auto newStatePtr = createState(newState, finalScore);
    currentState = newStatePtr.get();
    stateStack.push(std::move(newStatePtr));
}

void GameStateManager::pushState(State newState, int currentScore) {
    auto newStatePtr = createState(newState, currentScore);
    currentState = newStatePtr.get();
    stateStack.push(std::move(newStatePtr));
}


//void GameStateManager::endgame(){
//    Game::isRunning = false;
//}

void GameStateManager::popState() {
    if (!stateStack.empty()) {
        stateStack.pop();
        if (!stateStack.empty()) {
            currentState = stateStack.top().get();
        } else {
            currentState = nullptr;
        }
    }
}

void GameStateManager::handleEvent(SDL_Event& event) {
    if (currentState) {
        currentState->handleEvent(event);
    }
}

void GameStateManager::update() {
    if (currentState) {
        currentState->update();
    }
}

void GameStateManager::render() {
    if (currentState) {
        currentState->render(renderer);
    }
}

Renderer* GameStateManager::getRenderer() {
    return &renderer;
}

std::unique_ptr<GameState> GameStateManager::createState(State state, int finalScore) {
    switch (state) {
        case START_MENU_STATE:
            return std::make_unique<StartMenuState>(*this, renderer);
        case MAIN_GAME_STATE:
            return std::make_unique<PlayingState>(*this, renderer);
        case PAUSED_STATE:
            return std::make_unique<PausedState>(*this, renderer, finalScore);
        case GAME_OVER_STATE:
            return std::make_unique<GameOverState>(*this, renderer, finalScore, game);
        default:
            return nullptr;
    }
}
