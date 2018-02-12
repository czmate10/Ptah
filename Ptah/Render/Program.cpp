#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <glm/detail/type_mat.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/detail/type_mat2x2.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Program.h"

Ptah::Program::Program()
{
	program_handle_ = glCreateProgram();
	if(program_handle_ == 0)
		throw std::runtime_error("unable to create program");
}

Ptah::Program::~Program()
{
	if(program_handle_ == 0)
		return;

	GLint shader_count = 0;
	glGetProgramiv(program_handle_, GL_ATTACHED_SHADERS, &shader_count);

	GLuint* shaders = new GLuint[shader_count];
	glGetAttachedShaders(program_handle_, shader_count, nullptr, shaders);

	for(int i = 0; i < shader_count; i++)
	{
		std::cout << "Removing shader #" << i << " handle ID: " << shaders[i] << std::endl;
		glDeleteShader(shaders[i]);
	}

	glDeleteProgram(program_handle_);
	delete[] shaders;
}


void Ptah::Program::Link()
{
	if(linked_)
		return;
	if(program_handle_ == 0)
		throw std::runtime_error("program not compiled yet!");

	glLinkProgram(program_handle_);
	GLint linked = 0;
	glGetProgramiv(program_handle_, GL_LINK_STATUS, &linked);
	if(linked == GL_FALSE)
	{
		std::cout << GetInfoLog();
		throw std::runtime_error("program failed to link: " + GetInfoLog());
	}
	else
		linked_ = true;

	// Get attributes and uniforms and store them
	int attributes_count = 0, uniforms_count = 0;
	glGetProgramiv(program_handle_, GL_ACTIVE_ATTRIBUTES, &attributes_count);
	glGetProgramiv(program_handle_, GL_ACTIVE_UNIFORMS, &uniforms_count);
	attributes_.resize(attributes_count);
	uniforms_.resize(uniforms_count);

	char buffer[128];
	for(int i = 0; i < attributes_count; i++)
	{
		glGetActiveAttrib(program_handle_, i, 128, nullptr, &attributes_[i].size, &attributes_[i].type, buffer);
		attributes_[i].name = std::string(buffer);
		attributes_[i].location = glGetAttribLocation(program_handle_, buffer);
	}

	for(int i = 0; i < uniforms_count; i++)
	{
		glGetActiveUniform(program_handle_, i, 128, nullptr, &uniforms_[i].size, &uniforms_[i].type, buffer);
		uniforms_[i].name = std::string(buffer);
		uniforms_[i].location = glGetUniformLocation(program_handle_, buffer);

	}
}

void Ptah::Program::Validate()
{
	if(!linked_)
		throw std::runtime_error("program not linked yet!");

	glValidateProgram(program_handle_);
	GLint validated = 0;
	glGetProgramiv(program_handle_, GL_VALIDATE_STATUS, &validated);

	if(validated == GL_FALSE)
	{
		throw std::runtime_error("program failed to validate: " + GetInfoLog());
	}
}

void Ptah::Program::Use()
{
	if(!linked_ || program_handle_ == 0)
		throw std::runtime_error("program isn't linked !!!");

	glUseProgram(program_handle_);
}

/*enum shader_type : unsigned int
	{
		VERTEX = GL_VERTEX_SHADER,
		FRAGMENT = GL_FRAGMENT_SHADER,
		GEOMETRY = GL_GEOMETRY_SHADER,
		TESS_CONTROL = GL_TESS_CONTROL_SHADER,
		TESS_EVALUATION = GL_TESS_EVALUATION_SHADER,
		COMPUTE = GL_COMPUTE_SHADER
	};*/

void Ptah::Program::AddShader(std::string shader_src, Ptah::ShaderType type)
{
	unsigned int GL_type = 0;
	switch(type) {
		case Ptah::ShaderType::VERTEX: GL_type = GL_VERTEX_SHADER; break;
		case Ptah::ShaderType::FRAGMENT: GL_type = GL_FRAGMENT_SHADER; break; 
		case Ptah::ShaderType::GEOMETRY: GL_type = GL_GEOMETRY_SHADER; break;
		case Ptah::ShaderType::TESS_CONTROL: GL_type = GL_TESS_CONTROL_SHADER; break;
		case Ptah::ShaderType::TESS_EVALUATION: GL_type = GL_TESS_EVALUATION_SHADER; break;
		case Ptah::ShaderType::COMPUTE: GL_type = GL_COMPUTE_SHADER; break;
		default: throw std::runtime_error("Unknown shader type!"); break;
	}
	assert(GL_type);

	const char* src = shader_src.c_str();
	GLuint shader_handle_ = glCreateShader(GL_type);
	glShaderSource(shader_handle_, 1, &src, nullptr);
	glCompileShader(shader_handle_);

	int compiled;
	glGetShaderiv( shader_handle_, GL_COMPILE_STATUS, &compiled );
	if(compiled == GL_FALSE)
	{
		GLint log_length = 0;
		std::string log_str;
		glGetShaderiv(shader_handle_, GL_INFO_LOG_LENGTH, &log_length);

		if(log_length > 0)
		{
			char* log = new char[log_length];
			glGetShaderInfoLog(shader_handle_, log_length, nullptr, log);
			log_str = std::string(log);
			delete[] log;
		}

		throw std::runtime_error(std::string("failed to compile shader, error:\n") + log_str);
	}
	else
		glAttachShader(program_handle_, shader_handle_);
}

GLint Ptah::Program::GetAttribLocation(std::string name)
{
	for(auto i = attributes_.begin(); i != attributes_.end(); ++i)
	{
		if(name == i->name)
		{
			return i->location;
		}
	}
	return -1;
}

GLint Ptah::Program::GetUniformLocation(std::string name)
{
	for(auto i = uniforms_.begin(); i != uniforms_.end(); ++i)
	{
		if(name == i->name)
		{
			return i->location;
		}
	}
	return -1;
}

void Ptah::Program::SetInt(std::string location, int value)
{
	auto loc = GetUniformLocation(location);
	if(loc >= 0)
		glUniform1i(loc, value);
}

void Ptah::Program::SetFloat(std::string location, float value)
{
	auto loc = GetUniformLocation(location);
	if(loc >= 0)
		glUniform1f(loc, value);
}

void Ptah::Program::SetVector2(std::string location, glm::vec2 const & value)
{
	auto loc = GetUniformLocation(location);
	if(loc >= 0)
		glUniform2fv(loc, 1, glm::value_ptr(value));
}

void Ptah::Program::SetVector3(std::string location, glm::vec3 const & value)
{
	auto loc = GetUniformLocation(location);
	if(loc >= 0)
		glUniform3fv(loc, 1, glm::value_ptr(value));

}

void Ptah::Program::SetVector4(std::string location, glm::vec4 const & value)
{
	auto loc = GetUniformLocation(location);
	if(loc >= 0)
		glUniform4fv(loc, 1, glm::value_ptr(value));
}

void Ptah::Program::SetMatrix2(std::string location, glm::mat2 const & value)
{
	auto loc = GetUniformLocation(location);
	if(loc >= 0)
		glUniformMatrix2fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}

void Ptah::Program::SetMatrix3(std::string location, glm::mat3 const & value)
{
	auto loc = GetUniformLocation(location);
	if(loc >= 0)
		glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}

void Ptah::Program::SetMatrix4(std::string location, glm::mat4 const & value)
{
	auto loc =  GetUniformLocation(location);
	if(loc >= 0)
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}

std::string Ptah::Program::GetInfoLog()
{
	GLint log_length = 0;
	std::string log_str;
	glGetProgramiv(program_handle_, GL_INFO_LOG_LENGTH, &log_length);

	if(log_length > 0)
	{
		char* log = new char[log_length];
		glGetProgramInfoLog(program_handle_, log_length, nullptr, log);
		log_str = std::string(log);
		delete[] log;
	}

	return log_str;
}