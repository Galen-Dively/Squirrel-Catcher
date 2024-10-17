#include "../headers/handler.h"

// Constructor
Handler::Handler()
{
	client.establish();
	std::cout << "connection established\n";
}

// Add an entity (copy or move to avoid unnecessary copying)
void Handler::addEntity(std::unique_ptr<Entity> e) {
    std::cout << "Adding entity..." << std::endl; // Debugging log
    entities.push_back(std::move(e)); // Store the unique pointer
}

// Remove an entity (by reference)
void Handler::removeEntity(std::unique_ptr<Entity> e)
{
    // // Use std::remove_if and lambda to find and remove the entity
    // entities.erase(
    //     std::remove_if(entities.begin(), entities.end(),
    //         [&e](const std::unique_ptr<Entity>& entity)
    //         {
    //             // Assuming you have a comparison operator (operator==) for Entity
    //             return *entity == e;
    //         }),
    //     entities.end());
}

void Handler::syncWithServer()
{

    for (const auto& entity : entities)
    {
		if(entity->getId() == 1)
		{
			entity_info playerData = entity->getEntityInfo();  // Assuming Entity has getPlayerInfo
			playerData.connection_id = client.getPlayerID();
			client.sendPlayerInfo(playerData); // Send to the server

		}
        if (entity->getId() ==2)
		{
				
				// 2. Receive updated dummy data from the server
				entity_info dummyData;
				dummyData = client.recievePlayer();
				std::cout << "Entity Info Dummy: " << dummyData.x;

				// 3. Update the dummy entity with the new data from the server
				entity->setEntityInfo(dummyData);  // Assuming Entity has setPlayerInfo
		}  // Assuming the Entity class has a render method
    }

}


// Render all entities
void Handler::renderEntities(SDL_Renderer* renderer)
{
    // Loop through all entities and call their render function
    for (const auto& entity : entities)
    {
        entity->render(renderer);  // Assuming the Entity class has a render method
    }
}

Entity* Handler::getEntity(int id)
{
	for (const auto& entity : entities)
	{
		if(entity->getId() == id)
		{
	
			return entity.get();
		}
	}
	return nullptr;
}

void Handler::updateEntities(double deltaTime)
{
	for (const auto& entity : entities)
    {
        entity->tick(deltaTime);  // Assuming the Entity class has a render method
    }
	
}