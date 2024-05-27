#include <SDL2/SDL.h>
#include "config.h"
#include "game/game.h"

int main(int argc, char* argv[]) {
    game(config::window::width, config::window::height).run();
    return 0;
}

int WinMain(int argc, char* argv[]) {
    return main(argc, argv);
}