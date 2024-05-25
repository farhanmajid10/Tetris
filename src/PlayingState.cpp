#include "PlayingState.hpp"
#include "GameStateManager.hpp"
#include <iostream>
#include <string>

PlayingState::PlayingState(GameStateManager& gameStateManager, Renderer& renderer)
    : GameState(gameStateManager), renderer(renderer), board(), currentPiece(), nextPiece(), isGameOver(false), pieceX(Board::WIDTH / 2 - 2), pieceY(0), lastMoveTime(SDL_GetTicks()), score(0) {
    spawnPiece();
    std::cout << "PlayingState initialized\n";
}

void PlayingState::handleEvent(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_LEFT:
                movePiece(-1, 0);
                break;
            case SDLK_RIGHT:
                movePiece(1, 0);
                break;
            case SDLK_DOWN:
                movePiece(0, 1);
                break;
            case SDLK_UP:
                rotatePiece();
                break;
            case SDLK_SPACE:
                hardDropPiece();
                break;
            case SDLK_ESCAPE: // Ensure this case is correct
                gameStateManager.pushState(GameStateManager::PAUSED_STATE, score);
                break;
        }
    }
}

int PlayingState::getScore() const{
    return score;
}

void PlayingState::update() {
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastMoveTime > 500) { // Move piece down every 500 ms
        std::cout << "Moving piece down\n";
        if (!movePiece(0, 1)) { // If the piece can't move down, place it
            std::cout << "Placing piece at (" << pieceX << ", " << pieceY << ")\n";
            board.placePiece(currentPiece, pieceX, pieceY);
            int linesCleared = board.clearLines();
            score += linesCleared * 40;
            if (!isGameOver) {
                spawnPiece();
            }
        }
        lastMoveTime = currentTime;
    }
}

void PlayingState::render(Renderer& renderer) {
    std::cout << "Rendering PlayingState\n";
    SDL_SetRenderDrawColor(renderer.getSDLRenderer(), 0, 0, 0, 255);
    SDL_RenderClear(renderer.getSDLRenderer());

    int windowWidth = 800;
    int windowHeight = 600;
    int boardWidth = Board::WIDTH * 20;
    int boardHeight = Board::HEIGHT * 20;
    int offsetX = (windowWidth - boardWidth) / 2;
    int offsetY = (windowHeight - boardHeight) / 2;

    // Draw the board outline
    SDL_SetRenderDrawColor(renderer.getSDLRenderer(), 255, 255, 255, 255); 
    SDL_Rect boardOutline = {offsetX, offsetY, boardWidth, boardHeight};
    SDL_RenderDrawRect(renderer.getSDLRenderer(), &boardOutline);

    // Draw the board
    board.draw(renderer, offsetX, offsetY);  // Draw the board at some offset
    renderer.drawPiece(currentPiece, pieceX * 20 + offsetX, pieceY * 20 + offsetY);  // Draw the current piece

    // Draw the score
    SDL_Color white = {255, 255, 255, 255};
    SDL_Rect rect;
    std::string scoreText = "Score: " + std::to_string(score);
    SDL_Texture* textTexture = renderer.createTextTexture(scoreText.c_str(), white, rect, 24);
    SDL_Rect dstRect = {windowWidth - rect.w - 20, 20, rect.w, rect.h};
    SDL_RenderCopy(renderer.getSDLRenderer(), textTexture, nullptr, &dstRect);
    SDL_DestroyTexture(textTexture);

    SDL_RenderPresent(renderer.getSDLRenderer());
}

void PlayingState::checkGameOver() {
    if (board.isGameOver()) {
        isGameOver = true;
        std::cout << "Game Over\n";
        gameStateManager.changeState(GameStateManager::GAME_OVER_STATE, score);
    }
}


bool PlayingState::movePiece(int dx, int dy) {
    if (!board.isCollision(currentPiece, pieceX + dx, pieceY + dy)) {
        pieceX += dx;
        pieceY += dy;
        return true;
    }
    return false;
}

void PlayingState::rotatePiece() {
    Piece rotatedPiece = currentPiece;
    rotatedPiece.rotate();
    if (!board.isCollision(rotatedPiece, pieceX, pieceY)) {
        currentPiece = rotatedPiece;
    }
}

void PlayingState::spawnPiece() {
    currentPiece = nextPiece;
    nextPiece = Piece();
    pieceX = Board::WIDTH / 2 - 2;
    pieceY = 0;
    std::cout << "Spawning new piece\n";
    if (board.isCollision(currentPiece, pieceX, pieceY)) {
        isGameOver = true;
        std::cout << "Game Over: Collision detected on spawn\n";
        gameStateManager.changeState(GameStateManager::GAME_OVER_STATE, score); // Placeholder score
    }
}

void PlayingState::hardDropPiece() {
    while (!board.isCollision(currentPiece, pieceX, pieceY + 1)) {
        pieceY++;
    }
    board.placePiece(currentPiece, pieceX, pieceY);
    board.clearLines();
    if (!isGameOver) {
        spawnPiece();
    }
}
