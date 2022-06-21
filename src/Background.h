#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "SDL.h"

#include <vector>

class Background {
    public:
        void init(SDL_Renderer* renderer);
        SDL_Texture* loadImage(SDL_Renderer* renderer);
        void draw(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
};

#endif