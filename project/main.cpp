#include <iostream>
#include "src/entity.h"
#include "src/player.h"
SDL_Renderer *renderer = nullptr;
SDL_Window *window = nullptr;
int main(int argc, char *argv[])
{
    if (!init(&window, &renderer))
    {
        Entity player(200,200,200,200,renderer,"res/player.png");
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
            }
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);
        }

        SDL_DestroyRenderer(renderer);
        player.render(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
    return 0;
}