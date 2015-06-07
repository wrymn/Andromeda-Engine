#include "Time.h"
#include <SDL2\SDL.h>

namespace AndromedaEngine{

	//Initialize static variables
	unsigned int Time::FPS = 0;
	unsigned int Time::time = 0;
	float Time::deltaTime = 0;

	float Time::ms = 0;
	float Time::msPassed = 0;
	float Time::timeStart = 0;
	unsigned int Time::frames = 0;
	unsigned int Time::maxFPS = 0;

	//Called at the start of the frame
	void Time::Begin()
	{
		timeStart = SDL_GetTicks();
		time = SDL_GetTicks() * 0.001f;
	}
	//Called at the end of the frame
	void Time::End()
	{
		ms = SDL_GetTicks() - timeStart;
		deltaTime = ms * 0.001f;
		frames++;
		msPassed += ms;

		//Get FPS
		if (msPassed >= 1000)
		{
			FPS = frames;
			msPassed = 0;
			frames = 0;
		}
	}

	void Time::LockFPS(int targetFPS)
	{
		maxFPS = targetFPS; //Times 2x since SDL_Delay was having problems
	}

	int Time::GetMaxFPS()
	{
		return maxFPS;
	}
}