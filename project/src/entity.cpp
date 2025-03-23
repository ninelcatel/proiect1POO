
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "entity.h"
#include <iostream>
void Entity::setHealth(int health)
{
    hp = health;
}
void Entity::setPosition(int x, int y)
{
    position.x = x;
    position.y = y;
}

int Entity::getHealth()
{
    return hp;
}
SDL_Rect Entity::getPosition()
{
    return position;
}
void Entity::changeAppearence(const char *filePath, SDL_Renderer *renderer)
{   
    if (filePath == nullptr) {
        std::cerr << "ERROR: filePath is NULL!" << std::endl;
        return;
    }
    texture = loadTexture(filePath, renderer);
}

void Entity::render(SDL_Renderer *renderer)
{
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
void Entity::setIsFlipped(bool flip){
    isFlipped=flip;
}
bool Entity::getIsFlipped(){
    return isFlipped;
}
