#include "Textures.h"



GLenum Textures::i_format()
{
	if (nrComponents == 1)      // bmp file/ grayscale
        t_format = GL_RED;
    else if (nrComponents == 3) // jpg file
        t_format = GL_RGB;
    else if (nrComponents == 4) // png file
        t_format = GL_RGBA;
	return t_format;
}
// this one first
unsigned int Textures::OBJ_Textures(const std::string& path)
{
    //unsigned int textureID;

    glGenTextures(1, &textureID);

    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0); // use this one
    if (data)
    {
		i_format();

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

void Textures::StarField_Textures(const std::string& path)
{
}

void Textures::Terrain_Textures(const std::string& path)
{
}

void Textures::SkyBox_Textures(const std::string& path)
{
}
