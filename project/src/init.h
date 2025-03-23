#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

bool init(SDL_Window **window, SDL_Renderer **renderer);
SDL_Texture* loadTexture(const char* filePath, SDL_Renderer* renderer);