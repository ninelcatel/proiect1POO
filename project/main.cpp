#include <iostream>
#include "src/assets.h"
#include "src/player.h"
#include "src/room.h"
#include "src/enemy.h"
SDL_Renderer *renderer = nullptr;
SDL_Window *window = nullptr;

int main(int argc, char *argv[])
{
        std::srand(std::time(nullptr));
        Game game;  
        Player player("res/PLAYER/player.png",10,20);
        std::vector<Entity*> entites;
        entites.push_back(new Enemy("res/ENEMY/SKELETON/FLIPPED/SKELETON.png"));
        entites[0]->setPosition(500,350);
        entites[0]->setSize(102,108);
        entites[0]->pushFireZone(entites[0]->getPosition(),1000,entites[0]->isEnemy);
        StatusBars stats;
        Room room;
        SDL_Event event;
        bool running = true;
        
        while (running)
        {   
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    running = false;
                }
                player.handleEvent(event);
            }
            // int mouseX, mouseY;
            // SDL_GetMouseState(&mouseX, &mouseY);
            // std::cout<<"Mouse X:"<<mouseX<<" MouseY: "<<mouseY<<std::endl;
             player.update();
            
            entites[0]->takeDamage();
            SDL_SetRenderDrawColor(game.getRenderer(), 0, 0, 0, 255);
            SDL_RenderClear(game.getRenderer());
            
            // SDL_Rect pos=player.getPosition();
            // SDL_RenderFillRect(game.getRenderer(),&pos);
            room.render(player);
            player.render();
            // pos=entites[0]->getPosition();
            // SDL_RenderFillRect(game.getRenderer(),&pos); for visualizing hitboxes
            entites[0]->render();
            stats.render(player);
            
            SDL_RenderPresent(game.getRenderer());
            
        }
        SDL_DestroyRenderer(game.getRenderer());
        SDL_DestroyWindow(game.getWindow());
        SDL_Quit();
    return 0;
}