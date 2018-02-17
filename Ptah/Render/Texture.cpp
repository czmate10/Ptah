#include "Render/Texture.h"
#include "stb_image.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

Ptah::Texture::Texture(TextureType type, std::string path, int width, int height, int nr_channels, unsigned char* raw_data) 
	: Type(type)
	, Path(path)
	, Width(width)
	, Height(height)
	, NrChannels(nr_channels)
{
	// Determine OpenGL type of texture
	unsigned int gl_type = 0;
	switch(type)
	{
	case TextureType::TEXTURE_1D:
		gl_type = GL_TEXTURE_1D;
		break;
	case TextureType::TEXTURE_2D:
		gl_type = GL_TEXTURE_2D;
		break;
	case TextureType::TEXTURE_3D:
		gl_type = GL_TEXTURE_3D;
		break;
	case TextureType::TEXTURE_CUBEMAP:
		gl_type = GL_TEXTURE_CUBE_MAP;
		break;
	default:
		throw std::runtime_error("Unknown texture type for texture '" + path + "'");
	}

	// Determine the corresponding OpenGL format type for this texture
	unsigned gl_format = 0;
	if(nr_channels == 3)
		gl_format = GL_RGB;
	else if(nr_channels == 4)
		gl_format = GL_RGBA;

	// Setup the OpenGL texture
	glGenTextures(1, &texture_handle_);  
	glBindTexture(GL_TEXTURE_2D, texture_handle_);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(gl_type, 0, gl_format, width, height, 0, gl_format, GL_UNSIGNED_BYTE, raw_data);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Free stb data
	stbi_image_free(raw_data);
}
