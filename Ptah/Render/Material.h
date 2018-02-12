#pragma once
#include <map>
#include <glm/glm.hpp>

namespace Ptah
{
	class Program;
	class Texture;	

	/**
	 * Struct to hold data of uniforms
	 */
	struct MaterialUniform
	{
		MaterialUniform()
		{}

		// GLenum, value type
		unsigned int Type;

		// Only used in case of textures to know which OpenGL Texture Unit we want to use
		unsigned int TextureUnit = 0;
		
		// We only need one value, union holds memory of the biggest datamember only
		union
		{
			bool Bool;
			int Int;
			float Float;
			Texture* Texture;
			glm::vec2 Vector2;
			glm::vec3 Vector3;
			glm::vec4 Vector4;
			glm::mat2 Matrix2;
			glm::mat3 Matrix3;
			glm::mat4 Matrix4;
		};
	};

	/**
	 * Material class, used by the renderer to know which shader program, textures and shader uniforms to use
	 */
	class Material {
	public:
		Material(Program* program);

		Program* GetProgram();

		// Setters
		void SetBool(std::string name, bool value);
		void SetInt(std::string name, int value);
		void SetFloat(std::string name, float value);
		void SetTexture(std::string name, Texture* value, unsigned int texture_unit);
		void SetVector2(std::string name, glm::vec2 const & value);
		void SetVector3(std::string name, glm::vec3 const & value);
		void SetVector4(std::string name, glm::vec4 const & value);
		void SetMatrix2(std::string name, glm::mat2 const & value);
		void SetMatrix3(std::string name, glm::mat3 const & value);
		void SetMatrix4(std::string name, glm::mat4 const & value);
		
		// Getters
		bool GetBool(std::string name);
		int GetInt(std::string name);
		float GetFloat(std::string name);
		Texture* GetTexture(std::string name);
		glm::vec2 GetVector2(std::string name);
		glm::vec3 GetVector3(std::string name);
		glm::vec4 GetVector4(std::string name);
		glm::mat2 GetMatrix2(std::string name);
		glm::mat3 GetMatrix3(std::string name);
		glm::mat4 GetMatrix4(std::string name);

	private:
		Program* program_;
		std::map<std::string, MaterialUniform> uniforms_;
	};
}