#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "Player.h"

#include <string>
#include <vector>

#define IMG_PATH "assets/character.png"
#define BG_IMG_PATH "assets/background.png"
#define TILE_IMG_PATH "assets/tile.png"
#define FTILE_IMG_PATH "assets/floortile.png"
#define WIDTH 800
#define HEIGHT 600
#define MAP_WIDTH 800
#define MAP_HEIGHT 1200

#define PLATFORM_HEIGHT 40
#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 38

class Game {
    public:
        static SDL_Renderer* renderer;
        SDL_Texture* playerTexture;
        Game();
        ~Game();
        void init();
        void render();
        void update();
        void clean();
        void handleEvents();
        bool running();
        void checkIntersect(SDL_Rect a, std::vector<SDL_Rect> b);
        void fixCollision(SDL_Rect a, SDL_Rect b, SDL_Rect collisionHeight);
        float getDeltaTime();
    private:
        Game* game;
        SDL_Window* window;
        bool isRunning;
};

#endif