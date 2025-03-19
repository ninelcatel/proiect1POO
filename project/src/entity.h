#pragma once
#include "init.h"
#include <SDL2/SDL.h>
#include <iostream>
class Entity
{
        

protected:
    SDL_Rect position;
    SDL_Texture *texture;
    const char *filePath;
    int hp;

public:
    Entity(int x, int y, int w, int h, SDL_Renderer *renderer, const char *filePath)
    {
        texture = loadTexture(filePath, renderer);
        if (!texture)
        {
            std::cerr << "COULDNT LOAD TEXTURE" << std::endl;
        }
        position = {x, y, w, h};
    } // coordinates + where to render and image loaded;
    ~Entity()
    {
        SDL_DestroyTexture(texture);
    }
    int getHealth();
    SDL_Rect getPosition();
    void setHealth(int hp);
    void setPosition(int x, int y);
    void changeAppearence(char *filePath, SDL_Renderer *renderer); // change the loaded texture
    void render(SDL_Renderer *renderer);
};