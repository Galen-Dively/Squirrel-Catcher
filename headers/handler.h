#pragma once
#include <vector>
#include <memory>  // for std::unique_ptr
#include <iostream>
#include <algorithm>  // for std::remove_if
#include "../headers/entity.h"  // Include your Entity header file
#include <SDL.h>  // Assuming you need SDL for rendering
#include "../headers/client.h"


class Handler
{
public:
    Handler();
    void addEntity(std::unique_ptr<Entity> e);    // Accept by const reference
    void removeEntity(std::unique_ptr<Entity> e); // Accept by const reference

    void renderEntities(SDL_Renderer* r); // Pass SDL_Renderer to render entities
	void updateEntities(double deltaTime);

	Entity* getEntity(int id);
	Client client;

	void syncWithServer();
	

private:
    // Store entities as unique pointers for better memory management
    std::vector<std::unique_ptr<Entity>> entities;
};
