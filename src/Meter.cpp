#include "Meter.h"
#include "Game.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include <iostream>
#include <string>

SDL_Texture* fontTexture;
int playerHeight = 0;
bool win = 0;

void Meter::isWinner(bool areYouWinningSon) {
    win = areYouWinningSon;
}

void Meter::getPos(int hPos) {
    playerHeight = hPos - 523;
}

void Meter::draw(SDL_Renderer *renderer, TTF_Font *font) {
    std::string text = "HEIGHT: " + std::to_string(abs(playerHeight));
    SDL_Rect fontRect = { 10, HEIGHT - 50, 140, 50 };
    SDL_Color textColor = { 255, 255, 255, 140 };
    SDL_Surface *surface;

    if (win) {
        fontRect = { (WIDTH - 350) / 2, (HEIGHT - 120) / 2, 350, 120 };
        text = "WINNER!";
    }

    surface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    fontTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, fontTexture, NULL, &fontRect);
    SDL_FreeSurface(surface);
}