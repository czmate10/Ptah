#include "Resources/TextureLoader.h"
#include "stb_image.h"
#include "Resources/Resources.h"
#include "Render/Texture.h"
#include "Logger.h"

Ptah::Texture* Ptah::TextureLoader::Load(TextureType type, std::string path)
{
	int width, height, nr_channels;
	unsigned char *data = stbi_load((Ptah::Resources::PATH_TEXTURES + path).c_str(), &width, &height, &nr_channels, 0); 

	Logger::Debug("Loading texture '" + path + "', (" + std::to_string(width) + "x" + std::to_string(height) + "), # of channels: " + std::to_string(nr_channels));

	auto tex = new Texture(type, path, width, height, nr_channels, data);
	return tex;
}
