#include "../headers/eliza.h"

Eliza::Eliza(const std::vector<std::string> paths, SDL_Renderer* r, int id) : Entity(paths, r, id) // Calling parent contrustor
{
    this->rect.x = 0;
    this->rect.y = 0;
    this->rect.w = 64;
    this->rect.h= 64;
    this->id = id;

    this-> entityInfo;
    this->entityInfo.id = this->id;
    this->entityInfo.x = this->rect.x;
    this->entityInfo.y = this->rect.y;
    speed = 200;

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

void Eliza::render(SDL_Renderer* r)
{
    if (textures[currentFrame]) {
        SDL_RenderCopy(r, textures[currentFrame], nullptr, &rect);
    }
}

void Eliza::tick(double deltaTime)
{   
    timeAccumulator += deltaTime;
    this->entityInfo.id = this->id;
    this->entityInfo.x = this->rect.x;
    this->entityInfo.y = this->rect.y;

    // If enough time has passed, switch to the next frame
    if (timeAccumulator >= frameTime) {
        currentFrame = (currentFrame + 1) % textures.size(); // Loop through frames
        timeAccumulator = 0.0;  // Reset the accumulator
    }
    move(deltaTime);
}

void Eliza::move(double deltaTime)
{
    const Uint8* state = SDL_GetKeyboardState(NULL);

    if(state[SDL_SCANCODE_W])
    {
        this->rect.y -= speed*deltaTime;
    }
    if (state[SDL_SCANCODE_S])
    {
        this->rect.y += speed*deltaTime;
    }
    if(state[SDL_SCANCODE_A])
    {
        this->rect.x -= speed*deltaTime;
    }
    if(state[SDL_SCANCODE_D])
    {
        this->rect.x += speed*deltaTime;
    }
    
}


SDL_Rect Eliza::getRect()
{
    return rect;
}

SDL_Texture* Eliza::getTexture()
{
    return texture;
}

