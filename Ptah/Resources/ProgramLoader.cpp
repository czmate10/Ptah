#include "ProgramLoader.h"
#include "Engine.h"
#include "Render/Program.h"
#include "Resources.h"
#include "Logger.h"

std::string Ptah::ProgramLoader::FormatSource(std::string source)
{
	// Replace all #include
	size_t lastPlace = 0;
	while(true)
	{
		lastPlace = source.find("#include", lastPlace + 1);
		if(lastPlace == std::string::npos)
			break;

		auto fileNameSize = source.find("\n", lastPlace) - lastPlace - 9;
		auto fileName = source.substr(lastPlace + 9, fileNameSize);
		auto fileContent = Ptah::Engine::Instance().ReadFile(Ptah::Resources::PATH_SHADERS + fileName);
		fileContent = Ptah::ProgramLoader::FormatSource(fileContent);
		source.replace(lastPlace, 9 + fileNameSize, fileContent);

		std::cout << source << std::endl;
	}

	return source;
}

// TODO: if file doesn't exist, use the log system. (once there's one)
Ptah::Program* Ptah::ProgramLoader::Load(std::string vertex_shader_path, std::string fragment_shader_path)
{
	Logger::Debug("Loading shader [" + vertex_shader_path + "] and [" + fragment_shader_path + "]");
	auto prog = new Ptah::Program();

	// Add vertex shader
	auto vertex_source = Ptah::ProgramLoader::FormatSource(Ptah::Engine::Instance().ReadFile(Ptah::Resources::PATH_SHADERS + vertex_shader_path));
	prog->AddShader(FormatSource(vertex_source), Ptah::ShaderType::VERTEX);

	// Add fragment shader
	auto fragment_source = Ptah::ProgramLoader::FormatSource(Ptah::Engine::Instance().ReadFile(Ptah::Resources::PATH_SHADERS + fragment_shader_path));
	prog->AddShader(FormatSource(fragment_source), Ptah::ShaderType::FRAGMENT);

	prog->Link();
	prog->Validate();
	prog->Use();

	return prog;
}
