#include "init.h"
#include "player.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
class StatusBars : public Game
{
    private:
        SDL_Texture* health_bar,
        *energy_bar,
        *broken_health,
        *broken_energy;
        public:
        StatusBars(){
            health_bar=loadTexture("res/heart/Heart.png",renderer);
            broken_health=loadTexture("res/heart/brokenHeart.png",renderer);
            energy_bar=loadTexture("res/heart/Energy.png",renderer);
            broken_energy=loadTexture("res/heart/brokenEnergy.png",renderer);
        }
        void render(Player &player);
};
class Menu : public Game{
    private:
        
};