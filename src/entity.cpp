#include "../headers/entity.h"

Entity::Entity(const std::vector<std::string> path, SDL_Renderer* r, int id)
{
	 id = 0;

	// Used For Animation
	currentFrame = 0;
    frameTime = 0.125;
    timeAccumulator = 0.0;
}

SDL_Texture* Entity::loadTexture(const std::string& path, SDL_Renderer* r) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface == nullptr) {
        std::cout << "Unable to load image! SDL_image Error: " << IMG_GetError() << std::endl;
        return nullptr; // Return nullptr if loading fails
    }
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(r, surface);
    SDL_FreeSurface(surface);
    
    if (texture == nullptr) {
        std::cout << "Unable to create texture! SDL Error: " << SDL_GetError() << std::endl;
    } else {}
    
    return texture;
}


void Entity::render(SDL_Renderer*)
{

}

void Entity::tick(double deltaTime)
{

}

int Entity::getId()
{
	return id;
}

struct entity_info Entity::getEntityInfo()
{
	return entityInfo;
}

void Entity::setEntityInfo(entity_info i)
{
	entityInfo = i;
}
