#pragma once
#include <glm\glm.hpp>

#include "Vector.h"
#include "Color.h"
#include "Input.h"
#include "Texture.h"
#include "Sprite.h"
#include "Errors.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "Time.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Scene.h"
#include "Collider.h"
#include "CircleCollider2D.h"
#include "BoxCollider.h"
#include "Manager.h"
#include "System.h"
#include "Video.h"

namespace AndromedaEngine
{
	//Initializes Andromeda Engine
	// - this has to be called first to initialize Engine
	extern void InitializeEngine(int argc, char* argv[]);
	// - this is called after calling external game classes
	extern void StartEngine();
}

// - List of all steps to get the engine going
//----------------------------------------------
// 1. Initialize (OpenGL, SDL, Glew...)
// 2. Create Window
// 3. Get Input (EXIT / PLAY)
// 3. Clear window
// Clear Color buffer 
// Clear Depth buffer
// 4. Paint to window
// 5. Shaders
//----------------------------------------------
// 5. Load Textures
// 6. Make engine library
// 7. Game Camera
// 8. Sprite batching optimization
//Add texture to list
//Create Vertex Array Object
//Sort the list of textures by their "Depth"
//Create batches