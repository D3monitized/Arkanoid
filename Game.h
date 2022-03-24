#pragma once
#include <SDL.h>
#include <stdio.h>

#include "Engine.h"
#include "Player.h"
#include "Block.h"
#include "Ball.h"
#include "MainMenu.h"
#include "LevelEditor.h"

class Game {
public:
	Game();
	~Game();

	SDL_Event event;

	//Game settings: 
	float ballTimer = 10; //when ballTimer hits 0, will spawn another ball

	//Other components
	Engine engine;
	MainMenu* menu;
	LevelEditor editor;

	//Player
	Player player;

	//Blocks
	Block* block[100000];
	Vector2 blockSize = Vector2(50, 50);
	Vector2 blockPos = Vector2();
	int blockRow = 0;
	int blockColumn = 0;
	int blockAmount = 0;

	//Ball
	Ball ball[20];
	int ballCount = 1;
	Vector2 ballSize = Vector2(35, 35);
	Vector2 ballPos = Vector2();
	float timer = 0;

	void Init(const char* title, int x, int y, int w, int h, bool fullscreen); 
	void SetupGame(); 
	void SetupCustomGame(); 
	void UpdateGame();
	void RenderGame(); 
	
	void SpawnBall();
	void OnSceneChanged();

	void HandleEvents();
	void Update();
	void Render();
	void Clean();		
};