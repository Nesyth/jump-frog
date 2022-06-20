#include "SDL.h"
#include "SDL_image.h"
#include "Game.h"

#include <iostream>
#include <vector>
#include <string>

#define TICK_INTERVAL 1

static Uint32 next_time;

Uint32 time_left(void)
{
    Uint32 now;

    now = SDL_GetTicks();
    if (next_time <= now)
        return 0;
    else
        return next_time - now;
}

int main() {
	Game* game = new Game;

    next_time = SDL_GetTicks() + TICK_INTERVAL;

	game->init();
    while (game->running()) {
		game->handleEvents();
		game->update();
		game->render();

		SDL_Delay(time_left());
        next_time += TICK_INTERVAL;
    }
	game->clean();
	delete game;

    return 0;
}