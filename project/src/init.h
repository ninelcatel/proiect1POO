#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
int init(SDL_Window **window,SDL_Renderer **renderer){
if(SDL_Init(SDL_INIT_VIDEO)!=0){
        std::cerr<<"SDL INIT ERROR"<<SDL_GetError();
        return 1;
    }
    *window= SDL_CreateWindow("game",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1024,720,SDL_WINDOW_SHOWN);
    
    if(!window){
        std::cerr<<"SDL COULDNT INITIALIZE WINDOW"<<SDL_GetError();
        SDL_Quit();
        return 1;
    }
    *renderer = SDL_CreateRenderer(*window,-1,SDL_RENDERER_ACCELERATED);
    if(!renderer){
        std::cerr<<"SDL COULDNT INITIALIZE RENDERER"<<SDL_GetError();
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return 1;
    }
    return 0;
}
SDL_Texture *loadTexture(const char* filePath,SDL_Renderer* renderer){
    SDL_Texture *texture = NULL;
    SDL_Surface *loadedSurface=IMG_Load(filePath);
    if(!loadedSurface){
        std::cerr<<"img couldn't load"<<std::endl;
        return NULL;
    }
    texture=SDL_CreateTextureFromSurface(renderer,loadedSurface);
    SDL_FreeSurface(loadedSurface);
    return texture;
}