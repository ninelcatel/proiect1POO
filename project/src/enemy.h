#pragma once
#include "entity.h"
#include "player.h"
#include <SDL2/SDL.h>

class Enemy : public Entity{   
    private:
        int animFrameCounter,attackFrameCounter;
        bool moving;
        static float STEP_SIZE;
        std::vector<std::pair<int,int>> path;
        size_t currentWaypointIndex = 0;
    public:
        Enemy(const char *filePath);
        void update(Player& player);
};