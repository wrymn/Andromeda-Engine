#ifndef COMMON_H
#define COMMON_H

#define MAKE_STRING1(x) #x
#define MAKE_STRING(x) MAKE_STRING1(x)

/*
	Whether the debug mode is enabled or not.
	- Debug mode enables as developer console.
*/
#define DEBUG_MODE false

/*
	Default width and height of the window in pixels.
*/
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 720

/*
	Target bit build.
*/
#define BIT_BUILD "32-bit"

/*
	The name of the engine.
*/
#define ENGINE_NAME "Andromeda Engine"

/*
	The major version of the engine.
	Each major version includes huge enhancement to the engine
*/
#define ANDROMEDA_MAJOR_VERSION 1

/*
	The minor version of the engine.
	Minor version includes smaller addition to the Andromeda Engine
*/
#define ANDROMEDA_MINOR_VERSION 0

/*
	Andromeda Engine full version.
*/
#define ANDROMEDA_VERSION ("v" MAKE_STRING(ANDROMEDA_MAJOR_VERSION) "." MAKE_STRING(ANDROMEDA_MINOR_VERSION))

#endif