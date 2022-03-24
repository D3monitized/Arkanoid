#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <stdlib.h>
#include <iostream>
#include "Engine.h"

#include "Game.h"

Game *game = nullptr;

int main() {
	game = new Game(); 

	game->Init("Arkanoid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, false);
	
	Uint64 previousFrame = SDL_GetPerformanceCounter(); 
	while (isRunning) {	
		Uint64 thisFrame = SDL_GetPerformanceCounter(); 
		Uint64 deltaTicks = thisFrame - previousFrame; 
		deltaTime = (float)deltaTicks / SDL_GetPerformanceFrequency(); 
		previousFrame = thisFrame;

		game->HandleEvents(); 
		game->Update();
		game->Render();	
		SDL_Delay(16);
	}

	game->Clean(); // feedback: despite you call the clean funcion the actual instance of Game class is never deleted. Proper way to do it is:
	delete game; 
	game = nullptr; 

	return 0;
}