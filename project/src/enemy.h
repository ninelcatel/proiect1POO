#pragma once
#include "entity.h"
#include "player.h"
#include <SDL2/SDL.h>

class Enemy : public Entity{
    public:
        Enemy(const char *filePath);
        void update(Player& player);
};