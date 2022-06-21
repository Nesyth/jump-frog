#ifndef WORLD_H
#define WORLD_H

#include "SDL.h"

#include <vector>

class World {
    public:
        World();
        // ~World();
        // void render();
        void init(SDL_Renderer* renderer);
        SDL_Texture* loadImage(SDL_Renderer* renderer);
        int update (int scrollUpdate);
        void draw(SDL_Renderer* renderer);
        std::vector<SDL_Rect> getObs();
};

#endif