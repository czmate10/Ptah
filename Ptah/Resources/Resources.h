#pragma once
#include <map>
#include <string>
#include "Render/Texture.h"

namespace Ptah
{
	class Program;
	class Texture;

	// Static class for storing and retrieving resources from the hard-drive
	class Resources {
	public:
		static const std::string PATH_SHADERS;
		static const std::string PATH_TEXTURES;

		/**
		 * Loads common resources
		 */
		static void LoadCommon();

		static Program* LoadProgram(std::string id, std::string vertex_shader_path, std::string fragment_shader_path);
		static Program* GetProgram(std::string id);

		static Texture* LoadTexture(std::string id, TextureType type, std::string path);
		static Texture* GetTexture(std::string id);

	protected:
		static std::map<std::string, Program*> programs_;
		static std::map<std::string, Texture*> textures_;

	private:
		Resources() = default;
	};
}