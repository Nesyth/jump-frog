#include "Game.h"
#include "Player.h"
#include "World.h"
#include "Background.h"
#include "Meter.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>

SDL_Renderer* Game::renderer;
SDL_Texture* playerTexture;
TTF_Font* font;
Player* player = nullptr;
World* world = nullptr;
Background* background = nullptr;
Meter* meter = nullptr;

std::string collision;
int collisionHeight;
SDL_Rect collisionRect;
int updateScroll = 0;
std::string highestScore;
bool finished = 0;

std::fstream scoreFile("assets/score.txt");
std::string content((std::istreambuf_iterator<char>(scoreFile) ), (std::istreambuf_iterator<char>()));

SDL_Rect camera = { 0, 0, WIDTH, HEIGHT};

Game::Game() {
    window = NULL;
    renderer = NULL;
    playerTexture = NULL;
}

Game::~Game() {}

void Game::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "SDL innited!\n";
        window = SDL_CreateWindow("Jump-Frog", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
        if (window) {
            std::cout << "Window created!\n";
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (renderer) {
                std::cout << "Renderer created!\n";
                int flags = IMG_INIT_PNG;
                int initted = IMG_Init(flags);
                if (TTF_Init() == -1) {
                    printf("TTF_Init: %s\n", TTF_GetError());
                } else {
                    font = TTF_OpenFont("/Library/Fonts/Fascinate-Regular.ttf", 24);
                    if (font == NULL) {
                        fprintf(stderr, "error: font not found\n");
                        exit(EXIT_FAILURE);
                    }
                    if ((initted&flags) != flags) {
                        std::cout << "IMG_Init: Failed to init required jpg and png support!\n";
                        printf("IMG_Init: %s\n", IMG_GetError());
                        isRunning = false;
                    } else {
                        std::cout << "Window loaded!\n";
                        isRunning = true;

                        Player* player = new Player();
                        World* world = new World();
                        background->init(renderer);
                        player->init(renderer);
                        world->init(renderer);

                        // playerTexture = player->loadImage(renderer); 
                    }
                }
            } else {
                std::cout << "Couldn't create a renderer\n";
                isRunning = false;
            }
        } else {
            std::cout << "Couldn't create a window\n";
            isRunning = false;
        }
	} else {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        isRunning = false;
    }
}

void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
			
			case SDL_KEYDOWN:
				// std::cout << ("Key press detected\n");
				break;

			case SDL_KEYUP:
				// std::cout << ("Key release detected\n");
				break;
        }

    player->handleEvents(event);
}

void Game::checkIntersect(SDL_Rect a, std::vector<SDL_Rect> b) {
    SDL_bool hasIntersection = SDL_FALSE;

    for (SDL_Rect rects : b) {
        if (SDL_HasIntersection(&a, &rects)) {
            SDL_IntersectRect(&a, &rects, &collisionRect);
            fixCollision(a, rects, collisionRect);
        }
    }
}

void Game::fixCollision(SDL_Rect a, SDL_Rect b, SDL_Rect collisionRect) {
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    int smallest = 100;
    std::string result = "false";

    if (abs(bottomA - topB) < smallest) {
        smallest = abs(bottomA - topB);
        result = "collisionOnTop";
    }

    if (abs(topA - bottomB) < smallest) {
        smallest = abs(topA - bottomB);
        result = "collisionHead";
    }

    if (abs(rightA - leftB) < smallest) {
        smallest = abs(topA - bottomB);
        result = "collisionLeftHand";
    }

    if (abs(leftA - rightB) < smallest) {
        smallest = abs(topA - bottomB);
        result = "collisionRightHand";
    }

    collision = result;
    collisionHeight = collisionRect.h;
}

void Game::update() {
    SDL_Rect playerRect = player->getRect();

    collision = "false";
    checkIntersect(playerRect, world->getObs());
    player->move(collision, collisionHeight);
    world->update(player->getRect().y);
    meter->getPos(player->getRect().y);

    if (player->checkIfFinished(collision)) { 
        if (!finished) {
            finished = true;
            int endTime = SDL_GetTicks();

            if (endTime < std::stoi(content)) {
                std::remove("assets/score.txt");

                std::ofstream outfile ("assets/score.txt");
                outfile << std::to_string(endTime);
                std::cout << std::setprecision(2);
                std::cout << std::fixed << "New highest score: " << endTime/1000 << "s" << std::endl;
                outfile.close();
            }
        }
        meter->isWinner(1);
    }

    // camera.x = (playerRect.x + playerRect.w / 2) - WIDTH / 2;
    // camera.y = (playerRect.y + playerRect.h / 2) - HEIGHT / 2;

    // if (camera.x < 0) { 
    //     camera.x = 0;
    // }

    // if (camera.y < 0 ) {
    //     camera.y = 0;
    // }

    // if (camera.x > WIDTH - camera.w) {
    //     camera.x = WIDTH - camera.w;
    // }

    // if (camera.y > HEIGHT - camera.h) {
    //     camera.y = HEIGHT - camera.h;
    // }
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 75, 155, 200);
    SDL_RenderClear(renderer);

    // std::cout << "camera.x: " << camera.x << "camera.y: " << camera.y << std::endl;

    background->draw(renderer, 0, 0, &camera);
    player->draw(renderer, camera.x, camera.y);
    world->draw(renderer);
    meter->draw(renderer, font);

    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    // SDL_DestroyTexture(playerTexture);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

bool Game::running() {
    return isRunning;
}