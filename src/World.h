#ifndef WORLD_H
#define WORLD_H

#include "SDL.h"

#include <vector>

#define TILE_WIDTH 160
#define TILE_HEIGHT 20

#define TILE_IMG_PATH "assets/tile.png"
#define FLOOR_TILE_IMG_PATH "assets/floortile.png"
#define FINISH_TILE_IMG_PATH "assets/finishtile.png"

class World {
    public:
        World();
        // ~World();
        // void render();
        void init(SDL_Renderer* renderer);
        SDL_Texture* loadImage(SDL_Renderer* renderer);
        void update (int scrollUpdate);
        void draw(SDL_Renderer* renderer);
        std::vector<SDL_Rect> getObs();
};

#endif