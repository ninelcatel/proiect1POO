#include "player.h"
#include "room.h"
#include <vector>
#include <SDL2/SDL_ttf.h>
#include <cmath>
const int animDelay = 51; // delay in ms
const int moveDelay = 11;
const int stayingDelay = 151;
const int attackDelay = 51;
const int getDamagedDelay = 5000;
static int animFrameCounter = 0;
Player::Player(const char *filePath, float atkp, float armoor)
    : Entity(filePath)
{
    // SDL_GetWindowSize(window, &initial_window_width, &initial_window_height);
    setRoomCoordinates({2, 2});
    setPosition(175, 330);
    setSize(115,70);
    isEnemy = false;
    ap = atkp;
    armor = armoor;
    setHealth(20);
    setMaxHealth(30);
    energy = 40;
    current_energy = 20;
    keyBindings[SDLK_w] = &Player::_moveUp;
    keyBindings[SDLK_s] = &Player::_moveDown;
    keyBindings[SDLK_a] = &Player::_moveLeft;
    keyBindings[SDLK_d] = &Player::_moveRight;
    keyBindings[SDLK_SPACE] = &Player::_enterRoom;
    keyBindings[SDLK_f] = &Entity::attack;

    keyStates[SDLK_w] = false;
    keyStates[SDLK_s] = false;
    keyStates[SDLK_a] = false;
    keyStates[SDLK_d] = false;
    keyStates[SDLK_f] = false;
    keyStates[SDLK_SPACE] = false;

    keyToDirection[SDLK_w] = UP;
    keyToDirection[SDLK_s] = DOWN;
    keyToDirection[SDLK_a] = LEFT;
    keyToDirection[SDLK_d] = RIGHT;
    keyToDirection[SDLK_f] = NONE;
    keyToDirection[SDLK_SPACE] = NONE;
}

void Player::handleEvent(SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN)
    {   

        if(event.key.keysym.sym==SDLK_ESCAPE){
            setGameState(GameState::PAUSE);
            for(auto it:keyStates)
                keyStates[it.first]=false;
         
        }
        if(event.key.keysym.sym==SDLK_SPACE && !event.key.repeat){
            keyStates[event.key.keysym.sym] = true;
            
    // auto [n,m]=getRoomCoordinates();
    // std::cout<<n<<" "<<m<<std::endl;
        }
        else{
        keyStates[event.key.keysym.sym] = true;
        if (event.key.keysym.sym == SDLK_f && !getIsAttacking() && attackFrameCounter % 5 == 0 && getCurrentEnergy()>0)
        {
            setIsAttacking(true);
            attackFrameCounter = 0;
        }
         }
        if (getIsFlipped() == false && event.key.keysym.sym == SDLK_a)
            setIsFlipped(true);
        else if (getIsFlipped() == true && event.key.keysym.sym == SDLK_d)
            setIsFlipped(false);
           
    }
    else if (event.type == SDL_KEYUP)
    {
        keyStates[event.key.keysym.sym] = false;
    }
    else if (event.type == SDL_WINDOWEVENT)
    {
        if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
        {
            SDL_Rect pos = getPosition();
            // scaleEntity(pos);
            scale();
            pos.x = static_cast<int>(pos.x * getScaleX());
            pos.y = static_cast<int>(pos.y * getScaleY());
            
            setPosition(pos.x, pos.y);
            speed = 0.75f * getScaleY();        //MUST BE Y, OTHERWISE SPEED WONT BE HIGH ENOUGH TO MAKE THE TRUNC WHEN CASTING

            Room::setTileSize(static_cast<int>(getScaleX()*Room::getTileSize().first),static_cast<int>(getScaleY()*Room::getTileSize().second)); //update tile size for enemy pathfinding
            std::cout<<Room::getTileSize().first<<" "<<Room::getTileSize().second<<" "<<std::endl;
            /*SDL_GetWindowSize(window, &window_width, &window_height);
            float scale_x = static_cast<float>(window_width) / initial_window_width;
            float scale_y = static_cast<float>(window_height) / initial_window_height;

            SDL_Rect current_position = getPosition();

            setPosition(
                static_cast<int>(current_position.x * scale_x),
                static_cast<int>(current_position.y * scale_y)
            );
            initial_window_width=window_width;
            initial_window_height=window_height;*/
        }
    }
}

void Player::update()
{
    // std::cerr<<getPosition().x<<" "<<getPosition().y<<std::endl;
    bool moving = false;
    ;
    frameCounter++;
    animFrameCounter++;

    if (frameCounter % 11 == 0)
    {    
        if(frameCounter%22000==0){ //Health regeneration every 22k frames ig
            setHealth(getHealth()>getCurrentHealth() ? getCurrentHealth()+5 : getHealth());
                // Player temp=*this;
            // this->setHealth(temp.getHealth()>temp.getCurrentHealth() ? (temp+5).getCurrentHealth() : temp.getHealth()); // sat and looked at this for 10 seconds then started laughing 
            //                                                                                                             // why do i have to implement + overload man
        
        }
        timeSinceLastAttack++;
        if (frameCounter % 3003 == 0)
        {   setEnergy(getCurrentEnergy()<getEnergy() ? getCurrentEnergy()+5 : getEnergy());
            setIsHit(false);
            takeDamage();
        }
        attackFrameCounter++;
        if (getIsAttacking())
        {
            if (attackFrameCounter % attackDelay == 0)
            {
                int currentFrame = (attackFrameCounter / attackDelay) % 4;
                if (attackFrameCounter % attackDelay == 0)
                    animation(false, currentFrame);

                // if last frame is reached, stop attack animation
                if (currentFrame == 3)
                {
                    attackFrameCounter = 0;
                    if (keyStates[SDLK_f] == false)
                        setIsAttacking(false); // setting keyStates to false makes the animation smoother and lets the player attack whilst moving
                    setEnergy(getCurrentEnergy()-5);
                }
            }
        }
        else
            attackFrameCounter = 0;

        for (const auto &pair : keyBindings)
        {
            if (keyStates[pair.first])
            {
                moving = keyToDirection[pair.first] != NONE;
                if (isValidMove(keyToDirection[pair.first]))
                {   
                    if(pair.first==SDLK_f && getCurrentEnergy()!=0){
                        (this->*pair.second)();
                        
                    }
                    else (this->*pair.second)();
                }
                // std::cerr<<getIsAttacking()<<std::endl;
                // action = keyToDirection[pair.first]==NONE;
            }
        }
        if (getIsHit())
        {
            if ((animFrameCounter % 32) == 0)
            {
                animation(false, animFrameCounter % 3);
            }
        }
        else
        {
            int frameModulo = moving ? 7 : 4; // 7 frames for moving, 4 for staying
            if ((animFrameCounter % (moving ? animDelay : stayingDelay)) == 0)
            {
                animation(moving, animFrameCounter % frameModulo);
            }
        }
    }
}
void Player::_moveUp()
{
    const SDL_Rect rect = getPosition();
    setPosition(rect.x, static_cast<int>(rect.y - speed));
}

void Player::_moveDown()
{
    const SDL_Rect rect = getPosition();
    setPosition(rect.x, static_cast<int>(rect.y + 2 * speed));
}

void Player::_moveLeft()
{
    const SDL_Rect rect = getPosition();
    setPosition(static_cast<int>(rect.x - speed), rect.y);
}

void Player::_moveRight()
{
    const SDL_Rect rect = getPosition();
    setPosition(static_cast<int>(rect.x + 2 * speed), rect.y);
}
void Player::setEnergy(int eng)
{ // eng=energy;
    current_energy = eng;
}
void Player::setMaxEnergy(int eng)
{
    energy = eng;
}
int Player::getEnergy()
{
    return energy;
}
int Player::getCurrentEnergy()
{
    return current_energy;
}

void Player::_enterRoom(){
    
    auto [x,y]=getRoomCoordinates();
    auto helper=Room::layout[x][y].roomSprites;
    scale();
    float scaledX,scaledY;
    Room::spritesScale(scaledX,scaledY);
    for(int i=0;i<7;i++){
        for(int j=0;j<8;j++){
            if(helper[i][j].sprite==DOOR){
                if(checkNearDoor(helper[i][j].position)){
                    switch(i){  //hardcoding the direction xd, love pink monster 
                        case 0:
                            setRoomCoordinates({x-1,y});
                            setPosition(static_cast<int>(500*scaledX),static_cast<int>(450*scaledY));
                            break;      
                        case 6:
                            setRoomCoordinates({x+1,y});
                            setPosition(static_cast<int>(500*scaledX),static_cast<int>(200*scaledY));
                            break;
                        case 3:
                            setRoomCoordinates({x,j==0 ? y-1 : y+1});
                            j!=0 ? setPosition(static_cast<int>(200*scaledX),static_cast<int>(300*scaledY))
                            : setPosition(static_cast<int>(700*scaledX),static_cast<int>(300*scaledY));                         
                            break;
                        default:
                            break;
                    }

                }
            }
            else if(helper[i][j].sprite==HOLE){ //for changing levels
                    if(checkNearDoor(helper[i][j].position)){
                        setIsChangingLevel(true);
                        SDL_Delay(100);
                        setRoomCoordinates(std::make_pair(2,2));
                    }
            }
        }
    }
}
bool Player::checkNearDoor(SDL_Rect doorPosition){
    SDL_Rect playerPosition=getPosition();
    float x,y;
    Room::spritesScale(x,y);
    doorPosition.h=static_cast<int>(50*y);
    return SDL_HasIntersection(&playerPosition,&doorPosition);
}