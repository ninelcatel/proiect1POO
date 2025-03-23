#include <iostream>
#include "src/entity.h"
#include "src/player.h"
SDL_Renderer *renderer = nullptr;
SDL_Window *window = nullptr;
int main(int argc, char *argv[])
{
    if (!init(&window, &renderer))
    {
        Player player(200,200,200,200,renderer,"res/player.png",10,20);
        bool running = true;
        SDL_Event event;
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
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            player.render(renderer);
            SDL_RenderPresent(renderer);
            
        }

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
    return 0;
}