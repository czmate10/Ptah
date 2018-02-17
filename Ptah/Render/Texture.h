#pragma once
#include <string>

namespace Ptah
{
	enum TextureType : unsigned int
	{
		TEXTURE_1D,
		TEXTURE_2D,
		TEXTURE_3D,
		TEXTURE_CUBEMAP,
	};

	class Texture
	{
	public:
		std::string Path;
		TextureType Type;
		int Width;
		int Height;
		int NrChannels;

		Texture(TextureType type, std::string path, int width, int height, int nr_channels, unsigned char* raw_data);

	private:
		unsigned int texture_handle_;
	};
}