#pragma once

namespace Ptah
{
	class Program;

	/**
	 * Helper class to ease loading shaders
	 */
	class ProgramLoader {
	public:
		static Program* Load(std::string vertex_shader_path, std::string fragment_shader_path);
	};
}