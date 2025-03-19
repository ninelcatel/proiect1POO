#pragma once
#include "entity.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
class Player : public Entity{
    
    private:
        
            float ap,armor; // ap = attack power
            SDL_Texture* texture;
    public:
        void HandleEvent(); // move? inventory? etc
        void Shoot();
};