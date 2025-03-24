
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
    int window_width=0,window_height=0;
    if(window) SDL_GetWindowSize(window,&window_width,&window_height);
    else{
        std::cerr<<"window is null!"<<" "<<SDL_GetError()<<std::endl;
    }
    std::cout<<window_width<<" "<<window_height<<std::endl<<position.x<<" "<<position.y<<std::endl;
    switch(dir){
        case UP:
            if(position.y>=0 && position.y<=5) return false;
            break;
        case DOWN:
            if(position.y>=window_height-5-position.h && position.y<=window_height-position.h) return false;
            break;
        case LEFT:
            if(position.x>=0 && position.x<=5) return false;
            break;
        case RIGHT:
            if(position.x>=window_width-5-position.w && position.x<=window_width-position.w) return false;
            break;
        default:
            
            break;
    }
    return true;
}