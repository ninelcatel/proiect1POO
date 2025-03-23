#include "player.h"
const int moveDelay=5;
static int frameCounter=0;
Player::Player(int x, int y, int w, int h, SDL_Renderer *renderer, const char *filePath, float atkp, float armoor) 
    : Entity(x, y, w, h, renderer, filePath) {
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

void Player::handleEvent(SDL_Event &event) {
    if (event.type == SDL_KEYDOWN) {
        keyStates[event.key.keysym.sym] = true;
    } else if (event.type == SDL_KEYUP) {
        keyStates[event.key.keysym.sym] = false;
    }
}

void Player::update() {
    frameCounter++;
    if(frameCounter%moveDelay==0){
    for (const auto &pair : keyBindings) {
        if (keyStates[pair.first]) {
            (this->*pair.second)(); // Call movement functions dynamically
        }
    }}
}

void Player::moveUp() {
    const SDL_Rect rect = getPosition();
    setPosition(rect.x, rect.y - speed);
}

void Player::moveDown() {
    const SDL_Rect rect = getPosition();
    setPosition(rect.x, rect.y + speed);
}

void Player::moveLeft() {
    const SDL_Rect rect = getPosition();
    setPosition(rect.x - speed, rect.y);
}

void Player::moveRight() {
    const SDL_Rect rect = getPosition();
    setPosition(rect.x + speed, rect.y);
}
