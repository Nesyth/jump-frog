#include "Background.h"
#include "Game.h"
#include "SDL_image.h"

#include <iostream>

SDL_Texture* bgTexture;

void Background::init(SDL_Renderer* renderer) {
    loadImage(renderer);
}

SDL_Texture* Background::loadImage(SDL_Renderer* renderer) {
    bgTexture = IMG_LoadTexture(renderer, BG_IMG_PATH);

    return bgTexture;
}

void Background::draw(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, 512, 1024 };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(renderer, bgTexture, clip, &renderQuad, angle, center, flip);
}