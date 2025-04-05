#pragma once
#include "init.h"
#include <algorithm>
#include <map>
#include "player.h"
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
    SDL_Rect basePosition; 
    SDL_Rect position;
    SDL_Texture* texture;
    std::vector<std::string> filePaths;
};
struct RoomLayout{
    bool exists; //0 is empty, 1 exists 
    bool isCleared;
    int enemyCount;
    Tiles roomSprites[7][8]; // 5x6 tiles with a border saved for doors only
};
class Room:public Game{
    private:
        static RoomLayout layout[5][5];
        SDL_Rect rect;
        SDL_Texture* room;
        
    public:
        Room();
        void generateLevel();
        void render(Player& player) ;
        void setTile(int x, int y,Sprites Sprite);
        Sprites getTile(int x,int y);
        void loadSpriteTextures();      
        std::vector<std::pair<int,int>> checkForNeighbour(int i,int j);
        static void spritesScale(float &x, float &y);
        friend class Player;
};