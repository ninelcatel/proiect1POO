#include "init.h"
#include <algorithm>
#include <map>
#include <vector>
enum class Sprites{
    BOULDER,
    HOLE,
    CHEST,
    POTION,
    NOTHING
};
struct Tiles{
    Sprites sprite;
    std::vector<const char*> filePaths;
};
class Room:public Game{
    private:
        Tiles roomMatrix[5][6];
        SDL_Rect rect;
        SDL_Texture* room; 
    public:
        Room();
        void generateLevel();
        void render() ;
        void setTile(int x, int y,Sprites Sprite);
        Sprites getTile(int x,int y);
};