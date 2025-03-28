#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>    
enum GameState{MENU,GAME,PAUSE,OPTIONS};
bool init(SDL_Window **window, SDL_Renderer **renderer);
SDL_Texture* loadTexture(const char* filePath, SDL_Renderer* renderer);
class Game{
    private:
        static GameState State;
        static bool initialized;; //track if initialized
        static float scale_x, scale_y;
   protected:
        static int window_width,window_height;
        static int initial_window_width,initial_window_height; 
        // used for dynamically resizing;
        static SDL_Renderer* renderer;
        static SDL_Window* window;
    public:
        Game();
        SDL_Renderer* getRenderer();
        SDL_Window* getWindow();
        void setGameState();
        void scale();
        GameState getGameState();
        void scaleEntity(SDL_Rect &position);
        static float getScaleX();
        static float getScaleY();
};
