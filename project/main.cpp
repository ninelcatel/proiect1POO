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
        StatusBars stats;
        Room room;
        Menu menu;
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
                if(game.getGameState()==GameState::GAME)  player.handleEvent(event);
                if(game.getGameState()==GameState::MENU) menu.update(event);
                if(game.getGameState()==GameState::PAUSE && event.key.keysym.sym==SDLK_RETURN && event.type==SDL_KEYDOWN ) game.setGameState(GameState::GAME); 
            }
            switch(game.getGameState()){
            case GameState::GAME:
                player.update();
                SDL_SetRenderDrawColor(game.getRenderer(), 0, 0, 0, 255);
                SDL_RenderClear(game.getRenderer());
                room.render(player);
                player.render();
                stats.render(player);
                break;
            case GameState::MENU:
                
                SDL_SetRenderDrawColor(game.getRenderer(), 0, 0, 0, 255);
                SDL_RenderClear(game.getRenderer());
                menu.render();
                break;
            case GameState::PAUSE:

                TTF_Font* font;
                font=TTF_OpenFont("res/font/Pixeled.ttf", 50);
                SDL_Color color ;
                color={255, 255, 255};
                SDL_Rect rect;
                int width, height;
                SDL_GetWindowSize(game.getWindow(), &width, &height);
                SDL_Surface * textSurface;
                textSurface=TTF_RenderText_Solid(font,"RESUME",color);
                SDL_Texture * textTexture;
                textTexture=SDL_CreateTextureFromSurface(game.getRenderer(),textSurface);
                SDL_FreeSurface(textSurface);                
                SDL_Rect textRect;
                TTF_SizeText(font, "RESUME", &textRect.w, &textRect.h);
                
                textRect.x=(width-textRect.w)/2;
                textRect.y=(height-textRect.h)/2;
                TTF_CloseFont(font);

                SDL_RenderClear(game.getRenderer());
                room.render(player);
                player.render();
                stats.render(player);
                SDL_SetRenderDrawBlendMode(game.getRenderer(), SDL_BLENDMODE_BLEND);

                SDL_SetRenderDrawColor(game.getRenderer(), 180, 180, 180, 50);
                SDL_Rect slightBlur;
                
                slightBlur={0,0,1920,1080};
                SDL_RenderFillRect(game.getRenderer(),&slightBlur);
                SDL_RenderCopy(game.getRenderer(),textTexture,nullptr,&textRect);
                
                SDL_DestroyTexture(textTexture);
                break;
            default:
                break;
            }
            SDL_RenderPresent(game.getRenderer());
            
        }
        SDL_DestroyRenderer(game.getRenderer());
        SDL_DestroyWindow(game.getWindow());
        SDL_Quit();
    return 0;
}