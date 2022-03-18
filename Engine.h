#pragma once
#include <iostream>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_audio.h"

#include "BoxCollider.h"
#include "Vector2.h"

#define WIDTH 1280
#define HEIGHT 720 

extern bool isRunning;

extern SDL_Window* window; 
extern SDL_Renderer* renderer; 
extern bool keys[SDL_NUM_SCANCODES];
extern bool mouseLeft; 
extern bool mouseRight; 
extern float deltaTime; 


extern enum class Scenes{
	Menu, Game, CustomGame, LevelEditor
};
extern Scenes currentScene; 

class Engine {
public: 
	//Audio	
	SDL_AudioSpec audioSpec;
	SDL_AudioDeviceID audioDevice;
	Uint8* waveStart; //where the data starts
	Uint32 waveLength; //how long the wavefile is
	void SetupDevice(); 
	void PlayAudio(std::string path);
	void PauseAudio();	
	~Engine(); 
};
