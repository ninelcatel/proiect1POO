#pragma once
#include "init.h"
#include <SDL2/SDL.h>
#include <iostream>
class Entity
{
        

private:
    SDL_Rect position;
    SDL_Texture *texture;
    const char *filePath;
    int hp;

public:
    Entity(int x=0, int y=0, int w=0, int h=0, SDL_Renderer *renderer=NULL, const char *filePath=NULL)
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
    SDL_Texture* getTexture();
    const char* getFilePath();
    SDL_Rect getPosition();
    void setHealth(int hp);
    void setPosition(int x=0, int y=0);
    void changeAppearence(char *filePath, SDL_Renderer *renderer); // change the loaded texture
    void render(SDL_Renderer *renderer);
    void setFilePath(const char* filePath);
};