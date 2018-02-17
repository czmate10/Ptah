#include "Resources/Resources.h"
#include "Resources/ProgramLoader.h"
#include "Resources/TextureLoader.h"
#include "Logger.h"

const std::string Ptah::Resources::PATH_SHADERS = "resources/shaders/";
const std::string Ptah::Resources::PATH_TEXTURES = "resources/textures/";

std::map<std::string, Ptah::Program*> Ptah::Resources::programs_ = std::map<std::string, Ptah::Program*>();
std::map<std::string, Ptah::Texture*> Ptah::Resources::textures_ = std::map<std::string, Ptah::Texture*>();




void Ptah::Resources::LoadCommon()
{
	Logger::Debug("Loading common resources");

	// Shaders
	LoadProgram("default", "default.vs", "default.fs");

	// Textures
	LoadTexture("test_uv", TextureType::TEXTURE_2D, "test_uv.png");
	/*LoadTexture("bricks", TextureType::TEXTURE_2D, "bricks.jpg");
	LoadTexture("bricks_disp", TextureType::TEXTURE_2D, "bricks_disp.jpg");
	LoadTexture("bricks_normal", TextureType::TEXTURE_2D, "bricks_normal.jpg");*/
}

Ptah::Program* Ptah::Resources::LoadProgram(std::string id, std::string vertex_shader_path, std::string fragment_shader_path)
{
	auto prog = ProgramLoader::Load(std::move(vertex_shader_path), std::move(fragment_shader_path));
	programs_.insert(std::make_pair(id, prog));

	return programs_.at(id);
}

Ptah::Program* Ptah::Resources::GetProgram(std::string id)
{
	return programs_.at(id);
}

Ptah::Texture* Ptah::Resources::LoadTexture(std::string id, TextureType type, std::string path)
{
	auto tex = TextureLoader::Load(type, path);
	textures_.insert(std::make_pair(id, tex));

	return tex;
}

Ptah::Texture* Ptah::Resources::GetTexture(std::string id)
{
	return textures_.at(id);
}
