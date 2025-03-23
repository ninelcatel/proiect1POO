#include "player.h"
const int animDelay = 500; // delay in ms
const int moveDelay = 5;
const int stayingDelay = 251;
static int frameCounter = 0;
static int animFrameCounter = 0;
Player::Player(int x, int y, int w, int h, SDL_Renderer *renderer, const char *filePath, float atkp, float armoor)
    : Entity(x, y, w, h, renderer, filePath)
{
    ap = atkp;
    armor = armoor;

    keyBindings[SDLK_w] = &Player::moveUp;
    keyBindings[SDLK_s] = &Player::moveDown;
    keyBindings[SDLK_a] = &Player::moveLeft;
    keyBindings[SDLK_d] = &Player::moveRight;

    keyStates[SDLK_w] = false;
    keyStates[SDLK_s] = false;
    keyStates[SDLK_a] = false;
    keyStates[SDLK_d] = false;
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
                if (animFrameCounter % animDelay == 0)
                {

                    if (!getIsFlipped())
                    {
                        switch (animFrameCounter % 7)
                        {
                        case 0:
                            changeAppearence("res/player.png", getRenderer());
                            break;
                        case 1:
                            changeAppearence("res/run1.png", getRenderer());
                            break;
                        case 2:
                            changeAppearence("res/run2.png", getRenderer());
                            break;
                        case 3:
                            changeAppearence("res/run3.png", getRenderer());
                            break;
                        case 4:
                            changeAppearence("res/run4.png", getRenderer());
                            break;
                        case 5:
                            changeAppearence("res/run5.png", getRenderer());
                            break;
                        case 6:
                            changeAppearence("res/run6.png", getRenderer());
                            break;
                        default:
                            break;
                        }
                    }
                    else
                    {
                        switch (animFrameCounter % 7)
                        {
                        case 0:
                            changeAppearence("res/flipped/player.png", getRenderer());
                            break;
                        case 1:
                            changeAppearence("res/flipped/run1.png", getRenderer());
                            break;
                        case 2:
                            changeAppearence("res/flipped/run2.png", getRenderer());
                            break;
                        case 3:
                            changeAppearence("res/flipped/run3.png", getRenderer());
                            break;
                        case 4:
                            changeAppearence("res/flipped/run4.png", getRenderer());
                            break;
                        case 5:
                            changeAppearence("res/flipped/run5.png", getRenderer());
                            break;
                        case 6:
                            changeAppearence("res/flipped/run6.png", getRenderer());
                            break;
                        default:
                            break;
                        }
                    }
                }
                (this->*pair.second)(); // Call movement functions dynamically
            }
        }
        if (moving == false && animFrameCounter % stayingDelay == 0)
        {
            if (!getIsFlipped())
                switch (frameCounter % 4)
                {
                case 0:
                    changeAppearence("res/player.png", getRenderer());
                    break;
                case 1:
                    changeAppearence("res/stay.png", getRenderer());
                    break;
                case 2:
                    changeAppearence("res/stay2.png", getRenderer());
                    break;
                case 3:
                    changeAppearence("res/stay.png", getRenderer());
                    break;
                default:
                    break;
                }
            else
            {
                switch (frameCounter % 4)
                {
                case 0:
                    changeAppearence("res/flipped/player.png", getRenderer());
                    break;
                case 1:
                    changeAppearence("res/flipped/stay.png", getRenderer());
                    break;
                case 2:
                    changeAppearence("res/flipped/stay2.png", getRenderer());
                    break;
                case 3:
                    changeAppearence("res/flipped/stay.png", getRenderer());
                    break;
                default:
                    break;
                }
            }
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
