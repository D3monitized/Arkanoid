#include "MainMenu.h"

void MainMenu::Update()
{
	//Buttons
	if (playButton.ButtonClicked())	
		currentScene = Scenes::Game; 
	if (loadLevelButton.ButtonClicked())	
		currentScene = Scenes::CustomGame;	
	if (levelEditorButton.ButtonClicked())			
		currentScene = Scenes::LevelEditor;				
	if (quitButton.ButtonClicked())
		isRunning = false; 
}

void MainMenu::Draw()
{
	//Header texture	
	SDL_Rect headerRect = { headerPos.x, headerPos.y, headerSize.x, headerSize.y };
	SDL_RenderCopy(renderer, headerTexture, NULL, &headerRect);

	//Buttons
	playButton.Draw(); 
	loadLevelButton.Draw(); 
	levelEditorButton.Draw();
	quitButton.Draw(); 
}

MainMenu::MainMenu()
{
	//Load header texture
	SDL_Surface* tempSurface = IMG_Load("Assets/MainMenu/MainMenuText.png");
	if (tempSurface == nullptr)
		std::cout << "Failed to load header-texture (Main Menu): " << SDL_GetError() << std::endl;
	headerTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	if (headerTexture == nullptr)
		std::cout << "Failed to create header-texture from surface (Main Menu): " << SDL_GetError() << std::endl;		

	headerSize = Vector2(300, 300);
	headerPos = Vector2(WIDTH / 2 - headerSize.x / 2, -headerSize.y / 4);
	
	//Buttons
	Vector2 buttonSize = Vector2(300, 300); 
	Vector2 buttonPos = Vector2(WIDTH / 2 - buttonSize.x / 2, headerPos.y + 100);
	playButton = UIButton("Assets/MainMenu/PlayButton.png", buttonPos, buttonSize);

	buttonPos.y += 100; 
	loadLevelButton = UIButton("Assets/MainMenu/LoadLevelButton.png", buttonPos, buttonSize); //to be changed into new texture

	buttonPos.y += 100; 	
	levelEditorButton = UIButton("Assets/MainMenu/LevelEditorButton.png", buttonPos, buttonSize); 

	buttonPos.y += 100; 
	quitButton = UIButton("Assets/MainMenu/QuitButton.png", buttonPos, buttonSize);
}

MainMenu::~MainMenu()
{
	headerTexture = nullptr; 
}