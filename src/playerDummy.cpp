#include "../headers/PlayerDummy.h"

PlayerDummy::PlayerDummy(const std::vector<std::string> paths, SDL_Renderer* r, int id) : Entity(paths, r, id) // Calling parent contrustor
{
    this->rect.x = 0;
    this->rect.y = 0;
    this->rect.w = 64;
    this->rect.h= 64;
    this->id = id;

    this->entityInfo;
    this->entityInfo.connection_id = 1;
    this->entityInfo.id = this->id;
    this->entityInfo.x = this->rect.x;
    this->entityInfo.y = this->rect.y;

    for (const std::string& path : paths) {
        SDL_Texture* texture = loadTexture(path, r);
        if (texture) {
            textures.push_back(texture);
        } else {
            std::cerr << "Failed to load texture: " << path << std::endl;
        }
    }
    // Animation
    currentFrame = 0;
    frameTime = 0.125;
    timeAccumulator = 0.0;
}

void PlayerDummy::render(SDL_Renderer* r)
{
    if (textures[currentFrame]) {
        SDL_RenderCopy(r, textures[currentFrame], nullptr, &this->rect);
    }
    std::cout << this->rect.x;
}

void PlayerDummy::tick(double deltaTime)
{   
    timeAccumulator += deltaTime;
    this->rect.x = this->entityInfo.x;
    this->rect.y = this->entityInfo.y;
    
    if (timeAccumulator >= frameTime) {
        currentFrame = (currentFrame + 1) % textures.size(); // Loop through frames
        timeAccumulator = 0.0;  // Reset the accumulator
    }
}


SDL_Rect PlayerDummy::getRect()
{
    return this->rect;
}

SDL_Texture* PlayerDummy::getTexture()
{
    return texture;
}

