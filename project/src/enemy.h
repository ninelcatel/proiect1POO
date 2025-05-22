#pragma once
#include "entity.h"
#include "player.h"

class Enemy : public Entity{   
    private:
        int animFrameCounter,attackFrameCounter;
        bool moving;
        static float STEP_SIZE;                     // }
        std::vector<std::pair<int,int>> path;       // }---> used for A* pathfinding
        size_t currentWaypointIndex = 0;            // } 
    public:
        Enemy(const char *filePath);
        void update(Player& player);
};