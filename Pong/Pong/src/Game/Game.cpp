#include "Game.h"

#include <iostream>
#include <ctime>
#include <chrono>

#include "../Engine/InputManager.h"

const char* title = "Pong";
const int width = 800;
const int height = 600;

void Game::Setup()
{
	// Initializing SDL

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "An error was produced when initializing SDL: " << SDL_GetError() << std::endl;
		is_running = false;
		return;
	}

    // Initializing TTF

    if (TTF_Init() != 0)
    {
        std::cout << "Error initializing TTF: " << TTF_GetError() << std::endl;
        is_running = false;
        return;
    }

	// Creating SDL Window

	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		std::cout << "An error was produced when creating SDL window: " << SDL_GetError() << std::endl;
		is_running = false;
		return;
	}

	// Creating SDL Renderer

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (renderer == NULL)
	{
		std::cout << "An error was produced when creating SDL renderer: " << SDL_GetError() << std::endl;
		is_running = false;
		return;
	}

    assets_manager = new AssetsManager(renderer);

    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm local_tm;
    localtime_s(&local_tm, &now_time); // TODO: probably take care of system specifics in the future :)
    int seed = (local_tm.tm_hour * 60 * 60) + (local_tm.tm_min * 60) + local_tm.tm_sec;
    random = new Random(seed);

    pong = new Pong(assets_manager, random);

	is_running = true;
}

void Game::Run()
{
	Setup();

    pong->Start();

	while (is_running)
	{
        delta_time = (SDL_GetTicks() - milliseconds_previous_frame) / 1000.0;
        if (delta_time > 1000) {
            delta_time = 0;
        }

        milliseconds_previous_frame = SDL_GetTicks();

		ProcessInput();
		Update();
		Render();
	}
}

void Game::ProcessInput()
{
    SDL_Event event;

    InputManager::SetMouseButtonUp(0, false);
    InputManager::SetMouseButtonUp(1, false);

    while (SDL_PollEvent(&event)) // Iterating through all the possible events that might have happened in this frame
    {
        Uint32 buttonState = SDL_GetMouseState(NULL, NULL);
        switch (event.type)
        {
        case SDL_QUIT:
            is_running = false;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_o:
                InputManager::SetKey(KeyCode::O, true);
                break;
            case SDLK_w:
                InputManager::SetKey(KeyCode::W, true);
                break;
            case SDLK_s:
                InputManager::SetKey(KeyCode::S, true);
                break;
            case SDLK_l:
                InputManager::SetKey(KeyCode::L, true);
                break;
            case SDLK_ESCAPE:
                InputManager::SetKey(KeyCode::ESCAPE, true);
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
            case SDLK_o:
                InputManager::SetKey(KeyCode::O, false);
                break;
            case SDLK_w:
                InputManager::SetKey(KeyCode::W, false);
                break;
            case SDLK_s:
                InputManager::SetKey(KeyCode::S, false);
                break;
            case SDLK_l:
                InputManager::SetKey(KeyCode::L, false);
                break;
            case SDLK_ESCAPE:
                InputManager::SetKey(KeyCode::ESCAPE, false);
                break;
            }
            break;
        case SDL_MOUSEMOTION:
            InputManager::SetMousePosition(glm::vec2(event.motion.x, event.motion.y));
            break;
        case SDL_MOUSEBUTTONDOWN:
            switch (event.button.button)
            {
            case SDL_BUTTON_LEFT:
                InputManager::SetMouseButtonDown(0, true);
                break;
            case SDL_BUTTON_RIGHT:
                InputManager::SetMouseButtonDown(1, true);
                break;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            switch (event.button.button)
            {
            case SDL_BUTTON_LEFT:
                InputManager::SetMouseButtonDown(0, false);
                InputManager::SetMouseButtonUp(0, true);
                break;
            case SDL_BUTTON_RIGHT:
                InputManager::SetMouseButtonDown(1, false);
                InputManager::SetMouseButtonUp(1, true);
                break;
            }
            break;
        }
    }
}

void Game::Update()
{
    pong->Update(delta_time);
}

void Game::Render()
{
	SDL_SetRenderDrawColor(renderer, 35, 35, 35, 255);
	SDL_RenderClear(renderer);

    pong->Render(renderer);

	SDL_RenderPresent(renderer);
}

void Game::Destroy()
{
    delete pong;
    delete random;
    delete assets_manager;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}