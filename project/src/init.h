#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

enum GameState{MENU,GAME,PAUSE,OPTIONS};
// pointer ownership hell
bool init(SDL_Window **window, SDL_Renderer **renderer);
SDL_Texture* loadTexture(const char* filePath, SDL_Renderer* renderer);

class Game{
    protected:
        static GameState State;
        static SDL_Renderer* renderer;
        static SDL_Window* window;
        static bool initialized; //track if initialized
    public:
        Game(){
            // Why do you need to have this `if` wrapper if you can not even accidentally instantiate another game object
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
        void setGameState();
        GameState getGameState();
};