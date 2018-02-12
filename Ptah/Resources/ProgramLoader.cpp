#include <sstream>
#include <fstream>
#include "ProgramLoader.h"
#include "Render/Program.h"

// TODO: if file doesn't exist, use the log system. (once there's one)
Ptah::Program* Ptah::ProgramLoader::Load(std::string vertex_shader_path, std::string fragment_shader_path)
{
	auto prog = new Ptah::Program();

	// Add vertex shader
	std::ifstream file_vertex(vertex_shader_path);
	assert(file_vertex.good());
	std::stringstream buffer_vertex;
	buffer_vertex << file_vertex.rdbuf();
	prog->AddShader(buffer_vertex.str(), Ptah::ShaderType::VERTEX);

	// Add fragment shader
	std::ifstream file_fragment(fragment_shader_path);
	assert(file_fragment.good());
	std::stringstream buffer_fragment;
	buffer_fragment << file_fragment.rdbuf();
	prog->AddShader(buffer_fragment.str(), Ptah::ShaderType::FRAGMENT);

	prog->Link();
	prog->Validate();
	prog->Use();

	return prog;
}
