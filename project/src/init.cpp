
#include "init.h"
SDL_Renderer* Game::renderer=nullptr;
SDL_Window* Game::window=nullptr;
bool Game::initialized=false;
bool init(SDL_Window **window, SDL_Renderer **renderer)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL INIT ERROR" << SDL_GetError();
        return true;
    }
    *window = SDL_CreateWindow("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 720, SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE);

    if (!window)
    {
        std::cerr << "SDL COULDNT INITIALIZE WINDOW" << SDL_GetError();
        SDL_Quit();
        return true;
    }
       
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        std::cerr << "SDL COULDNT INITIALIZE RENDERER" << SDL_GetError();
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return true;
    }
        
    SDL_SetRenderDrawColor(*renderer, 0, 0, 0, 255);
    SDL_RenderClear(*renderer);
    SDL_RenderPresent(*renderer);
    SDL_Delay(10);
    return false;
}
SDL_Texture *loadTexture(const char *filePath, SDL_Renderer *renderer)
{
    SDL_Texture *texture = nullptr;
    SDL_Surface *loadedSurface = IMG_Load(filePath);
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "Failed to initialize PNG support: " << IMG_GetError() << std::endl;
    }
    if (!loadedSurface)
    {
        std::cerr << "img couldn't load " <<filePath<<" "<<SDL_GetError()<<" "<< std::endl;
        return nullptr;
    }
    texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
    return texture;
}
