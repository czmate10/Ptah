#pragma once

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
		std::string Id;
		std::string Path;
		TextureType Type;

		Texture(std::string id, TextureType type, std::string path = "generated") : Id(id), Type(type), Path(path)
		{
		}
	};
}