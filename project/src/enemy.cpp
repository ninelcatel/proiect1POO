#include "enemy.h"
Enemy::Enemy(const char *filePath): Entity(filePath){
    isEnemy=true;
    
}
void Enemy::update(){
    if (frameCounter % 4003 == 0)
        {
            setIsHit(false);
            takeDamage();
        }
        
        SDL_Rect position=getPosition();
        position.x = static_cast<int>((position.x * getScaleX()));
        position.y = static_cast<int>((position.y * getScaleY()));
        position.w = static_cast<int>((position.w * getScaleY()));
        position.h = static_cast<int>((position.h * getScaleY()));
        setPosition(position.x,position.y);

        
}