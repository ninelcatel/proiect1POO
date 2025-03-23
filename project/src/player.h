#pragma once
#include <iostream>
#include <unordered_map>
#include "entity.h"

class Player : public Entity {
private:
    float ap, armor;
    const int speed = 1;
    std::unordered_map<SDL_Keycode, void(Player::*)()> keyBindings;
    std::unordered_map<SDL_Keycode, bool> keyStates;

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void attack();
    void dash();

public:
    Player(int x, int y, int w, int h, SDL_Renderer *renderer, const char *filePath, float atkp, float armoor);
    void update();
    void handleEvent(SDL_Event &event);
};
