#pragma once
#include <iostream>
#include <unordered_map>
#include "entity.h"
class Player : public Entity {
private:
    float ap, armor;
    int energy,current_energy;
    const int speed = 1;  
    std::unordered_map<SDL_Keycode, void(Player::*)()> keyBindings;
    std::unordered_map<SDL_Keycode, bool> keyStates;
    std::unordered_map<SDL_Keycode,Direction>keyToDirection;
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void attack();
    void dash();

public:
    Player(int x, int y, int w, int h, SDL_Renderer *renderer,SDL_Window* window, const char *filePath, float atkp, float armoor);
    void update();
    void handleEvent(SDL_Event &event);
    void setEnergy(int energy);
    int getEnergy();
    void setMaxEnergy(int energy);
    int getCurrentEnergy();
};
