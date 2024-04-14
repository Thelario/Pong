#include "Pong.h"

#include <iostream>

#include "../../Engine/InputManager.h"

const std::string background_asset_id = "fancy-court";
const int background_width = 800;
const int background_height = 600;

Pong::~Pong()
{
	ClearPong();
}

void Pong::ClearPong()
{
	delete ball;
	delete left_paddle;
	delete right_paddle;
	delete left_paddle_text;
	delete right_paddle_text;
}

void Pong::Start()
{
	left_paddle_score = 0;
	right_paddle_score = 0;

	left_paddle_text = new Text(glm::vec2(350, 50), glm::vec2(0.5), "0", "arial-font", assets_manager, { 255, 255, 255, 255 });
	right_paddle_text = new Text(glm::vec2(450, 50), glm::vec2(0.5), "0", "arial-font", assets_manager, { 255, 255, 255, 255 });

	left_paddle = new Paddle(glm::vec2(48, 300), true, assets_manager);
	right_paddle = new Paddle(glm::vec2(752, 300), false, assets_manager);

	ball = new Ball(glm::vec2(400, 300), 32, 32, 200, assets_manager, random, left_paddle, right_paddle, this);

	left_paddle->Start();
	right_paddle->Start();
	ball->Start();
}

void Pong::Update(float delta_time)
{
	if (InputManager::GetKey(KeyCode::ESCAPE)) {
		ClearPong();
		Start();
	}

	left_paddle->Update(delta_time);
	right_paddle->Update(delta_time);
	ball->Update(delta_time);
}

void Pong::Render(SDL_Renderer* renderer)
{
	RenderBackground(renderer);

	left_paddle->Render(renderer);
	right_paddle->Render(renderer);
	ball->Render(renderer);
	left_paddle_text->Render(renderer);
	right_paddle_text->Render(renderer);
}

void Pong::RenderBackground(SDL_Renderer* renderer)
{
	if (assets_manager == nullptr) {
		return;
	}

	Texture* texture = assets_manager->GetTexture(background_asset_id);

	SDL_Rect src = texture->GetSourceRect();

	SDL_Rect dest = {
		static_cast<int>(0),
		static_cast<int>(0),
		static_cast<int>(background_width),
		static_cast<int>(background_height)
	};

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_RenderCopy(renderer, texture->GetTexture(), &src, &dest);
}

void Pong::ChangeScore(bool left_paddle)
{
	if (left_paddle)
	{
		left_paddle_score++;
		left_paddle_text->SetText(std::to_string(left_paddle_score));
	}
	else
	{
		right_paddle_score++;
		right_paddle_text->SetText(std::to_string(right_paddle_score));
	}
}