#pragma once
#include <iostream>
#include <unordered_map>
#include "entity.h"
class Player : public Entity {
private:
    float ap, armor;
    int energy,current_energy;
    const int speed = 1;  
    std::unordered_map<SDL_Keycode, void(Player::*)()> keyBindings; //function pointer for movement
    std::unordered_map<SDL_Keycode, bool> keyStates;    //which keys are pressed so diagonal and smooth movement is possible
    std::unordered_map<SDL_Keycode,Direction>keyToDirection; //for not going out of bounds
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void attack();
    void dash();

public:
    int initial_window_width,initial_window_height;
    Player(const char *filePath, float atkp, float armoor);
    void update();
    void handleEvent(SDL_Event &event);
    void setEnergy(int energy);
    int getEnergy();
    void setMaxEnergy(int energy);
    int getCurrentEnergy();
    void animation(bool isFlipped,bool isMoving,int frame);
};
