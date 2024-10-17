#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "../headers/entityinfo.h"


class Entity
{
public:
	Entity(const std::vector<std::string> paths, SDL_Renderer* r, int id);

	virtual void render(SDL_Renderer* r);
	virtual void tick(double deltaTime);

	SDL_Texture* texture;
	SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* r);

	bool operator==(const Entity& other) const {
        return id ==
		 other.id; // Compare based on ID or other unique attribute
    }

	int getId();

	entity_info entityInfo;
	entity_info getEntityInfo();
	void setEntityInfo(entity_info i);

protected:
	int id;
	std::vector<SDL_Texture*> textures; // A vector of the textures from an entity
	// Values used in animation of entity
	int currentFrame;
	double frameTime;
	double timeAccumulator;


	int x;
	int y;

};