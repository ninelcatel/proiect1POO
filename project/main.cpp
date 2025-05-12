#include "src/gamemanager.h"
//TODO: whenever player pressess Space near a HOLE generate a new level.
int main(int argc, char* argv[]) {
    std::srand(std::time(nullptr));
    GameManager manager;
    manager.run();
    return 0;
}
