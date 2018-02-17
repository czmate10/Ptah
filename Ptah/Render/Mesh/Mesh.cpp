#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Render/Mesh/Mesh.h"

Ptah::Mesh::~Mesh()
{
	if(vao_ != 0)
	{
		glDeleteVertexArrays(1, &vao_);
		glDeleteBuffers(1, &vbo_);
	}
	if(ebo_ != 0)
	{
		glDeleteBuffers(1, &ebo_);
	}
}

void Ptah::Mesh::Finalize()
{
	if(vao_ == 0)
	{
		glGenVertexArrays(1, &vao_);
		glGenBuffers(1, &vbo_);
		glGenBuffers(1, &ebo_);
	}

	std::vector<float> raw_data;

	for(auto it = vertices_.begin(); it != vertices_.end(); ++it)
	{
		raw_data.push_back(it->x);
		raw_data.push_back(it->y);
		raw_data.push_back(it->z);
	}
	for(auto it = normals_.begin(); it != normals_.end(); ++it)
	{
		raw_data.push_back(it->x);
		raw_data.push_back(it->y);
		raw_data.push_back(it->z);
	}
	for(auto it = uvs_.begin(); it != uvs_.end(); ++it)
	{
		raw_data.push_back(it->x);
		raw_data.push_back(it->y);
	}

	glBindVertexArray(vao_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, raw_data.size() * sizeof(float), &raw_data[0], GL_STATIC_DRAW);

	// specify the data
	size_t at = 0;

	// vertices
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)at);
	at += vertices_.size() * sizeof(float) * 3;

	// normals
	if(!normals_.empty())
	{
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)at);
		at += normals_.size() * sizeof(float) * 3;
	}

	// uvs
	if(!uvs_.empty())
	{
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)at);
		at += uvs_.size() * sizeof(float) * 2;
	}

	// triangles
	if(!triangles_.empty())
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles_.size() * sizeof(unsigned int), &triangles_[0], GL_STATIC_DRAW);
	}

	glBindVertexArray(0);
}
