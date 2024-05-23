#include <SDL2/SDL.h>
#include "src/Game.hpp"

int SDL_main(int argc, char* argv[]) {
    Game game;
    if (game.getIsRunning()) {
        game.run();
    }
    return 0;
}

//free range
