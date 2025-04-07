#pragma once
#include "init.h"
#include <SDL2/SDL.h>
#include <iostream>

class Entity : public Game
{
private:
    std::pair<int,int> currentRoom_Position;
    SDL_Rect position;
    SDL_Texture *texture;
    const char *filePath;
    int hp,current_hp;
    bool alreadyHit=false;
    bool isFlipped=false;
    bool isAttacking=false;
protected:
    int timeSinceLastAttack=500;
public:
    bool isEnemy;
    Entity(const char *filePath=NULL)
    { 
        texture = loadTexture(filePath, renderer);
        if (!texture)
        {
            std::cerr << "COULDNT LOAD TEXTURE" << std::endl;
        }
        hp=current_hp=50;
    } // coordinates + where to render and image loaded;
    ~Entity()
    {
        SDL_DestroyTexture(texture);
    }
    int getHealth();
    int getCurrentHealth();
    SDL_Texture* getTexture();
    const char* getFilePath();
    bool getIsFlipped();
    SDL_Rect getPosition();
    SDL_Renderer* getRenderer();
    void setHealth(int hp);
    void setMaxHealth(int hp);
    void setPosition(int x, int y);
    void changeAppearence(const char *filePath); // change the loaded texture
    SDL_Texture* flipTexture(SDL_Texture* original);
    void render();
    void setFilePath(const char* filePath);
    void animation(bool isMoving, int frame);
    void setIsFlipped(bool flip);
    void setSize(int w,int h);
    bool isValidMove(Direction dir);
    void takeDamage();
    void attack();
    void update();
    bool getIsHit();
    std::pair<int,int> getRoomCoordinates();
    void setRoomCoordinates(std::pair<int,int> coordinates);
    void setIsHit(bool isHit);
    bool getIsAttacking();
    void setIsAttacking(bool attk);
    bool checkForObstacles(std::pair<int,int> layoutCoordinates,int i,int j,Direction dir);
    std::pair<int,int> getIndexesInRoomMatrix();
};
