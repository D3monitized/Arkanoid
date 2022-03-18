#include "Engine.h"

bool isRunning; 

SDL_Window* window; 
SDL_Renderer* renderer; 
bool keys[SDL_NUM_SCANCODES];
bool mouseLeft = false; 
bool mouseRight = false; 
float deltaTime = 0;

Scenes currentScene = Scenes::Menu; 

void Engine::PlayAudio(std::string path = "") 
{
	std::cout << "Play Audio" << std::endl; 

	//Checks if there's a path to a new audio file, if not, just play the current audio file
	if (path != "")
	{
		//Load audio file
		if (SDL_LoadWAV(path.c_str(), &audioSpec, &waveStart, &waveLength) == nullptr)
			std::cout << "Failed to load sound: " << SDL_GetError << std::endl;
	}	

	int status = SDL_QueueAudio(audioDevice, waveStart, waveLength);
	SDL_PauseAudioDevice(audioDevice, 0);	
}

void Engine::PauseAudio()
{
	SDL_PauseAudioDevice(audioDevice, 1);
}

void Engine::SetupDevice()
{
	//Setup audio device, will use default audio device on computer
	audioSpec.freq = 25000;
	audioSpec.channels = 2; 
	audioDevice = SDL_OpenAudioDevice(NULL, 0, &audioSpec, NULL, 0);
	if (audioDevice == 0)
		std::cout << "Audio device error: " << SDL_GetError() << std::endl; 	
	
	
	waveStart = 0;
	waveLength = 1;	
}

Engine::~Engine()
{
	SDL_FreeWAV(waveStart);
	SDL_CloseAudioDevice(audioDevice);
}
	