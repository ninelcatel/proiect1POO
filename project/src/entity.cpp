
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "entity.h"
#include <iostream>
void Entity::setHealth(int health)
{
    current_hp = health;
}
void Entity::setPosition(int x, int y)
{
    position.x = x;
    position.y = y;
}
void Entity::setSize(int w, int h)
{
    position.w = w;
    position.h = h;
}
int Entity::getHealth()
{
    return hp;
}
SDL_Rect Entity::getPosition() // also gives entity size with .h and .w;
{
    return position;
}
void Entity::changeAppearence(const char *filePath)
{
    if (filePath == nullptr)
    {
        std::cerr << "ERROR: filePath is NULL" << std::endl;
        return;
    }
    texture = loadTexture(filePath, renderer);
}

void Entity::render()
{
    if (window)
    {
        SDL_GetWindowSize(window, &window_width, &window_height);
        setSize(window_width * 0.1, window_height * 0.15);
    }
    else
    {
        std::cerr << "WINDOW IS NULL" << " " << SDL_GetError() << std::endl;
        return;
    }
    SDL_RenderCopy(renderer, texture, nullptr, &position);
}
SDL_Texture *Entity::getTexture()
{
    return texture;
}
const char *Entity::getFilePath()
{

    return filePath;
}
void Entity::setFilePath(const char *newPath)
{
    filePath = newPath;
}
SDL_Renderer *Entity::getRenderer()
{
    return renderer;
}
void Entity::setIsFlipped(bool flip)
{
    isFlipped = flip;
}
bool Entity::getIsFlipped()
{
    return isFlipped;
}
int Entity::getCurrentHealth()
{
    return current_hp;
}
void Entity::setMaxHealth(int health)
{
    hp = health;
}
bool Entity::isValidMove(Direction dir)
{

    if (window)
        SDL_GetWindowSize(window, &window_width, &window_height);
    else
    {
        std::cerr << "window is null!" << " " << SDL_GetError() << std::endl;
    }
    float upperBound = 110.0f * (window_height / 720.0f);
    float lowerBound = 485.0f * (window_height / 720.0f);
    float leftBound = 145.0f * (window_width / 1024.0f);
    float rightBound = 770.0f * (window_width / 1024.0f);
    // dont go out of bounds
    //  1024x720
    //  upper bound: y=110;
    //  lower bound: y=485
    //  left bound: x=145;
    //  right bound: x=77

    switch (dir)
    {
    case UP:
        return !(position.y <= upperBound);
    case DOWN:
        return !(position.y >= lowerBound);
    case LEFT:
        return !(position.x <= leftBound);
    case RIGHT:
        return !(position.x >= rightBound);
    case NONE:
        return true;
        ;
    default:
        return true;
    }
}
void Entity::takeDamage()
{
    
    auto currentTime = std::chrono::steady_clock::now();
    std::vector<FireZone> &fire = getFireZones();
    for (auto it = fire.begin(); it != fire.end();)
    {
        if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - it->activationTime).count() >= it->howLong)
        {   
            it = fire.erase(it);
            std::cout<<"TIME EXPIRED!"<<std::endl;
            continue;
        }
        else{
            std::cout<<position.x<<" "<<position.y<<" "<<position.w<<" "<<position.h<<std::endl<<it->zone.x<<" "<<it->zone.y<<" "<<it->zone.w<<" "<<it->zone.h<<" "<<std::endl;
            if (SDL_HasIntersection(&position, &it->zone))
        {
            setHealth(getCurrentHealth() - 5);
            std::cout<<"TAKING DAMAGE! "<<getCurrentHealth()<<std::endl;
        }
        ++it;
        }
    }
}