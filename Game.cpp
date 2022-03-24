#include <iostream>

#include "Game.h"
#include "Engine.h"
#include "Player.h"
#include "Block.h"
#include "Ball.h"
#include "MainMenu.h"
#include "LevelEditor.h"


// feedback: global variables below are not supporting object-oriented approach needed for this assignemnt. I'd vote for moving them to the Game class when possible or other classes
// where they belong, for example inside main function.

SDL_Event Game::event;

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

void Game::Init(const char* title, int x, int y, int w, int h, bool fullScreen)
{

	int flags = 0;
	if (fullScreen)
		flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems initialized" << std::endl;

		window = SDL_CreateWindow(title, x, y, w, h, flags);
		if (window)
			std::cout << "Window created" << std::endl;

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
			std::cout << "Renderer created" << std::endl;

		isRunning = true;
	}
	else
		isRunning = false;

	//Do Game Stuff	
	engine.SetupDevice();
	player = Player();
	ballPos = Vector2(player.pos.x + player.size.x / 2 - ballSize.x / 2, player.pos.y - player.size.y + ballSize.y);
	ball[0] = Ball(ballPos, ballSize);
	timer = ballTimer;
	player.GetBallReference(ball, &ballCount);

	if (currentScene == Scenes::Game)
		SetupGame();
	else if (currentScene == Scenes::CustomGame)
		SetupCustomGame(); 

	menu = new MainMenu(); // feedback: memory allocated but never released. Should be deleted in either destructor for Game or Clean function
	editor = LevelEditor();
}


void Game::SetupGame()
{
	//Calculates how many blocks to fit in vertically and horizontally depending on screen size
	blockRow = WIDTH / blockSize.x;
	blockColumn = (HEIGHT / 2) / blockSize.y;

	//Centeres the block rows to the middle of the screen
	float blockLength = (blockRow)*blockSize.x;
	float startOffsetX = (WIDTH - blockLength) / 2;
	std::cout << startOffsetX << std::endl;
	blockPos.x = startOffsetX;

	int count = 0; //Keeps track of which row the for loop is on. 
	SDL_Color currentColor = { 168, 50, 50 }; //Sets the color of the blocks, depending on which row. (Each row will have a new tint of the same color)
	int currentHealth = blockColumn + 1; //Will get changed for each row of blocks, The top ones that are created first will have the most hp
	for (size_t i = 0; i < blockRow + 2; i++)
	{
		int current = i + blockRow * count;
		block[current] = new Block(&engine, blockPos, blockSize, currentHealth); // feedback: memory allocated but never released. Should be deleted in either destructor for Game or Clean function
		block[current]->GetBallReference(ball, &ballCount);
		block[current]->isAlive = true;
		block[current]->color = currentColor;
		//block[current]->collider.draw = true; 
		blockPos.x += blockSize.x;

		if (blockPos.x + blockSize.x >= WIDTH && count < blockColumn)
		{
			blockPos.y += blockSize.y;
			blockPos.x = startOffsetX;
			currentColor.b += 10;
			currentHealth--;
			count++;
			i = 0;
		}

		blockAmount++;
	}

}

void Game::SetupCustomGame()
{
	std::cout << "Setting up custom game" << std::endl; 

	std::ifstream file;
	file.open("Assets/Level/TestLevel.txt");
	if (!file.is_open())
	{
		std::cout << "Couldn't open file" << std::endl;
		return;
	}

	//Loads all block positions and sizes from text file (located in "Assets/Level")
	int iteration = 0;
	for (std::string line; std::getline(file, line); )
	{
		if (iteration == 0)	{
			iteration++; 
			continue;
		}		

		Vector2 pos; 
		Vector2 size; 

		std::string temp;
		std::stringstream intValue;
		int currentNum = 0;

		bool x = false;
		bool y = false;
		bool w = false;		
		
		for (size_t i = 0; i < std::size(line); i++)
		{
			char current = line[i]; 

			switch (current)
			{
			case ' ':
				intValue = std::stringstream(temp);
				intValue >> currentNum;
				if (!x)
				{
					pos.x = currentNum;
					currentNum = 0; 
					temp = ""; 
					x = true;
					break;
				}
				else if (x && !y)
				{
					pos.y = currentNum;					
					currentNum = 0;
					temp = "";
					y = true;
					break;
				}
				else if (y && !w)
				{
					size.x = currentNum;
					currentNum = 0;
					temp = "";
					w = true;
					break;
				}				
			default:
				temp += current;
				break;
			}

			if (i == std::size(line) - 1)
			{				
				intValue = std::stringstream(temp); 
				intValue >> currentNum; 
				size.y = currentNum;
			}			
		}

		std::cout << pos << " " << size << std::endl;

		block[iteration - 1] = new Block(&engine, pos, size, 1); // feedback: same here, you allocate a new memory without deleting already allocated Block instances and never delete it. This is a double memory leak.
		block[iteration - 1]->GetBallReference(ball, &ballCount);
		block[iteration - 1]->isAlive = true;
		blockAmount++; 

		iteration++;
	}

	file.close();
}

void Game::OnSceneChanged()
{
	if (currentScene == Scenes::Game)
		SetupGame();
	else if (currentScene == Scenes::CustomGame)
		SetupCustomGame(); 
}

void Game::HandleEvents()
{
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_KEYDOWN: {
		int scancode = event.key.keysym.scancode;
		keys[scancode] = true;
		break;
	}
	case SDL_KEYUP: {
		int scancode = event.key.keysym.scancode;
		keys[scancode] = false;
		break;
	}
	case SDL_MOUSEBUTTONDOWN: {
		mouseLeft = event.button.button == SDL_BUTTON_LEFT;
		mouseRight = event.button.button == SDL_BUTTON_RIGHT;
		break;
	}
	case SDL_MOUSEBUTTONUP: {
		mouseLeft = event.button.button == SDL_BUTTON_LEFT ? false : mouseLeft;
		mouseRight = event.button.button == SDL_BUTTON_RIGHT ? false : mouseRight;
		break;
	}

	}
}

void UpdateGame();
void SpawnBall();

Scenes thisScene = currentScene; 
void Game::Update()
{
	if (currentScene != thisScene) {
		OnSceneChanged();
		thisScene = currentScene; 
	}
		

	//Game
	if (currentScene == Scenes::Game || currentScene == Scenes::CustomGame)
	{
		UpdateGame();
		SpawnBall();
	}
	if (currentScene == Scenes::Menu)
		menu->Update();
	if (currentScene == Scenes::LevelEditor)
		editor.Update();	
}

void UpdateGame()
{
	//Player
	player.Update();

	//Blocks	
	for (size_t i = 0; i < blockAmount; i++)
	{
		if (block[i] != nullptr)
		{
			block[i]->Update();
		}

	}

	//Ball
	ballPos = Vector2(player.pos.x + player.size.x / 2 - ballSize.x / 2, player.pos.y - player.size.y + ballSize.y);
	for (size_t i = 0; i < ballCount; i++)
	{
		if (&ball[i] != nullptr)
			ball[i].Update(ballPos);
	}
}

void SpawnBall()
{
	if (timer > 0)
	{
		timer -= deltaTime;
	}
	else
	{
		timer = ballTimer;
		ball[ballCount] = Ball();
		ballCount++;
	}
}

void RenderGame();
void Game::Render()
{
	SDL_RenderClear(renderer);

	//Game
	if (currentScene == Scenes::Game || currentScene == Scenes::CustomGame)
		RenderGame();
	if (currentScene == Scenes::Menu)
		menu->Draw();
	if (currentScene == Scenes::LevelEditor)
		editor.Draw();

	//Background color
	if (currentScene == Scenes::Game || currentScene == Scenes::CustomGame) //Game 
		SDL_SetRenderDrawColor(renderer, 39, 58, 93, 255); //Cornflower blue
	else //Main Menu / Level Editor
		SDL_SetRenderDrawColor(renderer, 48, 110, 69, 255); //Greenish

	SDL_RenderPresent(renderer);
}

void RenderGame()
{
	//Player
	player.Draw();

	//Blocks
	for (size_t i = 0; i < blockAmount; i++)
	{
		if (block[i] != nullptr)
			block[i]->Draw();
	}

	//Ball
	for (size_t i = 0; i < ballCount; i++)
	{
		if (&ball[i] != nullptr)
			ball[i].Draw();
	}
}

void Game::Clean()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	std::cout << "Game Quit" << std::endl;
}

Game::Game()
{
}
Game::~Game()
{
}

