#pragma once

#include <fstream>
#include <sstream>

#include "Engine.h"
#include "UIButton.h"
#include "Block.h"

class MainMenu {
public:	
	SDL_Texture* headerTexture; 				

	UIButton playButton; 
	UIButton loadLevelButton; 
	UIButton levelEditorButton;
	UIButton quitButton;
	
	Vector2 headerPos; 
	Vector2 headerSize;			

	void Update(); 
	void Draw(); 

	MainMenu(); 	
	~MainMenu(); 
};