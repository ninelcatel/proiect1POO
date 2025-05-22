#include "gamemanager.h"
#include <iostream>

GameManager::GameManager(): player("res/PLAYER/player.png")
{
    room=new Room();
}

GameManager::~GameManager() {
    delete room; //cleanup
    SDL_DestroyRenderer(game.getRenderer());
    SDL_DestroyWindow(game.getWindow());
    SDL_Quit();
}

void GameManager::run() {
    SDL_Event event;
    bool running = true;

    while (running) {                       // Game loop
        while (SDL_PollEvent(&event)) {
            handleEvents(event, running);
        }

        update();
        render();
        SDL_RenderPresent(game.getRenderer());
    }
    std::cout << player; //the operator overload
}

void GameManager::handleEvents(SDL_Event& event, bool& running) { // Handling events in function of GameState 
    if (event.type == SDL_QUIT) {
        running = false;
    }

    switch (game.getGameState()) {
        case GameState::GAME:
            player.handleEvent(event);
            break;
        case GameState::MENU:
            menu.handleEvent(event);
            if(menu.getIsRunning()==false) running=false; // If "QUIT" is pressed stop the game
            break;
        case GameState::PAUSE:
            if (event.key.keysym.sym == SDLK_RETURN && event.type == SDL_KEYUP) { // Press enter to unpause the game
                game.setGameState(GameState::GAME);
            }
            break;
        default:
            break;
    }
}

void GameManager::update() {
    if (game.getGameState() == GameState::GAME) {
        player.update();
    }
    if(player.getIsChangingLevels()){ // Changing Rooms
        player.setIsChangingLevel(false);
        delete room; // Free the memory
        room = new Room();
    }
}

void GameManager::render() {
    SDL_SetRenderDrawColor(game.getRenderer(), 0, 0, 0, 255);
    SDL_RenderClear(game.getRenderer());

    switch (game.getGameState()) {
        case GameState::GAME:
            room->render(player);
            player.render();
            stats.render(player);
            break;

        case GameState::MENU:
            menu.render();
            break;

        case GameState::PAUSE: {  // Could've been done with another class or function but works just as fine
            TTF_Font* font = TTF_OpenFont("res/font/Pixeled.ttf", 50);
            SDL_Color color = {255, 255, 255};
            SDL_Rect textRect;
            int width, height;
            SDL_GetWindowSize(game.getWindow(), &width, &height);

            SDL_Surface* textSurface = TTF_RenderText_Solid(font, "RESUME", color);
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(game.getRenderer(), textSurface);
            SDL_FreeSurface(textSurface);

            TTF_SizeText(font, "RESUME", &textRect.w, &textRect.h); // Text content
            textRect.x = (width - textRect.w) / 2;
            textRect.y = (height - textRect.h) / 2;
            TTF_CloseFont(font);

            room->render(player);
            player.render();
            stats.render(player);

            SDL_SetRenderDrawBlendMode(game.getRenderer(), SDL_BLENDMODE_BLEND); // For adding a slight blur on the background
            SDL_SetRenderDrawColor(game.getRenderer(), 180, 180, 180, 50);
            SDL_Rect blur = {0, 0, width, height}; // Occupy the whole screen
            SDL_RenderFillRect(game.getRenderer(), &blur);
            SDL_RenderCopy(game.getRenderer(), textTexture, nullptr, &textRect);
            SDL_DestroyTexture(textTexture); // Free memory
            break;
        }

        default:
            break;
    }
}
