#include "assets.h"
void StatusBars::render(Player &player){
    int max_hp=player.getHealth(),current_hp=player.getCurrentHealth(); //health
    int max_energy=player.getEnergy(),current_energy=player.getCurrentEnergy();
    int i=0;
    int window_width=0,window_height=0;
    if(window) SDL_GetWindowSize(window,&window_width,&window_height);
    else {
        std::cerr<<"window is null "<<SDL_GetError();
        return;
        }
    SDL_Rect position;
    position.x=0;
    position.w=window_width*0.020;
    position.h=window_height*0.035;
    position.y=window_height-2*position.h;
    // std::cout<<window_height<<std::endl<<window_width<<std::endl;

    while(i<=current_hp){
        SDL_RenderCopy(renderer,health_bar,nullptr,&position);
        i+=5;
        position.x+=position.w;
    }
    while(i<=max_hp){
        SDL_RenderCopy(renderer,broken_health,nullptr,&position);
        position.x+=position.w;
        i+=5;
    }
    
     position.x=0; // reset position
     position.y+=position.h;
        // position.x=50;
        // position.y=100;
    i=0;
    while(i<=current_energy){
        SDL_RenderCopy(renderer,energy_bar,nullptr,&position);
        i+=5;
        position.x+=position.w;
    }
    while(i<=max_energy){
        SDL_RenderCopy(renderer,broken_energy,nullptr,&position);
        position.x+=position.w;
        i+=5;
    }
}