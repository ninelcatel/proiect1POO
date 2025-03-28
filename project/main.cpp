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
            stats.render(player);
            SDL_RenderPresent(game.getRenderer());
            
        }
        SDL_DestroyRenderer(game.getRenderer());
        SDL_DestroyWindow(game.getWindow());
        SDL_Quit();
    return 0;
}