#pragma once

#include <SDL.h>

#include "../../Engine/AssetsManager.h"
#include "../../Engine/Random.h"

#include "Ball.h"

class Pong
{
	private:
		AssetsManager* assets_manager;
		Random* random;

		int left_paddle_score;
		int right_paddle_score;
		Text* left_paddle_text;
		Text* right_paddle_text;
		Paddle* left_paddle;
		Paddle* right_paddle;
		Ball* ball;

	public:
		Pong(AssetsManager* assets_manager, Random* random)
			: assets_manager(assets_manager), random(random) {}
		~Pong();

		void ClearPong();
		void Start();
		void Update(float delta_time);
		void Render(SDL_Renderer* renderer);

		void RenderBackground(SDL_Renderer* renderer);

		void ChangeScore(bool left_paddle);
};