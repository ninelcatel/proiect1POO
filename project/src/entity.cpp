
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
void Entity::setSize(int w, int h){
    position.w=w;
    position.h=h;
}
int Entity::getHealth()
{
    return hp;
}
SDL_Rect Entity::getPosition()  //also gives entity size with .h and .w;
{
    return position;
}
// `filePath` member already exists so renamed this parameter to `path`
void Entity::changeAppearence(const char *path)
{
    if (path == nullptr)
    {
        std::cerr << "ERROR: filePath is NULL" << std::endl;
        return;
    }
    texture = loadTexture(path, renderer);
}

void Entity::render()
{   int window_width=0,window_height=0;
    if(window) {
        SDL_GetWindowSize(window,&window_width,&window_height);
        position.w=window_width*0.1;
        position.h=window_height*0.15;
    }
    else{
        std::cerr<<"WINDOW IS NULL"<<" "<<SDL_GetError()<<std::endl;
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
// maybe check on setting the file path if it's valid or not?
// that's why you use setters and getters, for providing easy to use APIs
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
    // undefined behaviour waiting to happen but such is the c api ig
    int window_width = 0;
    int window_height = 0;
    SDL_GetWindowSize(window,&window_width,&window_height);

    // std::cout<<window_width<<" "<<window_height<<std::endl<<position.x<<" "<<position.y<<std::endl;

    switch(dir){
        case UP:
            return not (position.y>=0 && position.y<=5);
        case DOWN:
            return not (position.y>=window_height-5-position.h && position.y<=window_height-position.h);
        case LEFT:
            return not (position.x>=0 && position.x<=5);
        case RIGHT:
            return not (position.x>=window_width-5-position.w && position.x<=window_width-position.w);
        default:
            return true;
    }
}