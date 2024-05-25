#include "Game.hpp"
#include "GameStateManager.hpp"
#include "Renderer.hpp" 
#include <iostream>

Game::Game() : isRunning(true), window(nullptr), sdlRenderer(nullptr), renderer(nullptr), gameStateManager(nullptr) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        isRunning = false;
        return;
    }

    if (TTF_Init() == -1) {
        std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
        isRunning = false;
        SDL_Quit();
        return;
    }

    window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        isRunning = false;
        TTF_Quit();
        SDL_Quit();
        return;
    }

    sdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!sdlRenderer) {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        isRunning = false;
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return;
    }

    SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255); // Set background color to black
    renderer = new Renderer(sdlRenderer);
    gameStateManager = new GameStateManager(*renderer, *this);
    gameStateManager->changeState(GameStateManager::START_MENU_STATE);
}

void Game::quitgame(){
    Game::isRunning = false;
}

Game::~Game() {
    delete gameStateManager;
    delete renderer;
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

void Game::run() {
    SDL_Event event;
    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            } else {
                gameStateManager->handleEvent(event);
            }
        }
        gameStateManager->update();
        SDL_RenderClear(sdlRenderer);
        gameStateManager->render();
        SDL_RenderPresent(sdlRenderer);
    }
}

bool Game::getIsRunning() const {
    return isRunning;
}
