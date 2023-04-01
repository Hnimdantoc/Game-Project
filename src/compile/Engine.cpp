#include "Engine.hpp"
#include "TextureManager.hpp"
#include "Timer.hpp"
#include "Scenes.hpp"

Engine::Engine():window(NULL), renderer(NULL){};

Engine::~Engine(){}

Engine* Engine::static_Instance = nullptr;

void Engine::init(const char* title, int x, int y, int w, int h, Uint32 flags){
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    static_Instance = this;
    // Init window
    window = SDL_CreateWindow(title, x, y, w, h, flags);
    if (window == NULL) std::cout << "Window failed to initialize. Error: " << SDL_GetError() << std::endl;

    // Init renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) std::cout << "Failed to create renderer. Error: " << SDL_GetError() << std::endl;

    // Set icon for window
    icon = IMG_Load(ICON_PATH);
    SDL_SetWindowIcon(window, icon);
    SDL_FreeSurface(icon);

    // Load sprite sheets from txt file
    TextureManager::GetInstance()->LoadFromFile("res/AnimationLink/animation.txt");
    
    Menu* menu = new Menu();

    // Set ground
    _Ground.x = Ground_X;
    _Ground.y = Ground_Y;
    _Ground.x = Ground_W;
    _Ground.h = Ground_H;
}

void Engine::Quit(){
    Timer::getIntance()->~Timer();
    SDL_Log("Timer deleted");
    SceneManager::GetInstance()->CleanAllScene();
    SDL_Log("All scenes deleted");
    SDL_DestroyWindow(window);
    SDL_Log("Destroyed window");
    TTF_Quit();
    SDL_Quit();
}

void Engine::Render(){
    // Set draw color and clear the canvas for next draw
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    // Draw scene
    SceneManager::GetInstance()->Render();

    // Update the screen after draw
    SDL_RenderPresent(renderer);    
}

void Engine::Update(float dt){
    SceneManager::GetInstance()->Update(dt);
}

void Engine::Events(){
    Input::GetInstance()->Listen();
}