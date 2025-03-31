#pragma once
#include "entity.h"
#include <SDL2/SDL.h>

class Enemy : public Entity{
    public:
        Enemy(const char *filePath);
};