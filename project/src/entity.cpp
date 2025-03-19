
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "entity.h"
#include "init.h"
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
void Entity::changeAppearence(char *filePath, SDL_Renderer *renderer)
{
    texture = loadTexture(filePath, renderer);
}
void Entity::render(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, texture, nullptr, &position);
}