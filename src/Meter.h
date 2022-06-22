#ifndef METER_H
#define METER_H

#include "SDL.h"
#include "SDL_ttf.h"

class Meter {
    public:
        void isWinner(bool areYouWinningSon);
        void getPos(int hPos);
        void draw(SDL_Renderer *renderer, TTF_Font *font);
};

#endif