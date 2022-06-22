#include "SDL.h"
#include "SDL_image.h"
#include "Player.h"
#include "World.h"

#include <iostream>
#include <string>

SDL_Texture* texture;
SDL_Rect rect;
bool isJumping = false;
float up, down, right, left;
float velocity, gravity;
int lastAngle = 10;
bool jumpQueue = false;
double nowJump = 0, prepareJump = 0, deltaTimeJump = 0;
double previousDeltaTime = 0, currentDeltaTime = 0, deltaTime = 0;
bool flagLeft = false, flagRight = false;
std::string lastSide = "right";
bool hitHead = false;
bool hitOnce = false; //prevents head from going into a rect
bool innited = false;
int scrollY = 0, obstacleScrollY = 0;
int oldPosY = 0;

Player::Player() {
    rect.w = 50; 
    rect.h = 38;
    rect.x = (WIDTH - rect.w) / 2;
    rect.y = HEIGHT - rect.h - 40;

    velocity = 0;
    gravity = -300;
}

Player::~Player() {
    destroyImage();
}

SDL_Rect Player::getRect() {
    return rect;
}

void Player::setPos(int x, int y) {
    rect.x += x;
    rect.y += y;
}

void Player::init(SDL_Renderer* renderer) {
    loadImage(renderer);
}

SDL_Texture* Player::loadImage(SDL_Renderer* renderer) {
    texture = IMG_LoadTexture(renderer, IMG_PATH);

    return texture;
}

void Player::draw(SDL_Renderer* renderer, int x, int y) {
    SDL_Rect newRect = { rect.x - x, rect.y - y - 2, rect.w, rect.h };
    // std::cout << "newRect.x: " << newRect.x << "newRect.y: " << newRect.y << std::endl;
    // std::cout << "player.x: " << rect.x << "player.y: " << rect.y << std::endl;
    SDL_RenderCopyEx(renderer, texture, NULL, &newRect, lastAngle, NULL, SDL_FLIP_HORIZONTAL);
}

void Player::handleEvents(SDL_Event &event) {
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
		switch (event.key.keysym.sym) {
            case SDLK_UP: up = 1; break;
            case SDLK_DOWN: down = 1; break;
            case SDLK_RIGHT: right = 1; break;
            case SDLK_LEFT: left = 1; break;
		}
	}

    if (event.type == SDL_KEYUP && event.key.repeat == 0) {
		switch (event.key.keysym.sym) {
            case SDLK_UP: up = 0; break;
            case SDLK_DOWN: down = 0; break;
            case SDLK_RIGHT: right = 0; break;
            case SDLK_LEFT: left = 0; break;
		}
	}
}

void Player::move(std::string collision, int collisionHeight) {
    previousDeltaTime = currentDeltaTime;
    currentDeltaTime = SDL_GetTicks();
    deltaTime = ((currentDeltaTime - previousDeltaTime) * 0.001);

    if (collision == "false" && !isJumping) { // falling physics
        velocity = velocity + gravity * 0.016;
        rect.y = rect.y - velocity * 0.016;
        hitHead = false;

        if (innited) { // without does funny things when loading the game idk
            isJumping = true;
        }
    }

    if (collision == "collisionOnTop" && isJumping) {
        isJumping = false;

        velocity = 0;
    }

    if (collision == "collisionHead") {
        if (!hitOnce) {
            velocity = -velocity;
        }

        hitOnce = true;
        hitHead = true;
    }

    if (collision == "collisionLeftHand") {
        lastSide = "left";
    }

    if (collision == "collisionRightHand") {
        lastSide = "right";
    }

    if (!isJumping && !jumpQueue && up && collision != "false") { // loading jump
        prepareJump = SDL_GetTicks();
        jumpQueue = true;

        innited = true;
    }

    if (!up && jumpQueue && collision != "false") { // let go of "up" key, loaded jump
        nowJump = SDL_GetTicks();
        deltaTimeJump = (nowJump - prepareJump) * 0.001;

        if (deltaTimeJump < 0.1 && deltaTimeJump >= 0) {
            velocity = 30.0;
        } else if (deltaTimeJump < 0.2 && deltaTimeJump >= 0.1) {
            velocity = 100.0;
        } else if (deltaTimeJump < 0.3 && deltaTimeJump >= 0.2) {
            velocity = 145.0;
        } else if (deltaTimeJump < 0.4 && deltaTimeJump >= 0.3) {
            velocity = 185.0;
        } else if (deltaTimeJump < 0.5 && deltaTimeJump >= 0.4) {
            velocity = 220.0;
        } else if (deltaTimeJump < 0.6 && deltaTimeJump >= 0.5) {
            velocity = 250.0;
        } else if (deltaTimeJump < 0.7 && deltaTimeJump >= 0.6) {
            velocity = 270.0;
        } else {
            velocity = 285.0;
        }

        isJumping = true; // initiate jump
        jumpQueue = false; // reset counting ticks
    }

    if (isJumping) { // while jumping
        jumpQueue = false;
        if (lastSide == "left") { // check frog's current side
            lastAngle = -10;
            if (!hitHead) {
                if (!flagLeft) {
                    // scrollY = rect.y;

                    velocity = velocity + gravity * deltaTime;
                    rect.y = rect.y - velocity * deltaTime;

                    // scrollY -= rect.y;

                    rect.x = rect.x - 4;
                } else {
                    lastSide = "right";
                    flagLeft = false;
                }
            } else {
                if (!flagLeft) {
                    // scrollY = rect.y;

                    velocity = velocity + gravity * deltaTime;
                    rect.y = rect.y - velocity * deltaTime;

                    // scrollY -= rect.y;

                    rect.x = rect.x - 4;
                } else {
                    lastSide = "right";
                    flagLeft = false;
                }

            }
        }

        if (lastSide == "right") { // same as above
            lastAngle = 10;
            if (!hitHead) {
                if (!flagRight) {
                    // scrollY = rect.y;

                    velocity = velocity + gravity * deltaTime;
                    rect.y = rect.y - velocity * deltaTime;

                    // scrollY -= rect.y;

                    rect.x = rect.x + 4;
                } else {
                    lastSide = "left";
                    flagRight = false;
                }
            } else {
                if (!flagRight) {
                    // scrollY = rect.y;

                    velocity = velocity + gravity * deltaTime;
                    rect.y = rect.y - velocity * deltaTime;

                    // scrollY -= rect.y;

                    rect.x = rect.x + 4;
                } else {
                    lastSide = "left";
                    flagRight = false;
                }
            }
        }

        if (rect.x + rect.w > WIDTH) { // map boundry
            flagRight = true;
        }

        if (rect.x < 0) { // same as above
            flagLeft = true;
        }
    }

    if (!isJumping && left && rect.x > 0) { // moving left
        rect.x = (rect.x - 5);
        lastAngle = -10;
        lastSide = "left";
    }

    if (!isJumping && right && rect.x < WIDTH - rect.w) { // moving right
        rect.x = (rect.x + 5);
        lastAngle = 10;
        lastSide = "right";
    }

    if (velocity > 600) { // min/max
        velocity = 600;
    } else if (velocity < -600) {
        velocity = -600;
    }

    if (collision == "collisionOnTop" && !isJumping) { // collision fix
        if (collisionHeight > 1) {
            rect.y -= collisionHeight/2;
        }

        velocity = 0;

        flagRight = false;
        flagLeft = false;

        hitOnce = false;
    }

    if (collision != "false") {
        scrollY = 0;
    }

    oldPosY = rect.y;
}

int Player::getScrollY() {
    return scrollY;
}

bool Player::checkIfFinished(std::string collision) {
    if (rect.y < 100 && collision == "collisionOnTop") 
        return true;
    else 
        return false;
}

void Player::destroyImage() {
    SDL_DestroyTexture(texture);
}