#include "init.h"
#include "player.h"
#include <SDL2/SDL_ttf.h>
class StatusBars : public Game
{
    private:
        SDL_Texture* health_bar,
        *energy_bar,
        *broken_health, // Broken refers to empty sprtie for the respective bar, for example if player's hp is 30/40 6 hearts will be full and 2 will be empty
        *broken_energy; 
        public:
        StatusBars(){ // Loading the texture for the status bars
            health_bar=loadTexture("res/heart/Heart.png",renderer);
            broken_health=loadTexture("res/heart/brokenHeart.png",renderer);
            energy_bar=loadTexture("res/heart/Energy.png",renderer);
            broken_energy=loadTexture("res/heart/brokenEnergy.png",renderer);
        }
        void render(Player &player);
};
class Menu : public Game{
    private:
        std::vector<std::pair<SDL_Texture *,SDL_Rect>> text; // Vector used for rendering the text, the pair.first is made from TTF via textContent elements
        std::vector<std::string> text_content; 
        std::vector<bool> is_hovered; // Used to highlight and acces current selection
        TTF_Font* font;
        bool is_running=true;;
    public:
        void handleEvent(SDL_Event& e); // Handles going through menu tokens and accesing them
        void render();
        void initFont();
        Menu();
        bool getIsRunning() const{
            return is_running;
        }
        ~Menu();
};
