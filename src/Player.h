#ifndef PLAYER_H
#define PLAYER_H

#include "SDL.h"
#include "Game.h"
#include "World.h"

#include <string>

#define IMG_PATH "assets/character.png"

class Player {
    public:
        Player();
        ~Player();
        void init(SDL_Renderer* renderer);
        SDL_Rect getRect();
        static SDL_Texture* loadImage(SDL_Renderer* renderer);
        void draw(SDL_Renderer* renderer);
        void handleEvents(SDL_Event &event);
        bool jumping();
        void move(std::string collision, int collisionHeight);
        // void move(SDL_bool collision);
        int getScrollY();
        void destroyImage();
};

#endif