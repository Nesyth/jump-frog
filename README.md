# „Jump, Frog!” - clone of „Jump King” written in C++
 
![recording](https://github.com/Nesyth/slue/assets/18372752/3b38a1f5-f419-472c-957b-cb52e4aad83a)

## What's done?

- Rigid body physics.
- Collision system.
- High score measurement (time from start to finish).

## Tech Stack

C++, SDL2

## Controls

* **Left/right key** - left/right movement
* **Up key** - jump (holding the key results in a higher jump)

## Installation
 
Compile the repo with SDL2, SDL2_image, SDL2_ttf.

Example:
* Download SDL2, SDL2_image and SDL2_ttf.
* Place contents inside the repository.
* Run ```g++ -std=c++17 src/*.cpp -oplay -Iinclude/SDL2 -Llib -lSDL2 -lSDL2_image  -lSDL2_ttf```
* Run ```./play```