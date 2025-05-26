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
static int anim_frame_counter = 0;
Player::Player(const char *filePath)
    : Entity(filePath)
{
    // SDL_GetWindowSize(window, &initial_window_width, &initial_window_height);
    setRoomCoordinates({2, 2});
    setPosition(175, 330);
    setSize(115,70);
    is_enemy = false;
    setHealth(20);
    setMaxHealth(30);
    energy = 40;
    current_energy = 20;
    key_bindings[SDLK_w] = &Player::_moveUp;
    key_bindings[SDLK_s] = &Player::_moveDown;
    key_bindings[SDLK_a] = &Player::_moveLeft;
    key_bindings[SDLK_d] = &Player::_moveRight;
    key_bindings[SDLK_SPACE] = &Player::_enterRoom;
    key_bindings[SDLK_f] = &Entity::attack;

    key_states[SDLK_w] = false;
    key_states[SDLK_s] = false;
    key_states[SDLK_a] = false;
    key_states[SDLK_d] = false;
    key_states[SDLK_f] = false;
    key_states[SDLK_SPACE] = false;

    key_to_direction[SDLK_w] = UP;
    key_to_direction[SDLK_s] = DOWN;
    key_to_direction[SDLK_a] = LEFT;
    key_to_direction[SDLK_d] = RIGHT;
    key_to_direction[SDLK_f] = NONE;
    key_to_direction[SDLK_SPACE] = NONE;
}

void Player::handleEvent(SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN)
    {   

        if(event.key.keysym.sym==SDLK_ESCAPE){ //for pausing the game
            setGameState(GameState::PAUSE);
            for(auto it:key_states)
                key_states[it.first]=false;
         
        }
        if(event.key.keysym.sym==SDLK_SPACE && !event.key.repeat){ //changing rooms or levels
            key_states[event.key.keysym.sym] = true;
            
        }
        else{
        key_states[event.key.keysym.sym] = true;
        // logic for attacking only once per whole attack motion ( used to be pushing too many elements into the fireZones vector instakilling anything)
        if (event.key.keysym.sym == SDLK_f && !getIsAttacking() && attack_frame_counter % 5 == 0 && getCurrentEnergy()>0) 
        {
            setIsAttacking(true);
            attack_frame_counter = 0;
        }
         }
        if (getIsFlipped() == false && event.key.keysym.sym == SDLK_a) // flips the character in function of the direction
            setIsFlipped(true);
        else if (getIsFlipped() == true && event.key.keysym.sym == SDLK_d)
            setIsFlipped(false);
           
    }
    else if (event.type == SDL_KEYUP)
    {
        key_states[event.key.keysym.sym] = false;
    }
    else if (event.type == SDL_WINDOWEVENT) // logic for scaling all the textures when resizing the window
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
            // ^ first way of doing it
        }
    }
}

void Player::update()
{
    bool moving = false;
    frame_counter++;
    anim_frame_counter++;

    if (frame_counter % 11 == 0)
    {    
        if(frame_counter%22000==0){ //Health regeneration every 22k frames ig
            setHealth(getHealth()>getCurrentHealth() ? getCurrentHealth()+5 : getHealth());
                // Player temp=*this;
            // this->setHealth(temp.getHealth()>temp.getCurrentHealth() ? (temp+5).getCurrentHealth() : temp.getHealth()); // sat and looked at this for 10 seconds then started laughing 
            //                                                                                                             // why do i have to implement + overload man
        
        }
        time_since_last_attack++;
        if (frame_counter % 3003 == 0)
        {   setEnergy(getCurrentEnergy()<getEnergy() ? getCurrentEnergy()+5 : getEnergy());
            setIsHit(false);
            takeDamage(); //function that checks if a player is inside a firezone and take damage only once per attack
        }
        attack_frame_counter++;
        if (getIsAttacking())
        {
            if (attack_frame_counter % attackDelay == 0)
            {
                int currentFrame = (attack_frame_counter / attackDelay) % 4;
                if (attack_frame_counter % attackDelay == 0)
                    animation(false, currentFrame);

                // if last frame is reached, stop attack animation
                if (currentFrame == 3)
                {
                    attack_frame_counter = 0;
                    if (key_states[SDLK_f] == false)
                        setIsAttacking(false); // setting key_states to false makes the animation smoother and lets the player attack whilst moving
                    setEnergy(getCurrentEnergy()-5);
                }
            }
        }
        else
            attack_frame_counter = 0;

        for (const auto &pair : key_bindings) //looping through the key_bindings and call every function associated with it
        {
            if (key_states[pair.first])
            {
                moving = key_to_direction[pair.first] != NONE;
                if (isValidMove(key_to_direction[pair.first]))
                {   
                    if(pair.first==SDLK_f && getCurrentEnergy()!=0){
                        (this->*pair.second)();
                        
                    }
                    else (this->*pair.second)();
                }
                // std::cerr<<getIsAttacking()<<std::endl;
                // action = key_to_direction[pair.first]==NONE;
            }
        }
        if (getIsHit()) //calling animation for being hit
        {
            if ((anim_frame_counter % 32) == 0)
            {
                animation(false, anim_frame_counter % 3);
            }
        }
        else //calling animation for movement or idle position
        {
            int frameModulo = moving ? 7 : 4; // 7 frames for moving, 4 for staying
            if ((anim_frame_counter % (moving ? animDelay : stayingDelay)) == 0) 
            {
                animation(moving, anim_frame_counter % frameModulo);
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
    auto helper=Room::layout[x][y].room_sprites;
    scale();
    float scaledX,scaledY;
    Room::spritesScale(scaledX,scaledY);
    for(int i=0;i<7;i++){
        for(int j=0;j<8;j++){
            if(helper[i][j].sprite==DOOR){ // changing the room and updating position so it makes it look natural
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
                        SDL_Delay(100); // didnt try to not include it but thought a bit of delay woud make the game transition a bit more natural
                        setRoomCoordinates(std::make_pair(2,2)); //starting position is always 2,2
                    }
            }
        }
    }
}
bool Player::checkNearDoor(SDL_Rect doorPosition) const{ //helper function for changing rooms, verifying 
    SDL_Rect playerPosition=getPosition();
float x,y;
    Room::spritesScale(x,y);
    doorPosition.h=static_cast<int>(50*y);
    return SDL_HasIntersection(&playerPosition,&doorPosition);
}