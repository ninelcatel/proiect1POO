#include <iostream>
#include "src/assets.h"
#include "src/player.h"
#include "src/room.h"
SDL_Renderer *renderer = nullptr;
SDL_Window *window = nullptr;

int main(int argc, char *argv[])
{
        Game game;  
        Player player("res/PLAYER/player.png",10,20);
        std::vector<Entity*> entites;
        entites.push_back(new Entity("res/ENEMY/SKELETON/FLIPPED/SKELETON.png"));
        entites[0]->setPosition(500,350);
        entites[0]->setSize(200,200);
        Game::pushFireZone(entites[0]->getPosition(),5);
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
            player.update();
            SDL_SetRenderDrawColor(game.getRenderer(), 0, 0, 0, 255);
            SDL_RenderClear(game.getRenderer());
            room.render();
            player.render();
            entites[0]->render();
            stats.render(player);
            SDL_RenderPresent(game.getRenderer());
            
        }
        SDL_DestroyRenderer(game.getRenderer());
        SDL_DestroyWindow(game.getWindow());
        SDL_Quit();
    return 0;
}