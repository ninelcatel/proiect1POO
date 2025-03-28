#include "player.h"
#include <vector>
#include <cmath>
const int animDelay = 500; // delay in ms
const int moveDelay = 5;
const int stayingDelay = 251;
static int frameCounter = 0;
static int animFrameCounter = 0;

Player::Player(const char *filePath, float atkp, float armoor)
    : Entity(filePath)
    {
    // SDL_GetWindowSize(window, &initial_window_width, &initial_window_height);   
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
    keyBindings[SDLK_f] = &Player::attack;

    keyStates[SDLK_w] = false;
    keyStates[SDLK_s] = false;
    keyStates[SDLK_a] = false;
    keyStates[SDLK_d] = false;
    keyStates[SDLK_f] = false;

    keyToDirection[SDLK_w] = UP;
    keyToDirection[SDLK_s] = DOWN;
    keyToDirection[SDLK_a] = LEFT;
    keyToDirection[SDLK_d] = RIGHT;
    keyToDirection[SDLK_f] = NONE;
    
    
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
    else if (event.type == SDL_WINDOWEVENT)
    {
        if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
{   
    SDL_Rect pos=getPosition();
    // scaleEntity(pos);
    scale();
    pos.x=static_cast<int>(pos.x*getScaleX());
    pos.y=static_cast<int>(pos.y*getScaleY());
    setPosition(pos.x,pos.y);
    speed = 0.75f * getScaleY();
    
    /*SDL_GetWindowSize(window, &window_width, &window_height);
    float scale_x = static_cast<float>(window_width) / initial_window_width;
    float scale_y = static_cast<float>(window_height) / initial_window_height;

    SDL_Rect current_position = getPosition();

    setPosition(
        static_cast<int>(current_position.x * scale_x),
        static_cast<int>(current_position.y * scale_y)
    );
    initial_window_width=window_width;
    initial_window_height=window_height;*/
}
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
        int frameModulo = moving ? 7 : 4; //7 frames for moving, 4 for staying
        if((animFrameCounter %(moving ? animDelay : stayingDelay))==0){
            animation(getIsFlipped(),moving,animFrameCounter%frameModulo);
        }
    }
}
void Player::moveUp()
{
    const SDL_Rect rect = getPosition();
    setPosition(rect.x, static_cast<int>(rect.y - speed));
}

void Player::moveDown()
{
    const SDL_Rect rect = getPosition();
    setPosition(rect.x, static_cast<int>(rect.y + 2*speed));
}

void Player::moveLeft()
{
    const SDL_Rect rect = getPosition();
    setPosition(static_cast<int>(rect.x - speed), rect.y);
}

void Player::moveRight()
{
    const SDL_Rect rect = getPosition();
    setPosition(static_cast<int>(rect.x + 2*speed), rect.y);
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
    std::string prefix = isFlipped ? "res/PLAYER/FLIPPED/" : "res/PLAYER/";
    std::vector<std::string> suffix=isMoving ? std::vector<std::string>{"player","run1","run2","run3","run4","run5","run6"} : std::vector<std::string>{"player","stay","stay2","stay"};
    std::string filePath=prefix+suffix[index]+".png"; //whole path;
    changeAppearence(filePath.c_str()); //change from std::string to const char*
}
void Player::attack(){
}