#include "enemy.h"
#include "room.h"

const int STEP_SIZE = 2;
const int TILE_SIZE = 125;
const int ANIM_DELAY = 15;
Enemy::Enemy(const char *filePath) : Entity(filePath)
{
    timeSinceLastAttack=0;
    animFrameCounter=0;
    attackFrameCounter=0;
    isEnemy = true;
    moving=false;
}
void Enemy::update(Player &player)
{
    SDL_Rect playerRect = player.getPosition();
    SDL_Rect enemyRect = getPosition();
    
    if (frameCounter % 4003 == 0) // take damage every 4 seconds
    {
        setIsHit(false);
        takeDamage();
    }

    if (frameCounter % 60 == 0)
    {   
        timeSinceLastAttack+=1.35f;
        animFrameCounter++;
        auto [lx, ly] = player.getRoomCoordinates();
        auto [ex, ey] = this->getIndexesInRoomMatrix();
        auto [px, py] = player.getIndexesInRoomMatrix();

        if (path.empty() || px != path.back().first || py != path.back().second)
        {   
            moving=false;
            // Recalculate path only if needed
            path = aStar(ex, ey, px, py, Room::layout[lx][ly].roomSprites);
            currentWaypointIndex = 0; // Start from beginning of new path
        }

        // If there are enough steps in the path, move towards the next position
        if (path.size() > currentWaypointIndex)
        {   moving=true;
            if (ex == path[currentWaypointIndex].first && ey == path[currentWaypointIndex].second)
            {
                currentWaypointIndex++;
            }
            // If we have more waypoints, move toward the next one
            if (path.size() > currentWaypointIndex)
            {
                auto [nextY, nextX] = path[currentWaypointIndex];       // rows are based on Y in pixels...
                
                int targetX = nextX * (TILE_SIZE);
                int targetY = nextY * (TILE_SIZE-25);

                // Get current position
                SDL_Rect enemyRect = getPosition();

                // Calculate the distance to the target position
                int distX = targetX - enemyRect.x;
                int distY = targetY - enemyRect.y;

                // Determine if we've reached the waypoint (within STEP_SIZE)
                bool reachedX = abs(distX) <= STEP_SIZE;
                bool reachedY = abs(distY) <= STEP_SIZE;

                // If we've reached this waypoint, move to the next one
                if (reachedX && reachedY)
                {
                    currentWaypointIndex++;
                    // Set exact position to avoid drift
                    setPosition(targetX, targetY);
                    std::cout<<enemyRect.x<<" "<<enemyRect.y<<" Player: "<<playerRect.x<<" "<<playerRect.y<<std::endl;
                }
                else
                {
                    // Move horizontally if needed
                    if (!reachedX)
                    {
                        int moveX = distX > 0 ? STEP_SIZE : -STEP_SIZE;
                        setPosition(enemyRect.x + moveX, enemyRect.y);
                    }

                    // Get updated position after potential X movement
                    enemyRect = getPosition();

                    // Move vertically if needed
                    if (!reachedY)
                    {   
                        int moveY = distY > 0 ? STEP_SIZE : -STEP_SIZE;
                        setPosition(enemyRect.x, enemyRect.y + moveY);
                        
                    }
                }

                // // Update animation based on movement direction
                if (distX != 0)
                {
                    // Set direction based on movement
                    setIsFlipped(distX < 0);
                }                
            }
        }
          if(SDL_HasIntersection(&enemyRect,&playerRect)){
            setIsAttacking(true);
            this->attack();
          }
          if(getIsHit() && animFrameCounter%5==0) animation(moving,animFrameCounter%3);
        else if(getIsAttacking() && animFrameCounter%10==0) {
            animation(moving,attackFrameCounter%10);
            attackFrameCounter++;
            if(attackFrameCounter%10==0) setIsAttacking(false);
            }
        else if(animFrameCounter%ANIM_DELAY==0)animation(moving, (animFrameCounter) % 7); 

        
    }
    // In render method, add debugging visualizations
for (auto [x, y] : path) {
    SDL_Rect debugRect = {
        static_cast<int>(x * TILE_SIZE * getScaleX()),
        static_cast<int>(y * TILE_SIZE * getScaleY()),
        static_cast<int>(10 * getScaleX()),
        static_cast<int>(10 * getScaleY())
    };
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &debugRect);
}
    // Adjusting position to match the resolution scaling
    SDL_Rect position = getPosition();
    position.x = static_cast<int>((position.x * getScaleX()));
    position.y = static_cast<int>((position.y * getScaleY()));
    position.w = static_cast<int>((position.w * getScaleY()));
    position.h = static_cast<int>((position.h * getScaleY()));
    setPosition(position.x, position.y);
}