#pragma once

namespace AndromedaEngine
{
	class System
	{
	public:
		//Initializes Andromeda Engine
		static void Initialize(int argc, char* argv[]);
		//Shutdown the engine and frees all resources
		static void Quit();

	private:
		//Prints the engine info to the console at the start of program
		static void DisplayInfo();
	};
}