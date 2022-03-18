#pragma once
#include "Engine.h"

class UIButton {
public:
	SDL_Texture* buttonText; //button text texture
	SDL_Rect backgroundRect;

	bool clicked = false; 

	Vector2 buttonPos; 
	Vector2 buttonSize; 

	bool ButtonClicked(); 
	void Update(); 
	void Draw();

	UIButton(std::string texFilePath, Vector2 pos, Vector2 size); 
	UIButton(); 
	~UIButton();
};