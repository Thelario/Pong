#pragma once

#include <glm/glm.hpp>
#include <SDL.h>

#include "../../Engine/AssetsManager.h"

class Paddle
{
	private:
		bool is_player;
		int direction;
		glm::vec2 position;

		AssetsManager* assets_manager;

	public:
		Paddle(glm::vec2 initial_position, bool is_player, AssetsManager* assets_manager)
			: position(initial_position), is_player(is_player), assets_manager(assets_manager), direction(0) {}

		void Start();
		void Update(float delta_time);
		void Render(SDL_Renderer* renderer);

		glm::vec2 GetPosition() const;
		int GetWidth() const;
		int GetHeight() const;
};