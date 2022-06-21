#include "SDL.h"
#include "SDL_image.h"
#include "World.h"
#include "Game.h"

#include <vector>
#include <iostream>

std::vector<SDL_Rect> obs;
SDL_Texture* tileTexture;
SDL_Texture* fTileTexture;

World::World() {
    SDL_Rect rect;

    rect.w = WIDTH; rect.h = 400; rect.x = 0; rect.y = HEIGHT - 40;
    obs.push_back(rect);

    // ------------------------------------------------ //

    rect.w = 160; rect.h = 20; rect.x = 500; rect.y = 110;
    obs.push_back(rect);

    rect.w = 160; rect.h = 20; rect.x = 100; rect.y = 110;
    obs.push_back(rect);

    rect.w = 160; rect.h = 20; rect.x = 200; rect.y = 140;
    obs.push_back(rect);

    rect.w = 160; rect.h = 20; rect.x = 300; rect.y = 240;
    obs.push_back(rect);

    rect.w = 160; rect.h = 20; rect.x = 450; rect.y = 340;
    obs.push_back(rect);

    rect.w = 160; rect.h = 20; rect.x = 500; rect.y = 440;
    obs.push_back(rect);
}

std::vector<SDL_Rect> World::getObs() {
    return obs;
}

void World::init(SDL_Renderer* renderer) {
    loadImage(renderer);
}

SDL_Texture* World::loadImage(SDL_Renderer* renderer) {
    tileTexture = IMG_LoadTexture(renderer, TILE_IMG_PATH);
    fTileTexture = IMG_LoadTexture(renderer, FTILE_IMG_PATH);

    return tileTexture;
}

int World::update (int scrollUpdate) {
    for (int i = 0; i < obs.size(); i++) {
        SDL_Rect newObstacle = { obs[i].x, obs[i].y + scrollUpdate, obs[i].w, obs[i].h };
        obs[i] = newObstacle;

        // if (i == 0) std::cout << "obs[i].y: " << obs[i].y << " obs[i].scroll: " << scrollUpdate << std::endl;
    }
}

void World::draw(SDL_Renderer* renderer) {
    for (int i = 0; i < obs.size(); i++) {
        if (i != 0) {
            SDL_Rect targetRect = { obs[i].x - 15, obs[i].y - 10, obs[i].w + 30, obs[i].h + 20 };
            SDL_RenderCopy(renderer, tileTexture, NULL, &targetRect);
        } else {
            SDL_Rect targetRect = { obs[i].x, obs[i].y - 15, obs[i].w, obs[i].h + 30 };
            SDL_RenderCopy(renderer, fTileTexture, NULL, &targetRect);
        }
    }
}