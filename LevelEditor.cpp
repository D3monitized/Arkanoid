#include "LevelEditor.h"

bool mouseClicked; 

void LevelEditor::Update()
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	cursorMarker.pos = Vector2(mouseX - 25, mouseY - 25);

	if (mouseLeft && !mouseClicked)
	{
		mouseClicked = true;
		SDL_Color color = { 0, 0, 255, 0 };
		blocks[blockCount] = Block(cursorMarker.pos, cursorMarker.size);
		blocks[blockCount].color = color; 
		blocks[blockCount].isAlive = true; 
		blockCount++; 
		std::cout << "Created block" << std::endl; 
	}
	else if (!mouseLeft)
		mouseClicked = false;

	LevelEditor::CheckUIButtonInput(); 
}

void LevelEditor::CheckUIButtonInput()
{
	backButton.Update(); 
	saveButton.Update();

	if (backButton.ButtonClicked())
		currentScene = Scenes::Menu;
	if (saveButton.ButtonClicked())
		SaveLevel(); 
}

void LevelEditor::Draw()
{
	cursorMarker.Draw(); 
	for (size_t i = 0; i < blockCount; i++)
	{
		blocks[i].Draw(); 
	}

	backButton.Draw(); 
	saveButton.Draw();
}

void LevelEditor::SaveLevel()
{
	fs::create_directory("Assets/Level"); 

	std::ofstream outfile;
	outfile.open("Assets/Level/TestLevel.txt");
	if (!outfile.is_open()) //if file doesn't exist (isn't open), create a new one
		outfile = std::ofstream("Assets/Level/TestLevel.txt");

	outfile << "TestLevel" << std::endl; 

	for (size_t i = 0; i < blockCount; i++)
	{
		std::ostringstream stream; 
		stream << blocks[i].pos.x << " " << blocks[i].pos.y << " " << blocks[i].size.x << " " << blocks[i].size.y; 
		outfile << stream.str() << std::endl; 
	}

	outfile.close(); 

	currentScene = Scenes::Menu; 

	blockCount = 0; 
}

LevelEditor::LevelEditor()
{
	int mouseX, mouseY; 
	SDL_GetMouseState(&mouseX, &mouseY);
	SDL_Color markerColor = { 0, 0, 255, 0 };
	cursorMarker = Block(Vector2(mouseX - 25, mouseY - 25), Vector2(50, 50));
	cursorMarker.color = markerColor; 
	cursorMarker.isAlive = true; 

	backButton = UIButton("Assets/MainMenu/MainMenuText.png", Vector2(-50, -100), Vector2(300, 300));	
	saveButton = UIButton("Assets/MainMenu/SaveButton.png", Vector2(WIDTH - 280, -100), Vector2(300, 300));	
}

LevelEditor::~LevelEditor()
{
	
}