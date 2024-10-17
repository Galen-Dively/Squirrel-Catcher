#pragma once
#include <SDL.h>
#include <iostream>
#include "../headers/handler.h"
#include "../headers/eliza.h"
#include "../headers/playerDummy.h"

class Game
{

	public:
		Game();
		void init();
		void loop();
		void render();
		void initScene();

	private:
		const char* title;
		int width;
		int height;
		int pos;

		//delta time
		uint64_t currentFrameTime;
		uint64_t previousFrameTime;
		double deltaTime;


		SDL_Window* window;
		SDL_Surface* surface;
		SDL_Renderer* renderer;
		Handler handler;



};