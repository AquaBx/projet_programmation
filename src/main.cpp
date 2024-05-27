#include <SDL2/SDL.h>
#include "config.h"
#include "game/game.h"

int main(int argc, char* argv[])
{
    game game(Config::screenWidth, Config::screenHeight);
    game.run();
    return 0;
}

int WinMain(int argc, char* argv[])
{
    return main(argc, argv);
}