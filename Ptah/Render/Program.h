#pragma once
#include <vector>
#include <iostream>
#include "glm/glm.hpp"

namespace Ptah {
	enum ShaderType : unsigned int
	{
		VERTEX,
		FRAGMENT,
		GEOMETRY,
		TESS_CONTROL,
		TESS_EVALUATION,
		COMPUTE
	};

	struct GLUniform
	{
		int location;
		std::string name;
		unsigned int type;
		int size;
	};

	struct GLAttribute
	{
		int location;
		std::string name;
		unsigned int type;
		int size;
	};

	class Program {
	public:
		Program();
		~Program();

		/**
		 * glLinkProgram
		 */
		void Link();

		/**
		 * glValidateProgram
		 */
		void Validate();

		/**
		 * glUseProgram
		 */
		void Use();

		/**
		 * Loads the shader with the given type and inserts it to the program
		 * @param shader_src source of the shader
		 * @param type type of the shader
		 */
		void AddShader(std::string shader_src, ShaderType type);


		int GetAttribLocation(std::string name);

		/**
		 * glGetUniformLocation
		 * @param name Points to a null terminated string containing the name of the uniform variable whose location is to be queried.
		 * @return location of the requested uniform variable
		 */
		int GetUniformLocation(std::string name);

		void SetInt(std::string, int value);
		void SetFloat(std::string, float value);

		void SetVector2(std::string, glm::vec2 const & value);
		void SetVector3(std::string, glm::vec3 const & value);
		void SetVector4(std::string, glm::vec4 const & value);

		void SetMatrix2(std::string, glm::mat2 const & value);
		void SetMatrix3(std::string, glm::mat3 const & value);
		void SetMatrix4(std::string, glm::mat4 const & value);

	private:
		unsigned int program_handle_ = 0;
		bool linked_ = false;

		std::vector<Ptah::GLAttribute> attributes_;
		std::vector<Ptah::GLUniform> uniforms_;

		/**
		 * Get info log for errors, etc.
		 * @return info log describing the error
		 */
		std::string GetInfoLog();
	};
}