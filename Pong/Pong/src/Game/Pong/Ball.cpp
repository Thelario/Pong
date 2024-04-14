#include "Ball.h"

#include <iostream>

#include "../../Engine/Utils.h"

#include "Pong.h"

const std::string ball_asset_id = "fancy-ball";

Ball::Ball(glm::vec2 initial_position, int width, int height, float speed, AssetsManager* assets_manager, Random* random,
	Paddle* left_paddle, Paddle* right_paddle, Pong* pong)
	: position(initial_position), width(width), height(height), speed(speed), assets_manager(assets_manager),
	random(random), direction(glm::vec2(0)), left_paddle(left_paddle), right_paddle(right_paddle), pong(pong)
{ }

void Ball::Start()
{
	position = glm::vec2(400, 300);

	do {
		direction = glm::vec2(random->GenerateRandomFloat(-1, 1), random->GenerateRandomFloat(-1, 1));
	}
	while (direction.x == 0 || direction.y == 0);

	direction = glm::normalize(direction);
}

void Ball::Update(float delta_time)
{
	glm::vec2 new_position = position + delta_time * speed * direction;

	// Calculamos si la bola choca contra el paddle de la izquierda

	if (Utils::CheckCollisionAABB(true, new_position, width, height,
		left_paddle->GetPosition(), left_paddle->GetWidth(), left_paddle->GetHeight()))
	{
		direction.x *= -1;
		speed++;
	}

	// Calculamos si la bola choca contra el paddle de la derecha

	if (Utils::CheckCollisionAABB(true, new_position, width, height,
		right_paddle->GetPosition(), right_paddle->GetWidth(), right_paddle->GetHeight()))
	{
		direction.x *= -1;
		speed++;
	}

	// Calculamos si la bola choca contra los límites de derecha e izquierda

	if ((new_position.x - width / 2 <= 0))
	{
		pong->ChangeScore(false);
		Start();
	}
	else if ((new_position.x + width / 2 >= 800))
	{
		pong->ChangeScore(true);
		Start();
	}

	// Calculamos si la bola choca contra los límites de arriba y abajo

	if ((new_position.y - height / 2 <= 0) || (new_position.y + height / 2 >= 600)) {
		direction.y *= -1;
		speed++;
	}

	position += delta_time * speed * direction;
}

void Ball::Render(SDL_Renderer* renderer)
{
	// Render the ball

	if (assets_manager == nullptr) {
		return;
	}

	Texture* texture = assets_manager->GetTexture(ball_asset_id);

	SDL_Rect src = texture->GetSourceRect();

	SDL_Rect dest = {
		static_cast<int>(position.x - (width / 2)),
		static_cast<int>(position.y - (height / 2)),
		static_cast<int>(width),
		static_cast<int>(height)
	};

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_RenderCopy(renderer, texture->GetTexture(), &src, &dest);
}
