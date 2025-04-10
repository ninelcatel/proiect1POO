#include "assets.h"
#include <algorithm>
void StatusBars::render(Player &player)
{
    int max_hp = player.getHealth(), current_hp = player.getCurrentHealth(); // health
    int max_energy = player.getEnergy(), current_energy = player.getCurrentEnergy();
    int i = 5;
    if (window)
        SDL_GetWindowSize(window, &window_width, &window_height);
    else
    {
        std::cerr << "window is null " << SDL_GetError();
        return;
    }
    SDL_Rect position;
    position.x = 0;
    position.w = window_width * 0.020;
    position.h = window_height * 0.035;
    position.y = window_height - 2 * position.h;
    // std::cout<<window_height<<std::endl<<window_width<<std::endl;
    while (i <= current_hp)
    {
        SDL_RenderCopy(renderer, health_bar, nullptr, &position);
        i += 5;
        position.x += position.w;
    }
    while (i <= max_hp)
    {
        SDL_RenderCopy(renderer, broken_health, nullptr, &position);
        position.x += position.w;
        i += 5;
    }

    position.x = 0; // reset position
    position.y += position.h;
    // position.x=50;
    // position.y=100;
    i = 5;
    while (i <= current_energy)
    {
        SDL_RenderCopy(renderer, energy_bar, nullptr, &position);
        i += 5;
        position.x += position.w;
    }
    while (i <= max_energy)
    {
        SDL_RenderCopy(renderer, broken_energy, nullptr, &position);
        position.x += position.w;
        i += 5;
    }
}
void Menu::update(SDL_Event &e)
{
  
    auto it=std::find(isHovered.begin(),isHovered.end(),true);
    int index;
    if(it!=isHovered.end()){
        index=std::distance(isHovered.begin(),it);
    }
    if(!e.key.repeat && e.type==SDL_KEYUP){
    switch (e.key.keysym.sym)
    {
    case SDLK_UP:
        isHovered[index]=false;
        isHovered[index==0 ? (isHovered.size()-1) : (index-1)]=true;
        break;
    case SDLK_DOWN:
        isHovered[index]=false;
        isHovered[(index==isHovered.size()-1) ? 0 : index+1]=true;
        break;
    case SDLK_RETURN:
        switch(index){
            case 0:
                setGameState(GameState::GAME);
                break;
            case 1:
                SDL_SetWindowSize(window,1920,1080);        // call the scaling in the player update func
                break;
            case 2:
                for (auto &t : text)
                {
                    SDL_DestroyTexture(t.first);
                }
                TTF_CloseFont(font);
                TTF_Quit();
                SDL_Quit();
                break;
            default:
                break;
        }
        break;
    default:
        break;
    }
    }
    for(int i=0;i<3;++i){
        if(isHovered[i]==true){
            SDL_SetTextureColorMod(text[i].first,255,255,255);
        }
        else{
            SDL_SetTextureColorMod(text[i].first,245,40,145);
        }
    }
}
void Menu::init_font(){
    if (TTF_Init() == -1)
    {
        std::cerr << "failed to initialize font!: " << TTF_GetError() << std::endl;
        return;
    }
    font = TTF_OpenFont("res/font/Pixeled.ttf", 40);
    if (!font)
    {
        std::cerr << "failed to open font!: " << TTF_GetError() << std::endl;
        return;
    }
    SDL_Color color = {255, 255, 255};
    SDL_Rect rect;
    int width, height;
    SDL_GetWindowSize(window, &width, &height);

    int yAxis = rect.y;
    for (int i = 0; i < textContent.size(); ++i)
    {
        if (TTF_SizeText(font, textContent[i].c_str(), &rect.w, &rect.h) != 0)
        {
            std::cerr << "Failed to get text size: " << TTF_GetError() << std::endl;
        }
        rect.x = (width - rect.w) / 2;
        rect.y = (height - rect.h) / 2 + i * rect.h;
        SDL_Surface *surface = TTF_RenderText_Solid(font, textContent[i].c_str(), color);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        text.push_back({texture, rect});
        if (!text[i].first)
        {
            std::cerr << "failed to create textContent texture! " << SDL_GetError() << " " << TTF_GetError() << std::endl;
            return;
        }
        SDL_FreeSurface(surface); // Not freeing causes memory leaks
    }
}
void Menu::render(){
    SDL_Surface *background=IMG_Load("res/MENU_WALLPAPER.png");
    SDL_Texture *backgroundTexture;
    backgroundTexture=SDL_CreateTextureFromSurface(renderer,background);
    SDL_FreeSurface(background);
    SDL_Rect backgroundRect;
    backgroundRect={0,0,1024,720};
    SDL_RenderCopy(renderer,backgroundTexture,NULL,&backgroundRect);
    for (auto &t : text)
    {
        SDL_RenderCopy(renderer, t.first, NULL, &t.second);
    }
}
Menu::Menu()
{
    textContent = {"PLAY", "CHANGE RESOLUTION", "EXIT"};
    isHovered = std::vector<bool>(3, false);
    isHovered[0]=true;
    init_font();
}
Menu::~Menu()
{
    for (auto &t : text)
    {
        SDL_DestroyTexture(t.first);
    }
    TTF_CloseFont(font);
    TTF_Quit();
}
