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
            std::cerr << "COULDN'T LOAD TEXTURE" << std::endl;
        }
    } // coordinates + where to render and image loaded;
    ~Entity()
    {
        SDL_DestroyTexture(texture);
    }
    // UTILITY
    void changeAppearence(const char *filePath); // change the loaded texture | you made a typo here
    SDL_Texture* flipTexture(SDL_Texture* original);
    void render();
    bool isValidMove(Direction dir);
    // GETTERS | good habit to mark getters as `[[nodiscard]]` and `const`
    [[nodiscard]] int getHealth() const { return hp; };
    [[nodiscard]] int getCurrentHealth() const { return current_hp; };
    [[nodiscard]] SDL_Texture* getTexture() const { return texture; };
    [[nodiscard]] const char* getFilePath() const { return filePath; };
    [[nodiscard]] bool getIsFlipped() const { return isFlipped; };
    [[nodiscard]] SDL_Rect getPosition() const { return position; };
    [[nodiscard]] SDL_Renderer* getRenderer() const { return renderer; };
    // SETTERS
    void setHealth(const int newHp) { current_hp = newHp; };
    void setMaxHealth(const int newHp) { hp = newHp; }
    void setPosition(const int x = 0, const int y = 0) { position = {.x = x, .y = y}; } // why does setPosition have default arguments?
    void setFilePath(const char* newPath) { filePath = newPath; } // maybe check on setting the file path if it's valid or not? that's why you use setters and getters, for providing easy to use APIs
    void setIsFlipped(const bool flip) { isFlipped = flip; }
    void setSize(const int w, const int h) { position = {.w = w, .h = h}; }

};
