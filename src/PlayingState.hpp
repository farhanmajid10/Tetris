#ifndef PLAYING_STATE_HPP
#define PLAYING_STATE_HPP

#include "GameState.hpp"
#include "Renderer.hpp"
#include "Board.hpp"
#include "Pieces.hpp"

class PlayingState : public GameState {
public:
    PlayingState(GameStateManager& gameStateManager, Renderer& renderer);
    void handleEvent(SDL_Event& event) override;
    void update() override;
    void render(Renderer& renderer) override;
    int getScore() const;

private:
    Renderer& renderer;
    Board board;
    Piece currentPiece;
    Piece nextPiece;
    bool isGameOver;
    int pieceX, pieceY;
    Uint32 lastMoveTime;
    int score;

    void checkGameOver();
    bool movePiece(int dx, int dy);
    void dropPiece();
    void rotatePiece();
    void spawnPiece();
    void hardDropPiece();
};

#endif // PLAYING_STATE_HPP
