#include "enemy.h"
int STEP_SIZE=1;
Enemy::Enemy(const char *filePath) : Entity(filePath)
{
    isEnemy = true;
}
void Enemy::update(Player &player)
{

    SDL_Rect playerRect = player.getPosition();
    SDL_Rect enemyRect = getPosition();
    if (frameCounter % 4003 == 0)
    {
        setIsHit(false);
        takeDamage();
    }
    if(frameCounter%60==0){                     //very naive and it gets stuck easily , use some pathing algorithm
                                                // since we have acces to the layout matrix and alreadt have the getRoomIndexes func
        int distX=playerRect.x - enemyRect.x;
        int distY=playerRect.y - enemyRect.y;
        int sgnX=distX < 0 ? -1 : 1;
        int sgnY=distY < 0 ? -1 : 1;
        Direction dirX = sgnX < 0 ? LEFT : RIGHT;
        Direction dirY = sgnY < 0 ? UP : DOWN;
        distX=abs(distX);
        distY=abs(distY);
         bool canMoveX = isValidMove(dirX);
        bool canMoveY = isValidMove(dirY);
        if(canMoveX && canMoveY){
            if(distX>=distY){
                setPosition(enemyRect.x+sgnX*STEP_SIZE,enemyRect.y);
            }
            else setPosition(enemyRect.x,enemyRect.y+sgnY*STEP_SIZE);
        }
        else if(canMoveX && !canMoveY){
                setPosition(enemyRect.x+sgnX*STEP_SIZE,enemyRect.y);
        }
        else if(canMoveY && !canMoveX){
            setPosition(enemyRect.x,enemyRect.y+sgnY*STEP_SIZE);   
        }
    }
    SDL_Rect position = getPosition(); // scale accordingly to the resolution, scale is called again after updating the whole vector
    position.x = static_cast<int>((position.x * getScaleX()));
    position.y = static_cast<int>((position.y * getScaleY()));
    position.w = static_cast<int>((position.w * getScaleY()));
    position.h = static_cast<int>((position.h * getScaleY()));
    setPosition(position.x, position.y);
}
