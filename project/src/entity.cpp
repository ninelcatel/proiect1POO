//line 153 make animation for entities when hit
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "entity.h"
#include <algorithm>
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
    {   int passedTime=std::chrono::duration_cast<std::chrono::seconds>(currentTime - it->activationTime).count();
        if ((passedTime) >= (it->howLong))
        {
            it=fire.erase(it);
            setIsHit(false);
            // std::cout<<fire.size()<<std::endl;
            // std::cout << "Time Passed: " << passedTime << ", Attack Duration: " << it->howLong << std::endl;
            // std::cout<<"TIME EXPIRED!"<<std::endl;
        }
        else 
        {   if (!getIsHit()){
            SDL_Rect hitbox = it->zone;
            hitbox.x = static_cast<int>((hitbox.x + 30) * getScaleX()); // make the hitbox smaller
            hitbox.y = static_cast<int>((hitbox.y + 30) * getScaleY());
            hitbox.w = static_cast<int>((hitbox.w - 60) * getScaleX());
            hitbox.h = static_cast<int>((hitbox.h - 90) * getScaleY());

            if (this->position.x != it->zone.x  // so it doesnt take damage from itself , maybe add another conditon for entityType or such.
                && this->isEnemy != it->isEnemy // skeleton wont damage another skeleton
                && SDL_HasIntersection(&position, &hitbox)
               )
            {
                setHealth(getCurrentHealth() - 5);
                setIsHit(true);
                // std::cout<<position.x<<" "<<position.y<<" "<<position.w<<" "<<position.h<<" "<<it->zone.x<<" "<<it->zone.y<<" "<<it->zone.w<<" "<<it->zone.h<<std::endl;
                std::cout << "TAKING DAMAGE! " << getCurrentHealth() << " " <<it->isEnemy<<" "<<it->howLong<<" "<< std::endl;
            }
            }
            ++it;  
        }
    }
}
void Entity::attack()
{   if(timeSinceLastAttack<=250) return;
    SDL_Rect attack_range;
    attack_range = position;
    int eyeFrames = isFlipped ? -30 : 30;
    attack_range.x = static_cast<int>((attack_range.x + eyeFrames) * getScaleX());
    attack_range.y = static_cast<int>(attack_range.y * getScaleY());
    pushFireZone(attack_range, 1, isEnemy);
    timeSinceLastAttack=0;
}
void Entity::setIsHit(bool isHit)
{
    alreadyHit = isHit;
}
bool Entity::getIsHit()
{
    return alreadyHit;
}
void Entity::animation(bool isMoving, int index)
{
    std::string prefix = isEnemy ? "res/ENEMY/SKELETON/": "res/PLAYER/";
    prefix = prefix + (alreadyHit ? "" : isAttacking ? "ATTACK/" : "") + (isFlipped ? "FLIPPED/" : "") ; // add this for already hit
    std::vector<std::string> suffix = isEnemy ? alreadyHit ? 
    std::vector<std::string>{"SKELETON","SKELETON_HIT","SKELETON"} 
    : isAttacking ? 
    std::vector<std::string>{"SKELETON", "ATTACK1", "ATTACK2", "ATTACK3"} : 
    isMoving ? 
    std::vector<std::string>{"SKELETON", "run1", "run2", "run3", "run4", "run5", "run6"} 
    : std::vector<std::string>{"SKELETON", "SKELETON", "SKELETON", "SKELETON"}
    :
    alreadyHit ? 
    std::vector<std::string>{"player","PLAYER_HIT","player","PLAYER_HIT"} 
    : isAttacking ? 
    std::vector<std::string>{"player", "ATTACK1", "ATTACK2", "ATTACK3"} : 
    isMoving ? 
    std::vector<std::string>{"player", "run1", "run2", "run3", "run4", "run5", "run6"} 
    : std::vector<std::string>{"player", "stay", "stay2", "stay"};
    // std::cout<<index<<" ";

    int maxIndex = suffix.size() - 1;
    if (index < 0 || index > maxIndex) {
        // std::cerr << "Invalid animation index: " << index << ", max: " << maxIndex << std::endl;
        return;  // Prevent segmentation fault
    }

    std::string filePath = prefix + suffix[index] + ".png"; // whole path;
    changeAppearence(filePath.c_str());                     // change from std::string to const char*
}
void Entity::setIsAttacking(bool attk){
    isAttacking=attk;
}
bool Entity::getIsAttacking(){
    return isAttacking;
}