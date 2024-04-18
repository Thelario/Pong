#pragma once

#include <map>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Texture.h"

class AssetsManager
{
private:
	SDL_Renderer* renderer;

	std::map<std::string, Texture*> textures;
	std::map<std::string, TTF_Font*> fonts;
	std::map<std::string, Mix_Chunk*> sounds;

	Mix_Music* music;

public:
	AssetsManager(SDL_Renderer* renderer);
	~AssetsManager();

	bool LoadAssets();
	void ClearAssets();

	SDL_Texture* GenerateTexture(const std::string& file_path);
	Texture* GetTexture(const std::string& asset_id) const;

	void AddFont(const std::string& asset_id, const std::string& file_path, int font_size);
	TTF_Font* GetFont(const std::string& asset_id) const;

	void PlayMusic();
	void PlaySound(const std::string& sound_id);
};