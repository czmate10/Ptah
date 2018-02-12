#include <GL/glew.h>
#include "Render/Material.h"
#include "Render/Program.h"
#include "Render/Texture.h"

Ptah::Material::Material(Program* program)
{
	program_ = program;	
}

Ptah::Program* Ptah::Material::GetProgram()
{
	return program_;
}

void Ptah::Material::SetBool(std::string name, bool value)
{
	uniforms_[name].Type = GL_BOOL;
	uniforms_[name].Bool = value;
}

void Ptah::Material::SetInt(std::string name, int value)
{
	uniforms_[name].Type = GL_INT;
	uniforms_[name].Int = value;
}

void Ptah::Material::SetFloat(std::string name, float value)
{
	uniforms_[name].Type = GL_BOOL;
	uniforms_[name].Float = value;
}

void Ptah::Material::SetTexture(std::string name, Texture* value, unsigned int texture_unit)
{
	// The texture object should hold the corresponding value type (1D, 2D, etc.)
	uniforms_[name].Type = value->Type;
	uniforms_[name].TextureUnit = texture_unit;
	uniforms_[name].Texture = value;

	program_->Use();
	program_->SetInt(name, texture_unit); // Let OpenGL know which texture unit our texture resides in
}

void Ptah::Material::SetVector2(std::string name, glm::vec2 const & value)
{
	uniforms_[name].Type = GL_FLOAT_VEC2;
	uniforms_[name].Vector2 = value;
}

void Ptah::Material::SetVector3(std::string name, glm::vec3 const & value)
{
	uniforms_[name].Type = GL_FLOAT_VEC3;
	uniforms_[name].Vector3 = value;
}

void Ptah::Material::SetVector4(std::string name, glm::vec4 const & value)
{
	uniforms_[name].Type = GL_FLOAT_VEC4;
	uniforms_[name].Vector4 = value;
}

void Ptah::Material::SetMatrix2(std::string name, glm::mat2 const & value)
{
	uniforms_[name].Type = GL_FLOAT_MAT2;
	uniforms_[name].Matrix2 = value;
}

void Ptah::Material::SetMatrix3(std::string name, glm::mat3 const & value)
{
	uniforms_[name].Type = GL_FLOAT_MAT3;
	uniforms_[name].Matrix3 = value;
}

void Ptah::Material::SetMatrix4(std::string name, glm::mat4 const & value)
{
	uniforms_[name].Type = GL_FLOAT_MAT4;
	uniforms_[name].Matrix4 = value;
}

bool Ptah::Material::GetBool(std::string name)
{
	return uniforms_[name].Bool;
}

int Ptah::Material::GetInt(std::string name)
{
	return uniforms_[name].Int;
}

float Ptah::Material::GetFloat(std::string name)
{
	return uniforms_[name].Float;
}

Ptah::Texture* Ptah::Material::GetTexture(std::string name)
{
	return uniforms_[name].Texture;
}

glm::vec2 Ptah::Material::GetVector2(std::string name)
{
	return uniforms_[name].Vector2;
}

glm::vec3 Ptah::Material::GetVector3(std::string name)
{
	return uniforms_[name].Vector3;
}

glm::vec4 Ptah::Material::GetVector4(std::string name)
{
	return uniforms_[name].Vector4;
}

glm::mat2 Ptah::Material::GetMatrix2(std::string name)
{
	return uniforms_[name].Matrix2;
}

glm::mat3 Ptah::Material::GetMatrix3(std::string name)
{
	return uniforms_[name].Matrix3;
}

glm::mat4 Ptah::Material::GetMatrix4(std::string name)
{
	return uniforms_[name].Matrix4;
}
