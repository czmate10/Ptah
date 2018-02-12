#include "Resources.h"
#include "ProgramLoader.h"
#include "Render/Texture.h"


std::map<std::string, Ptah::Program*> Ptah::Resources::programs_ = std::map<std::string, Ptah::Program*>();
std::map<std::string, Ptah::Texture*> Ptah::Resources::textures_ = std::map<std::string, Ptah::Texture*>();

void Ptah::Resources::LoadCommon()
{
	LoadProgram("default", "resources/shaders/default.vs", "resources/shaders/default.fs");
	LoadTexture("test_uv", "resources/textures/test_uv.png");
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

Ptah::Texture* Ptah::Resources::LoadTexture(std::string id, std::string path)
{
	return nullptr;
}

Ptah::Texture* Ptah::Resources::GetTexture(std::string id)
{
	return textures_.at(id);
}
