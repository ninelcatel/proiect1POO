#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

bool init(SDL_Window **window, SDL_Renderer **renderer);
SDL_Texture* loadTexture(const char* filePath, SDL_Renderer* renderer);
class Game{
    protected:
        static SDL_Renderer* renderer;
        static SDL_Window* window;
        static bool initialized;; //track if initialized
    public:
        Game(){
            if(!initialized) {
                init(&window,&renderer);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);
            SDL_ShowWindow(window); // to not show blinking at the initialization
            initialized=true;
            }
        }
        SDL_Renderer* getRenderer();
        SDL_Window* getWindow();
};