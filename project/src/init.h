#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

enum GameState{MENU,GAME,PAUSE,OPTIONS};
// pointer ownership hell
bool init(SDL_Window **window, SDL_Renderer **renderer);
SDL_Texture* loadTexture(const char* filePath, SDL_Renderer* renderer);

class Game {
protected:
    static GameState State;
    static SDL_Renderer* renderer;
    static SDL_Window* window;
    static bool initialized; //track if initialized
public:
    Game(){
      /*
      1. why do you need to have this `if` wrapper
      if you can not even accidentally instantiate
      another game object?
      2. took me a while to see this. why in God's
      holy name did you do this and not make a
      GameManager class? `protected` and `static`
      in combination, that's a pretty neat hack but
      it obscures your code a lot tbh and i've been
      reading it for a couple of hours already
       */
        if(!initialized) {
            init(&window,&renderer);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);
            SDL_ShowWindow(window); // to not show blinking at the initialization
            initialized=true;
        }
    }
    [[nodiscard]] SDL_Renderer* getRenderer() const { return renderer; }
    [[nodiscard]] SDL_Window* getWindow() const { return window; }
    void setGameState();
    GameState getGameState();
};