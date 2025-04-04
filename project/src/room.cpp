#include "room.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
Room::Room(){
    room=loadTexture("res/ROOM/MAIN_ROOM.png",renderer);
    rect={0,0,1024,720};
    for(int i=0;i<4;++i){
        for(int j=0;j<4;++j)
            layout[i][j].exists=false;
    }
    layout[1][1].exists=true;
    layout[1][0].exists=true;
    layout[1][2].exists=true;
    layout[0][1].exists=true;
    layout[2][1].exists=true;
    
};
void Room::render(){
    (window) ? SDL_GetWindowSize(window,&window_width,&window_height) : SDL_Quit();
    rect.w=window_width;
    rect.h=window_height;
    SDL_RenderCopy(renderer,room,nullptr,&rect);
    
}
void Room::generateLevel(){
    const int maxRooms=6;
    int roomCount=1;
    std::vector<std::pair<int,int>> activeRooms={{1,1},{1,0},{0,1},{2,1},{1,2}};
    while(roomCount<=maxRooms && !activeRooms.empty()){
        int randNumber=std::rand();
        int index=randNumber%activeRooms.size();
        auto [x,y]=activeRooms[index];
        std::vector<std::pair<int, int>> directions = {
            {x-1, y}, {x+1, y}, {x, y-1}, {x, y+1}
        };
        std::random_shuffle(directions.begin(), directions.end());
        bool roomAdded = false;
        for(auto [nx,ny] : directions){
            if(nx<0 || nx>4 || ny<0 || ny>4) continue;
            if(layout[nx][ny].exists) continue;
            layout[nx][ny].exists=true;
            ++roomCount;
            activeRooms.push_back({nx,ny});
            roomAdded=true;
            break;
        }
        if(!roomAdded) activeRooms.erase(activeRooms.begin()+index);
    }
    /*for(int i=0;i<=4;++i){
        for(int j=0;j<=4;++j)
            std::cout<<layout[i][j].exists<<" ";
        std::cout<<std::endl;
    }*/
   std::vector<std::pair<int,int>> tupleslist;
   
   for(auto [x,y] : activeRooms){
        
        tupleslist=checkForNeighbour(x,y); // adding doors 
        if(tupleslist.size()){
        for(auto [i,j] : tupleslist){
            std::string pathPrefix="res/ROOM/DOORS/DOOR_";  //putting doors;
            auto [nx,ny]= x==i ? 
            y<j ? std::make_pair(3,7) : std::make_pair(3,0) 
            : x<i ? std::make_pair(6,3) : std::make_pair(0,3);
            layout[x][y].roomSprites[nx][ny].sprite=DOOR;
            std::string suffix = nx==3 ? ny!=0 ? "RIGHT" : "LEFT" : nx!=0 ? "DOWN" : "UP";
            std::string fullPath = pathPrefix+ suffix + ".png";
            layout[x][y].roomSprites[nx][ny].filePaths.push_back(fullPath.c_str());
        
        }
        }
   }
}
/*bool Room::checkForNeighbour(int i,int j){
    if(i-1>=0) if(layout[i-1][j].exists) return true;
    if(i+1>4) if(layout[i+1][j].exists) return true;
    if(j-1>=0) if(layout[i][j-1].exists) return true;
    if(j+1>4) if(layout[i][j+1].exists) return true;
    return false;   
}*/

std::vector<std::pair<int,int>> Room::checkForNeighbour(int i,int j){
    std::vector<std::pair<int,int>> tuplesList;
    if(i-1>=0) if(layout[i-1][j].exists) tuplesList.push_back({i-1,j});
    if(i+1<4) if(layout[i+1][j].exists) tuplesList.push_back({i+1,j});
    if(j-1>=0) if(layout[i][j-1].exists) tuplesList.push_back({i,j-1});
    if(j+1<4) if(layout[i][j+1].exists) tuplesList.push_back({i,j+1});
    return tuplesList;
}
