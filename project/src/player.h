#pragma once
#include <iostream>
#include <unordered_map>
#include "entity.h"
class Player : public Entity
{
private:
    float ap, armor;
    int energy, current_energy;
    float speed = 0.5f;
    int attackFrameCounter;
    std::unordered_map<SDL_Keycode, void (Player::*)()> keyBindings; // function pointer for movement
    std::unordered_map<SDL_Keycode, bool> keyStates;                 // which keys are pressed so diagonal and smooth movement is possible
    std::unordered_map<SDL_Keycode, Direction> keyToDirection;       // for not going out of bounds
    void _moveUp();
    void _moveDown();
    void _moveLeft();
    void _moveRight();
    bool isChangingLevels;
    void _enterRoom();
public:
    Player(const char *filePath, float atkp, float armoor);
    virtual void update() override;
    void handleEvent(SDL_Event &event);
    void setEnergy(int energy);
    int getEnergy();
    void setMaxEnergy(int energy);
    int getCurrentEnergy();
    
    bool checkNearDoor(SDL_Rect doorPosition);
    bool getIsChangingLevels() const{
        return isChangingLevels;
    };
    void setIsChangingLevel(bool x){
        isChangingLevels=x;
    }
    friend std::ostream& operator<<(std::ostream& os,const Player& e){
        os << "The Player has the following attributes: "<<e.getCurrentHealth()<<"/"<<e.getHealth()<<" Health Points "<<std::endl
        <<e.current_energy<<"/"<<e.energy<<" Energy"<<std::endl;
        return os;
    }
};