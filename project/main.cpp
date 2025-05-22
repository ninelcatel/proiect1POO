#include "src/gamemanager.h"
int main(int argc, char* argv[]) {
    std::srand(std::time(nullptr));
    GameManager manager;
    manager.run();
    return 0;
}
