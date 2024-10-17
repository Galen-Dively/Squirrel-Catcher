#include<iostream>
#include <SDL.h>
#include "../headers/game.h"


int main(int argc, char const *argv[])
{
	Game game; // Create the game object
	game.init(); // Initalizes the scene
	game.loop(); // Main loop
	return 0;
}