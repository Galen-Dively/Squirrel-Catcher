#pragma once
#include "../headers/entity.h"

class PlayerDummy : public Entity
{
public:
	PlayerDummy(const std::vector<std::string> path, SDL_Renderer* r, int id);
	void render(SDL_Renderer* renderer) override;
	void tick(double deltaTimes) override;


	float speed;

	SDL_Rect getRect();
	SDL_Texture* getTexture();
 
	SDL_Rect rect;

    

};
