#pragma once

#include "init.h"
#include <iostream>

// why do you create Direction enum here when you use it inside player.h and only there?
// why do you need to create it globally?
enum Direction {UP,DOWN,LEFT,RIGHT};

class Entity : public Game
{
private:
    // c++ initialization is made in order of the declaration of the variables
    // so look up into structure member alignment, padding and data packing
    SDL_Rect position{};
    SDL_Texture *texture{nullptr};
    const char *filePath{nullptr};
    int hp{} , current_hp{};
    bool isFlipped{false};

public:
    // Clang-Tidy: `Single-argument constructors must be marked explicit to avoid unintentional implicit conversions`
    // Clang-Tidy: `Constructor does not initialize these fields: position, hp, current_hp`
    explicit Entity(const char *filePath = nullptr)
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
    // why does setPosition have default arguments?
    void setPosition(int x=0, int y=0);
    void changeAppearence(const char *filePath); // change the loaded texture
    SDL_Texture* flipTexture(SDL_Texture* original);
    void render();
    void setFilePath(const char* filePath);
    void setIsFlipped(bool flip);
    void setSize(int w,int h);
    bool isValidMove(Direction dir);
};
