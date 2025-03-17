#include <SDL2/SDL.h>
#include <entity.h>
Entity::Entity() {
    hp=1;
    position={0,0,64,64};
};
Entity:: ~Entity(){};
void Entity::setHealth(int health){
    hp=health;
}

void Entity::setPosition(int x,int y){
    position.x=x;
    position.y=y;
}

int Entity::getHealth(){
    return hp;
}

SDL_Rect Entity::getPosition(){
    return position;
}