#pragma once
#include <string>

namespace AndromedaEngine
{
	// Reports error and prints it into console
	// isFatalError - true to quit program after report
	extern void Error(bool reportErrorCondition, std::string, bool isFatalError);
	extern void Error(bool reportErrorCondition, std::string);
	extern void Error(std::string);
	extern void Error(std::string, bool isFatalError);
	extern void print(std::string text);
}