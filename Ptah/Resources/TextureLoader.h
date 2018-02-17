#pragma once
#include <string>
#include "Render/Texture.h"

namespace Ptah
{
	class Texture;

	class TextureLoader {
	public:
		static Texture* Load(TextureType type, std::string path);
	};
}