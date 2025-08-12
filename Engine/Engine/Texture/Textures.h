#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <stb/stb_image.h>
#include <iostream>

int nrComponents, width, height; // Number of components in the image

GLuint textureID; // Texture ID

	GLenum Image_format() {
		GLenum t_format = GL_RGBA; // Default format
		if (nrComponents == 1)      // bmp file/ grayscale
			t_format = GL_RED;
		else if (nrComponents == 3) // jpg file
			t_format = GL_RGB;
		else if (nrComponents == 4) // png file
			t_format = GL_RGBA;
		return t_format;
	}

	unsigned int OBJ_Textures(const std::string& path)
	{
		glGenTextures(1, &textureID);

		unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0); // use this one
		if (data)
		{
			Image_format();
			GLenum t_format = Image_format(); // Get the texture format based on the number of components

			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, t_format, width, height, 0, t_format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glBindTexture(GL_TEXTURE_2D, 0);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Texture failed to load at path: " << path << std::endl;
			stbi_image_free(data);
		}

		return textureID;

	}
	void StarField_Textures(const std::string& path) {

	}
	void Terrain_Textures(const std::string& path) {

	}
	void SkyBox_Textures(const std::string& path) {

	}
	// this will copy the used textures to a folder called "UsedTextures/OBJ_Textures" -
	// in the project folder if its not alredy in the folder
	void CopyTextureTo_Folder(const std::string& folderPath) {

	}


	
	


