#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>    
#include <chrono>
#include <vector>
enum Direction{UP,DOWN,LEFT,RIGHT,NONE};
struct FireZone {
        SDL_Rect zone;         
        bool is_active;           
        std::chrono::steady_clock::time_point activation_time; // When the fire zone was activated
        double how_long; //how much does the zone will mainly be 1 sec or sth
        bool is_enemy;
    };
enum class GameState{MENU,GAME,PAUSE};
bool init(SDL_Window **window, SDL_Renderer **renderer);
SDL_Texture* loadTexture(const char* filePath, SDL_Renderer* renderer);
class Game{
    private:
        static GameState State;
        static bool initialized;; //track if initialized for window resizing
        static float scale_x, scale_y;
        static std::vector<FireZone>* fire_zones; // Main logic for making player / enemies take damage
   protected: // Protected because each child has the logic of upscaling/downscaling and frame_counters.

        static int window_width,window_height;
        static int initial_window_width,initial_window_height; 
        // used for resizing;
        static int frame_counter;
        static SDL_Renderer* renderer;
        static SDL_Window* window;
    public:
        Game();
        
        
        void scale();
        void scaleEntity(SDL_Rect &position);
        static void pushFireZone(SDL_Rect rect,double time,bool is_enemy);
        // ---- setters -----
        static void setGameState(GameState state);
        // ---- getters -----
        static float getScaleX() ;
        static float getScaleY() ;
        static std::vector<FireZone>& getFireZones() ;
        static GameState getGameState() ;
        SDL_Renderer* getRenderer() const;
        SDL_Window* getWindow() const; 

        
};
class GameComponent {
    public:
        virtual ~GameComponent() = default;
        virtual void update() = 0;
        virtual void render() = 0;

};