
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
{   
     if(window) {
        SDL_GetWindowSize(window,&window_width,&window_height);
        setSize(window_width*0.1,window_height*0.15);
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
    std::cout/*<<window_width<<" "<<window_height<<std::endl*/<<position.x<<" "<<position.y<<std::endl;
    switch(dir){ //dont go out of bounds            
                // 1024x720 
                // upper bound: y=110;
                // lower bound: y=485
                // left bound: x=145;
                // right bound: x=770
                
        case UP:
            return !(position.y>=0 && position.y<=5) ;
        case DOWN:
            return !(position.y>=window_height-5-position.h && position.y<=window_height-position.h) ;
        case LEFT:
            return !(position.x>=0 && position.x<=5) ;
        case RIGHT:
            return !(position.x>=window_width-5-position.w && position.x<=window_width-position.w) ;
        case NONE:
            return true;
        default:        
            return true;
    }
}