#pragma once

#include "../Engine/Random.h"

#include "Pong/Pong.h"

class Game
{
	private:
		Uint32 milliseconds_previous_frame;
		double delta_time;
		bool is_running;

		SDL_Window* window;
		SDL_Renderer* renderer;
		AssetsManager* assets_manager;
		Random* random;

		Pong* pong;

	public:
		void Setup();
		void Run();
		void Destroy();

		void ProcessInput();
		void Update();
		void Render();
};