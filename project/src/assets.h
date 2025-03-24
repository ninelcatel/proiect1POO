#include "init.h"
#include "player.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
class StatusBars{
    private:
        SDL_Texture* health_bar,*energy_bar,*broken_health,*broken_energy;
        SDL_Renderer* renderer;
        SDL_Window* window;
    public:
        StatusBars(SDL_Renderer * renderer,SDL_Window *window){
            this->renderer=renderer;
            this->window=window;
            health_bar=loadTexture("res/heart/Heart.png",renderer);
            broken_health=loadTexture("res/heart/brokenHeart.png",renderer);
            energy_bar=loadTexture("res/heart/Energy.png",renderer);
            broken_energy=loadTexture("res/heart/brokenEnergy.png",renderer);
        }
        void render(Player &player);
};