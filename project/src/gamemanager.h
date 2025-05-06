
#include "init.h"
#include "player.h"
#include "room.h"
#include "menu.h"
#include "assets.h"
class GameManager {

private:
    void handleEvents(SDL_Event& event, bool& running);
    void update();
    void render();

    Game game;
    Player player;
    Room room;
    Menu menu;
    StatusBars stats;
public:
    GameManager();
    ~GameManager();
    void run();

};
