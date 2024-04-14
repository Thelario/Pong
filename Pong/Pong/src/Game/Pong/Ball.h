#pragma once

#include <glm/glm.hpp>

#include "../../Engine/AssetsManager.h"
#include "../../Engine/Random.h"
#include "../../Engine/Text.h"

#include "Paddle.h"

class Pong;
class Ball
{
	private:
		int width;
		int height;
		float speed;
		glm::vec2 direction;
		glm::vec2 position;

		AssetsManager* assets_manager;
		Random* random;

		Pong* pong;
		Paddle* left_paddle;
		Paddle* right_paddle;

	public:
		Ball(glm::vec2 initial_position, int width, int height, float speed, AssetsManager* assets_manager, Random* random,
			Paddle* left_paddle, Paddle* right_paddle, Pong* pong);

		void Start();
		void Update(float delta_time);
		void Render(SDL_Renderer* renderer);

		void BallHit();
};