cmake_minimum_required(VERSION 3.10)

project(MyGame CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(main
    main.cpp
    src/entity.cpp
    src/init.cpp
    src/player.cpp
    src/assets.cpp
)

target_link_libraries(main SDL2::SDL2 SDL2_image::SDL2_image)
