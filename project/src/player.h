#pragma once
#include <unordered_map>
#include "entity.h"
class Player : public Entity
{
private:
    float ap, armor;
    int energy, current_energy;
    float speed = 0.5f;
    int attack_frame_counter;
    std::unordered_map<SDL_Keycode, void (Player::*)()> key_bindings; // function pointer for movement
    std::unordered_map<SDL_Keycode, bool> key_states;                 // which keys are pressed so diagonal and smooth movement is possible
    std::unordered_map<SDL_Keycode, Direction> key_to_direction;       // for not going out of bounds or into obstacles
    void _moveUp();
    void _moveDown();
    void _moveLeft();
    void _moveRight();
    void _enterRoom();
    bool is_changing_levels;
public:
    Player(const char *filePath);
    virtual void update() override;
    void handleEvent(SDL_Event &event);

    
    // ----- setters -----
    void setEnergy(int energy);
    void setMaxEnergy(int energy);
    void setIsChangingLevel(bool x){
        is_changing_levels=x;
    }
    // ---- getters ----
    int getEnergy();
    int getCurrentEnergy();
    bool getIsChangingLevels() const{
        return is_changing_levels;
    };
    bool checkNearDoor(SDL_Rect doorPosition) const;
    friend std::ostream& operator<<(std::ostream& os,const Player& e){
        os << "The Player has the following attributes: "<<e.getCurrentHealth()<<"/"<<e.getHealth()<<" Health Points "<<std::endl
        <<e.current_energy<<"/"<<e.energy<<" Energy"<<std::endl;
        return os;
    }
};