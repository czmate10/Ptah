#pragma once
#include <string>

namespace Ptah
{
	class Program;

	/**
	 * Helper class to ease loading shaders
	 */
	class ProgramLoader {
	public:
		/**
		 * Sort of pre-compiler, replaces #includes with contents of the files, etc.
		 */
		static std::string FormatSource(std::string source);		

		/**
		 * Loads a shader program from a vertex and fragment shader source
		 */
		static Program* Load(std::string vertex_shader_path, std::string fragment_shader_path);
	};
}