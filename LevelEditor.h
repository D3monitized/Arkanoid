#pragma once
#include <fstream>
#include <sstream>
#include <filesystem>
namespace fs = std::filesystem; 

#include "Engine.h"
#include "Block.h"
#include "UIButton.h"

class LevelEditor {
public:
	Block blocks[1000]; 
	Block cursorMarker;	

	UIButton backButton; 
	UIButton saveButton; 
	
	int blockCount = 0; 

	void CheckUIButtonInput();

	void SaveLevel(); 

	void Update(); 
	void Draw(); 

	LevelEditor();
	~LevelEditor(); 
};