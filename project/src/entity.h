#pragma once
#include "init.h"
#include <SDL2/SDL.h>
#include <iostream>
enum Direction{UP,DOWN,LEFT,RIGHT,NONE};
class Entity : public Game
{
private:
    SDL_Rect position;
    SDL_Texture *texture;
    const char *filePath;
    int hp,current_hp;
    bool isFlipped=false;


public:
    Entity(const char *filePath=NULL)
    { 
        texture = loadTexture(filePath, renderer);
        if (!texture)
        {
            std::cerr << "COULDNT LOAD TEXTURE" << std::endl;
        }
    } // coordinates + where to render and image loaded;
    ~Entity()
    {
        SDL_DestroyTexture(texture);
    }
    int getHealth();
    int getCurrentHealth();
    SDL_Texture* getTexture();
    const char* getFilePath();
    bool getIsFlipped();
    SDL_Rect getPosition();
    SDL_Renderer* getRenderer();
    void setHealth(int hp);
    void setMaxHealth(int hp);
    void setPosition(int x, int y);
    void changeAppearence(const char *filePath); // change the loaded texture
    SDL_Texture* flipTexture(SDL_Texture* original);
    void render();
    void setFilePath(const char* filePath);
    void setIsFlipped(bool flip);
    void setSize(int w,int h);
    bool isValidMove(Direction dir);
    void takeDamage();
};
