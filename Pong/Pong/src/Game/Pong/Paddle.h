#pragma once

#include <glm/glm.hpp>
#include <SDL.h>

#include "../../Engine/AssetsManager.h"

class Paddle
{
	private:
		bool is_player;
		bool animating;
		int direction;
		glm::vec2 position;

		int animation_direction;
		glm::vec2 default_scale;
		glm::vec2 current_scale;
		glm::vec2 max_scale;

		AssetsManager* assets_manager;

	public:
		Paddle(glm::vec2 initial_position, glm::vec2 scale, bool is_player, AssetsManager* assets_manager)
			: position(initial_position), default_scale(scale), current_scale(scale), max_scale(scale * glm::vec2(1.2)),
			  is_player(is_player), assets_manager(assets_manager), direction(0) {}

		void Start();
		void Update(float delta_time);
		void Render(SDL_Renderer* renderer);

		glm::vec2 GetPosition() const;
		int GetWidth() const;
		int GetHeight() const;
		void SetAnimate(bool animate);

		void MovePaddle(float delta_time);
		void AnimatePaddle(float delta_time);
};