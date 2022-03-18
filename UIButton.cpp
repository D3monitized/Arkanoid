#include "UIButton.h"

void UIButton::Update()
{	
	
}

bool UIButton::ButtonClicked()
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	if (mouseX > backgroundRect.x && mouseX < backgroundRect.x + backgroundRect.w &&
		mouseY > backgroundRect.y && mouseY < backgroundRect.y + backgroundRect.h && mouseLeft && !clicked)
	{
		clicked = true;
		return true; 
		std::cout << "button clicked" << std::endl;
	}
	if (!mouseLeft)
		clicked = false;

	return false; 
}

void UIButton::Draw()
{
	SDL_Rect buttonRect = { buttonPos.x, buttonPos.y, buttonSize.x, buttonSize.y };

	backgroundRect.x = buttonPos.x + buttonSize.x / 4;
	backgroundRect.y = buttonPos.y + buttonSize.y / 2.55f;
	backgroundRect.w = buttonSize.x / 2;
	backgroundRect.h = buttonSize.y / 5;
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &backgroundRect);

	SDL_RenderCopy(renderer, buttonText, NULL, &buttonRect);
}

UIButton::UIButton()
{

}

UIButton::UIButton(std::string texFilePath, Vector2 pos, Vector2 size)
{
	SDL_Surface* tempSurface = IMG_Load(texFilePath.c_str());
	if (tempSurface == nullptr)
		std::cout << "Failed to load button image: " << texFilePath << " " << SDL_GetError() << std::endl; 

	buttonText = SDL_CreateTextureFromSurface(renderer, tempSurface); 
	if (buttonText == nullptr)
		std::cout << "Failed to create button texture from surface: " << SDL_GetError() << std::endl; 

	SDL_FreeSurface(tempSurface); 

	buttonPos = pos; 
	buttonSize = size; 
}

UIButton::~UIButton()
{
	buttonText = nullptr; 
}