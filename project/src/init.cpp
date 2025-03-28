
#include "init.h"
SDL_Renderer* Game::renderer=nullptr;
SDL_Window* Game::window=nullptr;
bool Game::initialized=false;
int Game::initial_window_height=720;
int Game::initial_window_width=1024;
int Game::window_height=720;
int Game::window_width=1024;
float Game::scale_x=1;
float Game::scale_y=1;
bool init(SDL_Window **window, SDL_Renderer **renderer)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL INIT ERROR" << SDL_GetError();
        return true;
    }
    *window = SDL_CreateWindow("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 720, SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE);

    if (!*window)
    {
        std::cerr << "SDL COULDNT INITIALIZE WINDOW" << SDL_GetError();
        SDL_Quit();
        return true;
    }
       
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        std::cerr << "SDL COULDNT INITIALIZE RENDERER" << SDL_GetError();
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return true;
    }
        
    SDL_SetRenderDrawColor(*renderer, 0, 0, 0, 255);
    SDL_RenderClear(*renderer);
    SDL_RenderPresent(*renderer);
    SDL_Delay(10);
    return false;
}
SDL_Texture *loadTexture(const char *filePath, SDL_Renderer *renderer)
{
    SDL_Texture *texture = NULL;
    SDL_Surface *loadedSurface = IMG_Load(filePath);
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
    std::cerr << "Failed to initialize PNG support: " << IMG_GetError() << std::endl;
    }
    if (!loadedSurface)
    {
        std::cerr << "img couldn't load " <<filePath<<" "<<SDL_GetError()<<" "<< std::endl;
        return NULL;
    }
    texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
    if(!texture){
        std::cerr<<"texture couldn't load "<<SDL_GetError()<<std::endl;
        return NULL;
    }
    return texture;
}
Game::Game(){
            if(!initialized) {
            
            initialized=true;
            
            init(&window,&renderer);
            
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);
            SDL_ShowWindow(window); // to not shdow blinking at the initialization
            
            SDL_GetWindowSize(window,&window_width,&window_height);
            
            initial_window_width=window_width;
            initial_window_height=window_height;
            std::cout<<"!"<<initial_window_width<<"!"<<window_width;
            // std::cout<<"!"<<initial_window_width<<"!"<<window_width;
            }
        }
SDL_Renderer* Game::getRenderer(){
    return renderer;
}

SDL_Window* Game::getWindow(){
    return window;
}
/*void Game::scaleEntity(SDL_Rect &position)
{   

    // std::cout<<std::endl<<"!!!!!!"<<window_height<<" "<<window_width<<std::endl<<"!!!!!"<<initial_window_height<<" "<<initial_window_width<<std::endl;
        SDL_GetWindowSize(window, &window_width, &window_height);

    float scale_x = static_cast<float>(window_width) / initial_window_width;
    float scale_y = static_cast<float>(window_height) / initial_window_height;

    position.x = static_cast<int>(position.x * scale_x);
    position.y = static_cast<int>(position.y * scale_y);
    
    initial_window_height=window_height;
    initial_window_width=window_width;
}*/
void Game::scale(){        //use x and y via static_cast<int>(rect.x*x) or sth to scale when resziing

    SDL_GetWindowSize(window,&window_width,&window_height);
    
    scale_x = static_cast<float>(window_width) / initial_window_width;
    scale_y = static_cast<float>(window_height) / initial_window_height; 
    
    initial_window_height=window_height;  //for next scaling
    initial_window_width=window_width;
    //
}
 float Game::getScaleX(){
    return scale_x;
}

 float Game::getScaleY(){
    return scale_y;
}