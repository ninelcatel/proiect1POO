#include "assets.h"

// made a proper example here of how you should approach a function
// `to write ub code is human, to refactor ub code is divine` - Simi or something
void StatusBars::render(Player &player) {
    int window_width = 0;
    int window_height = 0;

    /*
        1. window can be ambiguous without the context that is a protected member
        2. `window_width` and `window_height` get destroyed after this function call
        ends so this is a dangling pointer waiting to happen; consider making it
        static or something
     */

    if (window)
        SDL_GetWindowSize(window, &window_width, &window_height);
    else {
        std::cerr << "window is null " << SDL_GetError();
        return;
    }

    auto max_hp = player.getHealth();
    auto current_hp = player.getCurrentHealth();
    auto max_energy = player.getEnergy();
    auto current_energy = player.getCurrentEnergy();

    // SDL_Rect has members `int x, y, h, w`, you want to do implicit conversion between float and int
    // you also want to initialize them in an arbitrary order which is voodoo
    // you can also remove repetition of magic numbers and properly name them
    constexpr double w_offset = 0.020;
    constexpr double h_offset = 0.035;

    SDL_Rect position{
        .x = 0,
        .y = static_cast<int>(window_height * (1 - 2 * h_offset)),
        .w = static_cast<int>(window_width * w_offset),
        .h = static_cast<int>(window_height * h_offset),
    };
    // learn to use a debugger man
    // std::cout<<window_height<<std::endl<<window_width<<std::endl;
    for (auto i = 0; i <= max_hp; i += 5) {
        const auto& current_sprite = (i <= current_hp) ? health_bar : broken_health;
        SDL_RenderCopy(renderer, current_sprite, nullptr, &position);
        position.x += position.w;
    }
    
    position.x = 0;
    position.y += position.h;

    for (auto i = 0; i <= max_energy; i += 5) {
        const auto& current_sprite = (i <= current_energy) ? energy_bar : broken_energy;
        SDL_RenderCopy(renderer, current_sprite, nullptr, &position);
        position.x += position.w;
    }
}