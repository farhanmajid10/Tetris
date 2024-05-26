#include "GameOverState.hpp"
#include "GameStateManager.hpp"
#include <string>

GameOverState::GameOverState(GameStateManager& gameStateManager, Renderer& renderer, int finalScore, Game &game)
    : GameState(gameStateManager), renderer(renderer), finalScore(finalScore), game(game) {
    game.getHighScores().update(finalScore);
}

void GameOverState::handleEvent(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_RETURN:
                gameStateManager.changeState(GameStateManager::START_MENU_STATE);
                break;
            case SDLK_ESCAPE:
                game.quitgame();
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

    // Game Over
    SDL_Texture* gameOverTextTexture = renderer.createTextTexture("Game Over!", white, rect, 48);
    SDL_Rect gameOverDstRect = {windowWidth / 2 - rect.w / 2, windowHeight / 4 - rect.h, rect.w, rect.h}; // Move "Game Over" higher
    SDL_RenderCopy(renderer.getSDLRenderer(), gameOverTextTexture, nullptr, &gameOverDstRect);
    SDL_DestroyTexture(gameOverTextTexture);

    // Total Score
    std::string scoreText = "Total Score: " + std::to_string(finalScore);
    SDL_Texture* scoreTextTexture = renderer.createTextTexture(scoreText.c_str(), white, rect, 24);
    SDL_Rect scoreDstRect = {windowWidth / 2 - rect.w / 2, windowHeight / 2 - rect.h / 2 - 120, rect.w, rect.h};
    SDL_RenderCopy(renderer.getSDLRenderer(), scoreTextTexture, nullptr, &scoreDstRect);
    SDL_DestroyTexture(scoreTextTexture);

    // High Scores Title
    SDL_Texture* highScoresTitleTexture = renderer.createTextTexture("High Scores:", white, rect, 24);
    SDL_Rect highScoresTitleDstRect = {windowWidth / 2 - rect.w / 2, scoreDstRect.y + rect.h + 30, rect.w, rect.h};
    SDL_RenderCopy(renderer.getSDLRenderer(), highScoresTitleTexture, nullptr, &highScoresTitleDstRect);
    SDL_DestroyTexture(highScoresTitleTexture);

    // Render High Scores with proper alignment
    auto highScores = game.getHighScores().getHighScores();
    int yOffset = highScoresTitleDstRect.y + rect.h + 30;
    int serialNumberXOffset = windowWidth / 2 - 100;
    int scoreXOffset = windowWidth / 2 - 50;
    for (int i = 0; i < highScores.size(); ++i) {
        std::string serialDisplay = std::to_string(i + 1) + ".";
        SDL_Texture* serialTextTexture = renderer.createTextTexture(serialDisplay.c_str(), white, rect, 24);
        SDL_Rect serialDstRect = {serialNumberXOffset, yOffset, rect.w, rect.h};
        SDL_RenderCopy(renderer.getSDLRenderer(), serialTextTexture, nullptr, &serialDstRect);
        SDL_DestroyTexture(serialTextTexture);

        std::string scoreDisplay = std::to_string(highScores[i]);
        if (highScores[i] == finalScore) {
            scoreDisplay += " *"; // Add star if it's the current score
        }
        SDL_Texture* highScoreTextTexture = renderer.createTextTexture(scoreDisplay.c_str(), white, rect, 24);
        SDL_Rect highScoreDstRect = {scoreXOffset, yOffset, rect.w, rect.h};
        SDL_RenderCopy(renderer.getSDLRenderer(), highScoreTextTexture, nullptr, &highScoreDstRect);
        SDL_DestroyTexture(highScoreTextTexture);
        
        yOffset += 30;
    }

    // Press Enter to Return to Start Menu
    SDL_Texture* startMenuTextTexture = renderer.createTextTexture("Press Enter to Return to Start Menu.", white, rect, 24);
    SDL_Rect startMenuDstRect = {windowWidth / 2 - rect.w / 2, yOffset + 30, rect.w, rect.h};
    SDL_RenderCopy(renderer.getSDLRenderer(), startMenuTextTexture, nullptr, &startMenuDstRect);
    SDL_DestroyTexture(startMenuTextTexture);
    
    // Press Esc to Quit Game
    SDL_Texture* quitTextTexture = renderer.createTextTexture("Press Esc to Quit Game.", white, rect, 24);
    SDL_Rect quitDstRect = {windowWidth / 2 - rect.w / 2, yOffset + 60, rect.w, rect.h};
    SDL_RenderCopy(renderer.getSDLRenderer(), quitTextTexture, nullptr, &quitDstRect);
    SDL_DestroyTexture(quitTextTexture);

    SDL_RenderPresent(renderer.getSDLRenderer());
}
