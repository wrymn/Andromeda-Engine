#include <iostream>
#include <string>
#include <SDL2\SDL.h>
#include "Errors.h"

namespace AndromedaEngine
{

	//REPORTS ERROR MESSAGE
	void Error(bool reportErrorCondition, std::string text)
	{
		if (reportErrorCondition)
		{
			std::cout << "Error occured:" << std::endl << std::endl;

			//Report message
			std::cout << text << std::endl << std::endl;
		}
	}

	//REPORTS ERROR MESSAGE
	void Error(std::string text)
	{
		std::cout << "Error occured:" << std::endl << std::endl;

		//Report message
		std::cout << text << std::endl << std::endl;
	}

	//REPORTS FATAL ERROR MESSAGE AND QUITS THE PROGRAM
	void Error(bool reportErrorCondition, std::string text, bool isFatalError)
	{
		if (reportErrorCondition)
		{
			if (isFatalError)
				std::cout << "Error occured:" << std::endl << std::endl;
			else
				std::cout << "Fatal error occured:" << std::endl << std::endl;

			//Report message
			std::cout << text << std::endl << std::endl;

			//User input if Fatal
			if (isFatalError)
			{
				std::cout << "Press any key and enter to exit." << std::endl << std::endl;
				int tmp = 0;
				std::cin >> tmp;
				SDL_Quit();
			}
		}
	}
	//REPORTS FATAL ERROR MESSAGE AND QUITS THE PROGRAM
	void Error(std::string text, bool isFatalError)
	{
		if (isFatalError)
			std::cout << "Error occured:" << std::endl << std::endl;
		else
			std::cout << "Fatal error occured:" << std::endl << std::endl;

		//Report message
		std::cout << text << std::endl << std::endl;

		//User input if Fatal
		if (isFatalError)
		{
			std::cout << "Press any key and enter to exit." << std::endl << std::endl;
			int tmp = 0;
			std::cin >> tmp;
			SDL_Quit();
		}
	}

	//Prints the text to the console
	void print(std::string text)
	{
		std::cout << text << std::endl;
	}
}