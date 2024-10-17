#include "../headers/game.h"

Game::Game()
{

    // StartWindow Aspects
    title = "Squirel Madness";
    width = 500;
    height = 500;

    pos = SDL_WINDOWPOS_CENTERED;
    // End Window Aspects

    // Start SDL Initialzation
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return;  // Exit the constructor if initialization fails
    }

     if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return;  // Exit if SDL_image initialization fails
    }
    // End SDL Init

    // Window And surdaces
    window = SDL_CreateWindow(title, pos, pos, width, height, 0);

    // Create the renderer after creating the window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

}

// Called before loop to setup scene
void Game::init() {
    initScene();
}

void Game::loop() {
    bool running = true;
    SDL_Event event;

    // Delta time
    previousFrameTime = SDL_GetPerformanceCounter();

    while (running) {

        //Calculate Delta Time
        currentFrameTime = SDL_GetPerformanceCounter();
        uint64_t elapsedTicks = currentFrameTime - previousFrameTime;
        deltaTime = (double)elapsedTicks / (double)SDL_GetPerformanceFrequency();  // In seconds
        previousFrameTime = currentFrameTime;
    

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        
        }

        handler.syncWithServer();
        handler.updateEntities(deltaTime);
        render();
        
    }
}

void Game::render()
{

    // Set the draw color (background color)
    SDL_SetRenderDrawColor(renderer, 51, 255, 51, 255); // RGB: 51, 51, 51, Alpha: 255 (opaque)
    SDL_RenderClear(renderer);

    handler.renderEntities(renderer);

    SDL_RenderPresent(renderer);

} 

void Game::initScene()
{
    std::cout << "Initializing scene...";
    std::vector<std::string> elizaPaths = {
        "/Users/galendively/Documents/Development/Eliza Game/Images/eliza/eliza_forward_0.png",
        "/Users/galendively/Documents/Development/Eliza Game/Images/eliza/eliza_forward_1.png",
        "/Users/galendively/Documents/Development/Eliza Game/Images/eliza/eliza_forward_2.png",
        "/Users/galendively/Documents/Development/Eliza Game/Images/eliza/eliza_forward_3.png"
    };
    handler.addEntity(std::make_unique<Eliza>(elizaPaths, renderer, 1));
    handler.addEntity(std::make_unique<PlayerDummy>(elizaPaths, renderer, 2));
}