#pragma once
#include "init.h"
#include <algorithm>
#include <map>
#include "player.h"
#include "enemy.h"
#include <vector>
#include <queue>
#include <tuple>
#include <climits>

enum Sprites{
    BOULDER,
    BARREL,
    HOLE,
    CHEST,
    VASE,
    SKULL,
    POTION,
    DOOR,
    NOTHING
};
struct Tiles{
    Sprites sprite;
    SDL_Rect basePosition; 
    SDL_Rect position;
    SDL_Texture* texture;
    bool isBreakable;
    std::vector<std::string> filePaths; // initially i wanted to have multiple texture for a single one but im too lazy to change it so ill let it make my life miserable
};
struct RoomLayout{
    bool exists; //0 is empty, 1 exists 
    bool isCleared;
    int enemyCount;
    std::vector<Enemy*> enemies;
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
        static RoomLayout (&getLayout())[5][5];
        friend class Player;
        friend class Enemy;
};

struct Node {
    int x, y;
    int g, f;  // g = cost from start, f = g + heuristic
    bool operator<(const Node& other) const {
        return f > other.f; // priority queue wants smallest f
    }
};
int heuristic(int x1, int y1, int x2, int y2);
std::vector<std::pair<int, int>> aStar(int startX, int startY, int endX, int endY, const Tiles grid[7][8]);      
