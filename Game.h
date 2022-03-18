#pragma once
#include <SDL.h>
#include <stdio.h>

class Game {
public:
	Game();
	~Game();

	void Init(const char* title, int x, int y, int w, int h, bool fullscreen); 
	void SetupGame(); 
	void SetupCustomGame(); 
	
	void OnSceneChanged();

	void HandleEvents();
	void Update();
	void Render();
	void Clean();	
	static SDL_Event event;
};