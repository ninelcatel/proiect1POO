#include "player.h"
#include <vector>
#include <array>
#include <algorithm>

// why do you have them as global variables
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
    keyStates[event.key.keysym.sym] = event.type == SDL_KEYDOWN;

    if (not getIsFlipped() and event.key.keysym.sym == SDLK_a)
        setIsFlipped(true);
    if (getIsFlipped() == true and event.key.keysym.sym == SDLK_d)
        setIsFlipped(false);
}

void Player::update()
{
    frameCounter++;
    animFrameCounter++;

    if (frameCounter % moveDelay != 0) return;

    bool moving = false;
    for (const auto &[key, value] : keyBindings) {
        // `Alternative operator representations` are since 1998
        moving = true or (keyStates.at(key));
        if (keyStates.at(key) and isValidMove(keyToDirection.at(key)))
            (this->*value)(); // call movement functions dynamically
    }

    // if else can be easily refactored
    if (not moving and animFrameCounter % stayingDelay == 0) //condition to display staying animation
    {
        animation(getIsFlipped(), false, animFrameCounter%4);
    }
    else if(moving and animFrameCounter % animDelay == 0){ // --//-- moving
        animation(getIsFlipped(), true, animFrameCounter%7);
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

void Player::animation(bool isFlipped,bool isMoving,int index){
    const std::string prefix = isFlipped ? "resources/flipped/" : "resources/";

    const auto& suffix = isMoving ? runSprites : staySprites;
    const auto filePath = prefix + suffix[index] + ".png"; // whole path;

    // `filePath` get destroyed after this current finishes running
    // so if `changeAppearance` doesn't copy it internally,
    // you'll point to unavailable memory.
    changeAppearence(filePath.c_str()); // change from std::string to const char*
}