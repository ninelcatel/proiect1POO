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
    NOTHING // player or enemies can go through NOTHING
};
struct Tiles{
    Sprites sprite;
    SDL_Rect base_position; 
    SDL_Rect position;
    SDL_Texture* texture;
    bool is_breakable; // Idea for being able to destroy certain sprites via player attack, was too lazy to implement
    std::vector<std::string> file_paths; // initially i wanted to have multiple texture for a single one but im too lazy to change it so ill let it make my life miserable
};
struct RoomLayout{
    bool exists; //0 is empty, 1 exists 
    int enemy_count;
    std::vector<Enemy*> enemies;
    Tiles room_sprites[7][8]; // 5x6 tiles with a border saved for doors only
};
class Room:public Game{
    private:
        static RoomLayout layout[5][5];
        SDL_Rect rect;
        SDL_Texture* room;
        static int TILE_SIZE_Y;
        static int TILE_SIZE_X;
        static void generateLevel();
    public:
        Room();
        ~Room();
        void render(Player& player) ;
        void loadSpriteTextures();      
        static std::vector<std::pair<int,int>> checkForNeighbour(int i,int j);
        static void spritesScale(float &x, float &y);
        static RoomLayout (&getLayout())[5][5];
        static void setTileSize(int x,int y);
        static std::pair<int,int> getTileSize();
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
