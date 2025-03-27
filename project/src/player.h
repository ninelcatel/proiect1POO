#pragma once

#include "entity.h"
#include <iostream>
#include <unordered_map>
#include <array>

class Player : public Entity {
// access specifier does not change accessibility level
// plus it makes no sense for player to be parent to another class
private:
    float ap{};
    float armor{};
    int energy{};
    int current_energy{};
    const int speed{1};
    // God has forsaken you for `void(Player::*)()`
    std::unordered_map<SDL_Keycode, void(Player::*)()> keyBindings; // function pointer for movement
    std::unordered_map<SDL_Keycode, bool> keyStates;    // which keys are pressed so diagonal and smooth movement is possible
    std::unordered_map<SDL_Keycode,Direction> keyToDirection; // for not going out of bounds
    /*
    1. moved here from `void animation(bool isFlipped,bool isMoving,int frame)`
    because vector was created every time the function was called.
    2. changed it from vector to array, don't need the resize
    3. look up move semantics and {} initialization
    4. left the 2 arrays inside `Player` because you don't seem to
    instantiate more than one
    */
    const std::array<std::string, 7> runSprites { "player", "run1", "run2", "run3", "run4", "run5", "run6" };
    const std::array<std::string, 7> staySprites { "player", "stay", "stay2", "stay" };

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void attack();
    void dash();

public:
    Player(const char *filePath, float atkp, float armoor);
    void update();
    void handleEvent(SDL_Event &event);
    // if you have a getter and setter for that variable with just one line of code,
    // you don't need a getter and setter
    void setEnergy(int enrg) { current_energy = enrg; }
    [[nodiscard]] int getEnergy() const { return energy; }
    void setMaxEnergy(int enrg) { energy = enrg; }
    [[nodiscard]] int getCurrentEnergy() const { return current_energy; }
    void animation(bool isFlipped, bool isMoving, int frame);
};
