#pragma once

#include "init.h"
#include "player.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class StatusBars : public Game
{
    private:
        SDL_Texture
            *health_bar{nullptr},
            *energy_bar{nullptr},
            *broken_health{nullptr},
            *broken_energy{nullptr};
        public:
        StatusBars(){
            // if loadTexture can throw, handle that; if not, mark this as noexcept
            // noexcept and const correctness are both good habits
            health_bar=loadTexture("resources/heart/Heart.png",renderer);
            broken_health=loadTexture("resources/heart/brokenHeart.png",renderer);
            energy_bar=loadTexture("resources/heart/Energy.png",renderer);
            broken_energy=loadTexture("resources/heart/brokenEnergy.png",renderer);
        }
        void render(Player &player);
};
class Menu : public Game{

};