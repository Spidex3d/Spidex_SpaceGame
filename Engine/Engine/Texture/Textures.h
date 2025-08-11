#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <stb/stb_image.h>
#include <iostream>
class Textures
{

public:
	Textures() = default;
	~Textures() = default;

	GLenum i_format();

	unsigned int OBJ_Textures(const std::string& path);
	void StarField_Textures(const std::string& path);
	void Terrain_Textures(const std::string& path);
	void SkyBox_Textures(const std::string& path);
	// this will copy the used textures to a folder called "UsedTextures/OBJ_Textures" -
	// in the project folder if its not alredy in the folder
	void CopyTextureTo_Folder(const std::string& folderPath);

private:
	unsigned int textureID;
	int width, height, nrComponents;
	int t_format;
	
};

