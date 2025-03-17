#include "entity.h"
#include <SDL2/SDL.h>

class Player : public Entity{
    Player(int x, int y); // coordinates
    public:
        void HandleEvent();
        void Shoot();
};