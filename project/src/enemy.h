#pragma once
#include "entity.h"
#include "player.h"

class Enemy : public Entity{   
    private:
        int anim_frame_counter,attack_frame_counter;
        bool moving;
        static float STEP_SIZE;                     // }
        std::vector<std::pair<int,int>> path;       // }---> used for A* pathfinding
        size_t current_waypoint_index = 0;            // } 
    public:
        Enemy(const char *filePath);
        void update(Player& player);
};