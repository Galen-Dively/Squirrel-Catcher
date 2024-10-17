#pragma once
#include "entity.h"

struct SquirrelInfo
{
    int x;
    int y;
};

class Squirrel : public Entity
{
    public:
    Squirrel(const std::vector<std::string> path_to_images, SDL_Renderer* r, int id);

    void setSquirrelStruct(int x, int y); 

    private:
    float speed = 200;

};