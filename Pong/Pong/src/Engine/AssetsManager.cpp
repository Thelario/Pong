#include "AssetsManager.h"

#include <SDL_image.h>
#include <iostream>
#include <fstream>

#include "json.hpp"

using json = nlohmann::json;

AssetsManager::AssetsManager(SDL_Renderer* renderer)
{
	this->renderer = renderer;

	if (LoadAssets() == true) {
		std::cout << "Assets Manager created!" << std::endl;
	}
	else {
		std::cout << "Assets Manager created with errors!! BE CAREFUL!!!" << std::endl;
	}
}

AssetsManager::~AssetsManager()
{
	ClearAssets();

	std::cout << "Assets Manager destroyed!" << std::endl;
}

bool AssetsManager::LoadAssets()
{
	// Loading textures

	const std::string& config_file_name = "./config/textures_config.json";

	std::ifstream file;

	file.open(config_file_name);

	if (file.fail() == true)
	{
		std::cout << "Failed to open file: " << config_file_name << std::endl;
		return false;
	}

	json json_data = json::parse(file);

	std::string file_path = "./assets/images/";

	for (const auto& texture_json : json_data["textures"])
	{
		std::string texture_file_path = file_path + texture_json["name"].get<std::string>();

		SDL_Texture* texture = GenerateTexture(texture_file_path);

		Texture* my_texture = new Texture(texture, texture_json["width"], texture_json["height"], texture_json["tile_size"]);

		textures.emplace(texture_json["asset_id"], my_texture);
	}

	file.close();

	// Loading fonts

	AddFont("arial-font", "./assets/fonts/arial.ttf", 100);
	AddFont("charriot-font", "./assets/fonts/charriot.ttf", 100);

	return true;
}

void AssetsManager::ClearAssets()
{
	for (auto texture : textures)
	{
		delete texture.second;
	}

	textures.clear();

	for (auto font : fonts)
	{
		TTF_CloseFont(font.second);
	}

	fonts.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/// Textures
//////////////////////////////////////////////////////////////////////////////////////////////////////

SDL_Texture* AssetsManager::GenerateTexture(const std::string& file_path)
{
	// Create a surface based on the imgage file in the file path specified

	SDL_Surface* surface = IMG_Load(file_path.c_str());

	if (surface == NULL)
	{
		std::cout << "A problem occured when loading image with in file path "
			<< file_path << " | " << SDL_GetError() << std::endl;
		return nullptr;
	}

	// Created a texture based on the 

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (texture == NULL)
	{
		std::cout << "ERROR - A problem occured when creating a texture from image in file path "
			<< file_path << " | " << SDL_GetError() << std::endl;
		return nullptr;
	}

	SDL_FreeSurface(surface);

	return texture;
}

Texture* AssetsManager::GetTexture(const std::string& asset_id) const
{
	if (textures.find(asset_id) == textures.end())
	{
		std::cout << "ERROR - Trying to get a texture with a wrong asset id: " << asset_id << std::endl;
		return nullptr;
	}

	return textures.at(asset_id);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/// Fonts
//////////////////////////////////////////////////////////////////////////////////////////////////////

void AssetsManager::AddFont(const std::string& asset_id, const std::string& file_path, int font_size)
{
	TTF_Font* font = TTF_OpenFont(file_path.c_str(), font_size);

	if (font == NULL) {
		std::cout << TTF_GetError() << std::endl;
	}

	fonts.emplace(asset_id, font);
}

TTF_Font* AssetsManager::GetFont(const std::string& asset_id) const
{
	if (fonts.find(asset_id) == fonts.end())
	{
		std::cout << "ERROR - Trying to get a font with a wrong asset id: " << asset_id << std::endl;
		return nullptr;
	}

	return fonts.at(asset_id);
}
