Must have GCC,SDL2, SDL2_image and SDL2_ttf installed

git clone https://github.com/ninelcatel/proiect1POO.git

cd proiect1POO/project

mkdir build

cd build

cmake ..

make

./Game

or if you don't want to use cmake:

g++ main.cpp src/room.cpp src/assets.cpp src/enemy.cpp src/gamemanager.cpp src/entity.cpp src/init.cpp src/player.cpp -o main -lSDL2 -lSDL2_image -lSDL2_ttf && ./main
 