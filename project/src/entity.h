#pragma once
#include "init.h"

class Entity : public Game,public GameComponent
{
private:
    std::pair<int,int> current_room_position;
    SDL_Rect position;
    SDL_Texture *texture;
    const char *filePath;
    int hp,current_hp;
    bool already_hit=false;
    bool is_flipped=false;
    bool is_attacking=false;
protected:
    float time_since_last_attack=0;
public:
    bool is_enemy;
    Entity(const char *filePath=NULL)
    { 
        texture = loadTexture(filePath, renderer);
        if (!texture)
        {
            std::cerr << "COULDNT LOAD TEXTURE" << std::endl;
        }
        hp=current_hp=50;
    }
    ~Entity()
    {
        SDL_DestroyTexture(texture);
    }
       
    virtual void render() override;
    void animation(bool isMoving, int frame);
    bool isValidMove(Direction dir);
    void takeDamage();
    void attack();
    virtual void update() override; 
    bool checkForObstacles(std::pair<int,int> layoutCoordinates,int i,int j,Direction dir);
    // ---- setters ----
    void setHealth(int hp);
    void setMaxHealth(int hp);
    void setPosition(int x, int y);
    void setRoomCoordinates(std::pair<int,int> coordinates);
    void setIsHit(bool isHit);
    void setIsAttacking(bool attk);
    void changeAppearence(const char *filePath); // change the loaded texture
    void setIsFlipped(bool flip);
    void setSize(int w,int h);
    void setFilePath(const char* filePath);
    // ---- getters ----
    bool getIsHit() const;
    std::pair<int,int> getRoomCoordinates() const;
    bool getIsAttacking() const;
    std::pair<int,int> getIndexesInRoomMatrix() const;
    int getHealth() const;
    int getCurrentHealth() const;
    SDL_Texture* getTexture() const;
    const char* getFilePath() const;
    bool getIsFlipped() const;
    SDL_Rect getPosition() const;
    Entity operator+(const int& hp) {
        Entity result = *this;
        result.current_hp+=hp;
        return result;
    }
    friend std::ostream& operator<<(std::ostream& os,const Entity& e){
        os << "The Entity has the following attributes: "<<e.current_hp<<"/"<<e.hp<<" Health Points "<<std::endl;
        return os;
    }
};
