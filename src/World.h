#ifndef WORLD_H
#define WORLD_H

#include "SDL.h"

#include <vector>

class World {
    public:
        World();
        // ~World();
        // void render();
        void draw(SDL_Renderer* renderer);
        std::vector<SDL_Rect> getObs();
};

#endif