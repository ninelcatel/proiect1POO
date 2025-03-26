#include "player.h"
#include <vector>
const int animDelay = 500; // delay in ms
const int moveDelay = 5;
const int stayingDelay = 251;
static int frameCounter = 0;
static int animFrameCounter = 0;
Player::Player(const char *filePath, float atkp, float armoor)
    : Entity(filePath)
{   
    setPosition(200,200);
    ap = atkp;
    armor = armoor;
    setHealth(20);
    setMaxHealth(30);
    energy = 40;
    current_energy = 20;
    keyBindings[SDLK_w] = &Player::moveUp;
    keyBindings[SDLK_s] = &Player::moveDown;
    keyBindings[SDLK_a] = &Player::moveLeft;
    keyBindings[SDLK_d] = &Player::moveRight;

    keyStates[SDLK_w] = false;
    keyStates[SDLK_s] = false;
    keyStates[SDLK_a] = false;
    keyStates[SDLK_d] = false;

    keyToDirection[SDLK_w] = UP;
    keyToDirection[SDLK_s] = DOWN;
    keyToDirection[SDLK_a] = LEFT;
    keyToDirection[SDLK_d] = RIGHT;
}

void Player::handleEvent(SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN)
    {
        keyStates[event.key.keysym.sym] = true;
        if (getIsFlipped() == false && event.key.keysym.sym == SDLK_a)
            setIsFlipped(true);
        else if (getIsFlipped() == true && event.key.keysym.sym == SDLK_d)
            setIsFlipped(false);
    }
    else if (event.type == SDL_KEYUP)
    {
        keyStates[event.key.keysym.sym] = false;
    }
}

void Player::update()
{
    bool moving = false;
    frameCounter++;
    animFrameCounter++;
    if (frameCounter % moveDelay == 0)
    {
        for (const auto &pair : keyBindings)
        {
            if (keyStates[pair.first])
            {
                moving = true;
                if (isValidMove(keyToDirection[pair.first]))
                {
                    (this->*pair.second)(); // call movement functions dynamically
                }
            }
        }
        if (!moving && animFrameCounter % stayingDelay == 0) //condition to display staying animation
        {
            animation(getIsFlipped(),false,animFrameCounter%4);
        }
        else if(moving && animFrameCounter%animDelay==0){ // --//-- moving
            animation(getIsFlipped(),true,animFrameCounter%7);
        }
    }
}
void Player::moveUp()
{
    const SDL_Rect rect = getPosition();
    setPosition(rect.x, rect.y - speed);
}

void Player::moveDown()
{
    const SDL_Rect rect = getPosition();
    setPosition(rect.x, rect.y + speed);
}

void Player::moveLeft()
{
    const SDL_Rect rect = getPosition();
    setPosition(rect.x - speed, rect.y);
}

void Player::moveRight()
{
    const SDL_Rect rect = getPosition();
    setPosition(rect.x + speed, rect.y);
}
void Player::setEnergy(int eng)
{ // eng=energy;
    current_energy = eng;
}
void Player::setMaxEnergy(int eng)
{
    energy = eng;
}
int Player::getEnergy()
{
    return energy;
}
int Player::getCurrentEnergy()
{
    return current_energy;
}
 void Player::animation(bool isFlipped,bool isMoving,int index){
    std::string prefix = isFlipped ? "res/flipped/" : "res/";
    std::vector<std::string> suffix=isMoving ? std::vector<std::string>{"player","run1","run2","run3","run4","run5","run6"} : std::vector<std::string>{"player","stay","stay2","stay"};
    std::string filePath=prefix+suffix[index]+".png"; //whole path;
    changeAppearence(filePath.c_str()); //change from std::string to const char*
}