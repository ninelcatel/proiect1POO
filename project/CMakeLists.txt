cmake_minimum_required(VERSION 3.10)

project(MyGame CXX)

if(ENABLE_CXX_20)
    set(CMAKE_CXX_STANDARD 20)
else()
    set(CMAKE_CXX_STANDARD 17)
endif()

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(${CMAKE_PROJECT_NAME}
        main.cpp
        src/entity.cpp
        src/init.cpp
        src/player.cpp
        src/assets.cpp
)

target_link_libraries(${CMAKE_PROJECT_NAME} SDL2::SDL2 SDL2_image::SDL2_image)

# please for the love of god don't hard paste
# your assets into the `build` folder ever again
add_custom_command(
        TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources
        ${CMAKE_BINARY_DIR}/resources
        COMMENT "Copying resources to build directory"
)
