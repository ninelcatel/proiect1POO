#include "enemy.h"
#include "room.h"

 float Enemy::STEP_SIZE = 2;
const int ANIM_DELAY = 15;
Enemy::Enemy(const char *filePath) : Entity(filePath)
{
    setHealth(30);
    time_since_last_attack=0;
    anim_frame_counter=0;
    attack_frame_counter=0;
    is_enemy = true;
    moving=false;
}
void Enemy::update(Player &player)
{
    
    
     //  resolution scaling
    SDL_Rect position = getPosition();
    position.x = static_cast<int>((position.x * getScaleX()));
    position.y = static_cast<int>((position.y * getScaleY()));
    position.w = static_cast<int>((position.w * getScaleY()));
    position.h = static_cast<int>((position.h * getScaleY()));
    STEP_SIZE=STEP_SIZE*getScaleX();
    setPosition(position.x, position.y);
    SDL_Rect enemyRect = getPosition(); 
    SDL_Rect playerRect = player.getPosition();
    if (frame_counter % 4003 == 0) // take damage every 4 seconds
    {
        setIsHit(false);
        takeDamage();
    }

    if (frame_counter % 60 == 0)
    {   
        time_since_last_attack+=1.35f;
        anim_frame_counter++;
        auto [lx, ly] = player.getRoomCoordinates();
        auto [ex, ey] = this->getIndexesInRoomMatrix();
        auto [px, py] = player.getIndexesInRoomMatrix();

        if (path.empty() || px != path.back().first || py != path.back().second)
        {   
            moving=false;
            // Recalculate path only if needed
            path = aStar(ex, ey, px, py, Room::layout[lx][ly].room_sprites);
            current_waypoint_index = 0; // Start from beginning of new path
        }

        // If there are enough steps in the path, move towards the next position
        if (path.size() > current_waypoint_index)
        {   moving=true;
            if (ex == path[current_waypoint_index].first && ey == path[current_waypoint_index].second)
            {
                current_waypoint_index++;
            }
            // If we have more waypoints, move toward the next one
            if (path.size() > current_waypoint_index)
            {
                auto [nextY, nextX] = path[current_waypoint_index];       // rows are based on Y in pixels...
                int targetX = static_cast<int>(nextX * (Room::getTileSize().first));
                int targetY = static_cast<int>(nextY * (Room::getTileSize().second));

                // Get current position
                SDL_Rect enemyRect = getPosition();

                // Calculate the distance to the target position
                int distX = targetX - enemyRect.x;
                int distY = targetY - enemyRect.y;

                // Determine if we've reached the waypoint
                bool reachedX = abs(distX) <= STEP_SIZE;
                bool reachedY = abs(distY) <= STEP_SIZE;

                // If we've reached this waypoint, move to the next one
                if (reachedX && reachedY)
                {
                    current_waypoint_index++;
                    // Set exact position to avoid drift
                    setPosition(targetX, targetY);
                    std::cout<<enemyRect.x<<" "<<enemyRect.y<<" Player: "<<playerRect.x<<" "<<playerRect.y<<std::endl;
                }
                else
                {
                    // Move horizontally if needed
                    if (!reachedX)
                    {
                        int moveX = distX > 0 ? static_cast<int>(STEP_SIZE) : -static_cast<int>(STEP_SIZE);
                        setPosition(enemyRect.x + moveX, enemyRect.y);
                    }

                    // Get updated position after potential X movement
                    enemyRect = getPosition();

                    // Move vertically if needed
                    if (!reachedY)
                    {   
                        int moveY = distY > 0 ? static_cast<int>(STEP_SIZE) : -static_cast<int>(STEP_SIZE);
                        setPosition(enemyRect.x, enemyRect.y + moveY);
                        
                    }
                }

                // Update animation based on movement direction
                if (distX != 0)
                {
                    // Set direction based on movement
                    setIsFlipped(distX < 0);
                }                
            }
        }
          if(SDL_HasIntersection(&enemyRect,&playerRect)){ // Enemy will attack if the hitboxes reach but the attacking logic is made to make it hard for enemies to deal damage via attacks
            setIsAttacking(true);
            this->attack();
          }
          if(getIsHit() && anim_frame_counter%5==0) animation(moving,anim_frame_counter%3); // Animation for taking damage (pulsating red)
        else if(getIsAttacking() && anim_frame_counter%10==0) { // Animation for attacking
            animation(moving,attack_frame_counter%10);
            attack_frame_counter++;
            if(attack_frame_counter%10==0) setIsAttacking(false);
            }
        else if(anim_frame_counter%ANIM_DELAY==0)animation(moving, (anim_frame_counter) % 7);  // Animation for moving 

        
    }
    
   
}