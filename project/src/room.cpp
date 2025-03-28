#include "room.h"
Room::Room(){
    room=loadTexture("res/ROOM/MAIN_ROOM.png",renderer);
    rect={0,0,1024,720};
};
void Room::render(){
    (window) ? SDL_GetWindowSize(window,&window_width,&window_height) : SDL_Quit();
    rect.w=window_width;
    rect.h=window_height;
    SDL_RenderCopy(renderer,room,nullptr,&rect);
}