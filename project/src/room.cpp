#include "room.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
RoomLayout Room::layout[5][5]={};
Room::Room()
{
    room = loadTexture("res/ROOM/ROOM_TEMPLATE.png", renderer);
    rect = {0, 0, 1024, 720};
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
            layout[i][j].exists = false;
    }
    layout[2][2].exists = true;
    layout[2][1].exists = true;
    layout[2][3].exists = true;
    layout[1][2].exists = true;
    layout[3][2].exists = true;
    layout[2][2].roomSprites[0][3].filePaths.push_back("res/ROOM/DOORS/DOOR_UP.png"); // main room
    layout[2][2].roomSprites[6][3].filePaths.push_back("res/ROOM/DOORS/DOOR_DOWN.png");
    layout[2][2].roomSprites[3][0].filePaths.push_back("res/ROOM/DOORS/DOOR_LEFT.png");
    layout[2][2].roomSprites[3][7].filePaths.push_back("res/ROOM/DOORS/DOOR_RIGHT.png");
    layout[2][2].roomSprites[0][3].sprite = DOOR;
    layout[2][2].roomSprites[6][3].sprite = DOOR;
    layout[2][2].roomSprites[3][0].sprite = DOOR;
    layout[2][2].roomSprites[3][7].sprite = DOOR;
    generateLevel();
    loadSpriteTextures();
};
void Room::render(Player &player)
{
    (window) ? SDL_GetWindowSize(window, &window_width, &window_height) : SDL_Quit();
    rect.w = window_width;
    rect.h = window_height;
    auto [x, y] = player.getRoomCoordinates();
    SDL_RenderCopy(renderer, room, nullptr, &rect);
    for (int i = 0; i < 7; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {

            Tiles &helper = layout[x][y].roomSprites[i][j];
            if (helper.sprite == DOOR)
            {
                float scaleX,scaleY;
                spritesScale(scaleX,scaleY);
                helper.position.h=static_cast<int>(scaleY*helper.basePosition.h);
                helper.position.y=static_cast<int>(scaleY*helper.basePosition.y);
                helper.position.x=static_cast<int>(helper.basePosition.x*scaleX);
                helper.position.w=static_cast<int>(scaleX*helper.basePosition.w);
                SDL_RenderCopy(renderer, helper.texture, nullptr, &helper.position);
                                
            }
        }
    }
}
void Room::generateLevel()
{
    const int maxRooms = 6;
    int roomCount = 1;
    std::vector<std::pair<int, int>> activeRooms = {{2, 2}, {2, 1}, {1, 2}, {3, 2}, {2, 3}};
    while (roomCount <= maxRooms && !activeRooms.empty())
    {
        int randNumber = std::rand();
        int index = randNumber % activeRooms.size();
        auto [x, y] = activeRooms[index];
        std::vector<std::pair<int, int>> directions = {
            {x - 1, y}, {x + 1, y}, {x, y - 1}, {x, y + 1}};
        std::random_shuffle(directions.begin(), directions.end());
        bool roomAdded = false;
        for (auto [nx, ny] : directions)
        {
            if (nx < 0 || nx >= 5 || ny < 0 || ny >= 5)
                continue;
            if (layout[nx][ny].exists)
                continue;
            layout[nx][ny].exists = true;
            ++roomCount;
            activeRooms.push_back({nx, ny});
            roomAdded = true;
            break;
        }
        if (!roomAdded)
            activeRooms.erase(activeRooms.begin() + index);
    }

    std::vector<std::pair<int, int>> tupleslist;

    for (auto [x, y] : activeRooms)
    {

        tupleslist = checkForNeighbour(x, y); // adding doors
        if (tupleslist.size())
        {
            for (auto [i, j] : tupleslist)
            {
                std::string pathPrefix = "res/ROOM/DOORS/DOOR_"; // putting doors;
                auto [nx, ny] = x == i  ? y < j ? std::make_pair(3, 7) : std::make_pair(3, 0)
                                 : x < i ? std::make_pair(6, 3)
                                        : std::make_pair(0, 3);
                layout[x][y].roomSprites[nx][ny].sprite = DOOR;
                std::string suffix = nx == 3 ? ny != 0 ? "RIGHT" : "LEFT" : nx != 0 ? "DOWN"
                                                                                    : "UP";
                std::string fullPath = pathPrefix + suffix + ".png";
                layout[x][y].roomSprites[nx][ny].filePaths.push_back(fullPath);
                // std::cerr<<layout[x][y].roomSprites[nx][ny].filePaths[0]<<" "<<x<<" "<<y<<" "<<nx<<" "<<ny<<std::endl;
            }
        }
    }
    for(int i=0;i<5;i++)
        {
            for(int j=0;j<5;j++)
                std::cout<<layout[i][j].exists<<" ";
            std::cout<<std::endl;
        }
}
/*bool Room::checkForNeighbour(int i,int j){
    if(i-1>=0) if(layout[i-1][j].exists) return true;
    if(i+1>4) if(layout[i+1][j].exists) return true;
    if(j-1>=0) if(layout[i][j-1].exists) return true;
    if(j+1>4) if(layout[i][j+1].exists) return true;
    return false;
}*/

std::vector<std::pair<int, int>> Room::checkForNeighbour(int i, int j)
{
    std::vector<std::pair<int, int>> tuplesList;
    if (i < 0 || i >= 5 || j < 0 || j >= 5)
    {
        std::cerr << "checkForNeighbour called with out-of-bounds indices: " << i << " " << j << std::endl;
        return tuplesList;
    }

    if (i - 1 >= 0 && layout[i - 1][j].exists)
        tuplesList.push_back({i - 1, j});
    if (i + 1 < 5 && layout[i + 1][j].exists)
        tuplesList.push_back({i + 1, j});
    if (j - 1 >= 0 && layout[i][j - 1].exists)
        tuplesList.push_back({i, j - 1});
    if (j + 1 < 5 && layout[i][j + 1].exists)
        tuplesList.push_back({i, j + 1});

    return tuplesList;
}
void Room::loadSpriteTextures()
{
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            if (layout[i][j].exists)
            {
                for (int row = 0; row < 7; ++row)
                {
                    for (int col = 0; col < 8; ++col)
                    {
                        if (layout[i][j].roomSprites[row][col].sprite == DOOR && !layout[i][j].roomSprites[row][col].filePaths.empty())
                        {
                            layout[i][j].roomSprites[row][col].texture = loadTexture(layout[i][j].roomSprites[row][col].filePaths[0].c_str(), renderer);
                            
                            switch (row)
                            {
                            case 0:
                                layout[i][j].roomSprites[row][col].basePosition = {420, 80, 200, 125};
                                break;
                            case 6:
                                layout[i][j].roomSprites[row][col].basePosition = {420, 580, 200, 75};
                            case 3:
                                switch (col)
                                {
                                case 0:
                                    layout[i][j].roomSprites[row][col].basePosition = {100, 325, 75, 100};
                                    break;
                                case 7:
                                    layout[i][j].roomSprites[row][col].basePosition = {850, 325, 75, 100};
                                default:
                                    break;
                                }
                            default:
                                break;
                            }

                        }
                        
                        //  std::cout<<"layout[i][j]: "<<i<<" "<<j<<" sprite[row][col] "<<row<<" "<<col<<" "<<layout[i][j].roomSprites[row][col].filePaths[0]<<std::endl;
                    }
                }
            }
        }
    }
}
void Room::spritesScale(float &scale_x,float& scale_y){        //use x and y via static_cast<int>(rect.x*x) or sth to scale when resziing

    SDL_GetWindowSize(window,&window_width,&window_height);
    scale_x = static_cast<float>(window_width) / 1024;
    scale_y = static_cast<float>(window_height) / 720; 
}