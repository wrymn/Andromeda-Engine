#pragma once

namespace AndromedaEngine{

	class Time{
	public:
		//Sets the game FPS
		static void LockFPS(int targetFPS);
		//Returns the max FPS
		static int GetMaxFPS();
		//Called at the start of the main loop
		static void Begin();
		//Called at the end of the main loop
		static void End();
	private:

	public:
		//Frames Per Seconds
		static unsigned int FPS;
		//The time in seconds since the game started
		static unsigned int time;
		//The time in seconds it took to complete the last frame
		static float deltaTime;
	private:
		//Amount of milliseconds it takes to process the main loop
		static float ms;
		static float msPassed;
		static float timeStart;
		static unsigned int frames;

		static unsigned int maxFPS;
		//friend class MainGame;
	};
}