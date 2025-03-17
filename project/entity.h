#include <SDL2/SDL.h>
class Entity{
    Entity();
    ~Entity();
    protected:
        SDL_Rect position;
        int hp;
    public:
        int getHealth();
        SDL_Rect getPosition();
        void setHealth(int hp);
        void setPosition(int x,int y);    
};