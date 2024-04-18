#include "Paddle.h"

#include "../../Engine/InputManager.h"
#include <iostream>

const std::string paddle_asset_id = "fancy-paddle";
const int paddle_width = 32;
const int paddle_height = 128;
const int paddle_speed = 120;
const float animation_speed = 1.75f;

void Paddle::Start()
{
	direction = 0;
	animating = false;
	animation_direction = 1;
}

void Paddle::Update(float delta_time)
{
	MovePaddle(delta_time);
	AnimatePaddle(delta_time);
}

void Paddle::MovePaddle(float delta_time)
{
	direction = 0;

	if (is_player)
	{
		if (InputManager::GetKey(KeyCode::W)) {
			direction = -1;
		}
		if (InputManager::GetKey(KeyCode::S)) {
			direction = 1;
		}
	}
	else
	{
		if (InputManager::GetKey(KeyCode::O)) {
			direction = -1;
		}
		if (InputManager::GetKey(KeyCode::L)) {
			direction = 1;
		}
	}

	float new_position_y = position.y + delta_time * direction * paddle_speed;

	if ((new_position_y - paddle_height / 2 <= 0) || (new_position_y + paddle_height / 2 >= 600)) {
		return;
	}

	position.y = new_position_y;
}

void Paddle::AnimatePaddle(float delta_time)
{
	if (animating == false) {
		return;
	}

	current_scale += animation_speed * delta_time * glm::vec2(animation_direction);
	if (current_scale.x >= max_scale.x && current_scale.y >= max_scale.y) {
		animation_direction = -1;
	}

	if (current_scale.x <= default_scale.x && current_scale.y <= default_scale.y) {
		animation_direction = 1;
		current_scale = default_scale;
		animating = false;
	}
}

void Paddle::Render(SDL_Renderer* renderer)
{
	if (assets_manager == nullptr) {
		return;
	}

	Texture* texture = assets_manager->GetTexture(paddle_asset_id);

	SDL_Rect src = texture->GetSourceRect();

	float real_width = paddle_width * current_scale.x;
	float real_height = paddle_height * current_scale.y;

	SDL_Rect dest = {
		static_cast<int>(position.x - (real_width / 2)),
		static_cast<int>(position.y - (real_height / 2)),
		static_cast<int>(real_width),
		static_cast<int>(real_height)
	};

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_RenderCopy(renderer, texture->GetTexture(), &src, &dest);
}

glm::vec2 Paddle::GetPosition() const {
	return position;
}

int Paddle::GetWidth() const {
	return paddle_width;
}

int Paddle::GetHeight() const {
	return paddle_height;
}

void Paddle::SetAnimate(bool animate) {
	animating = animate;
}
