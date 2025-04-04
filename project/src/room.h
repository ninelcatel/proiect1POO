#include "init.h"
#include <algorithm>
#include <map>
#include <vector>
enum Sprites{
    BOULDER,
    HOLE,
    CHEST,
    POTION,
    DOOR,
    NOTHING
};
struct Tiles{
    Sprites sprite;
    std::vector<const char*> filePaths;
};
struct RoomLayout{
    bool exists; //0 is empty, 1 exists 
    bool isCleared;
    int enemyCount;
    Tiles roomSprites[7][8]; // 5x6 tiles with a border saved for doors only
};
class Room:public Game{
    private:
        RoomLayout layout[4][4];
        SDL_Rect rect;
        SDL_Texture* room; 
    public:
        Room();
        void generateLevel();
        void render() ;
        void setTile(int x, int y,Sprites Sprite);
        Sprites getTile(int x,int y);
        std::vector<std::pair<int,int>> checkForNeighbour(int i,int j);
};