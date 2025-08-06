#include "ShaderManager.h"

#include <iostream>


// Define the static member
Shader* ShaderManager::defaultGridShader = nullptr; // the grid shader
//Shader* ShaderManager::defaultGLTFShader = nullptr;
//Shader* ShaderManager::LightBulbShader = nullptr;   // the light bulb shader
//Shader* ShaderManager::LightShader = nullptr;   // the obj shaders 
//Shader* ShaderManager::defaultShader = nullptr;   // the obj shaders 
//Shader* ShaderManager::skyShader = nullptr;   // the sky shaders 
//Shader* ShaderManager::TerrainShader = nullptr;   // the sky shaders 
//Shader* ShaderManager::TestShader = nullptr;   // the sky shaders 
//Shader* ShaderManager::highlightShader = nullptr;   // the Edit mesh shaders 
//Shader* ShaderManager::LineShader = nullptr;   // the Edit mesh normal line shaders 

// Initialize the shader
void ShaderManager::SetupShaders() {
    // This is the grid shader
   // defaultGridShader = new Shader("../Engine/Shader/ShaderFiles/default_Grid.vert", "../Engine/Shader/ShaderFiles/default_Grid.frag");
    defaultGridShader = new Shader("Engine/Engine/Shader/ShaderFiles/default_Grid.vert",
        "Engine/Engine/Shader/ShaderFiles/default_Grid.frag");

}