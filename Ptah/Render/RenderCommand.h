#pragma once
#include "glm/glm.hpp"

namespace Ptah
{
	class Mesh;
	class Material;

	struct RenderCommand
	{
		glm::mat4 transform;
		Material* mat;
		Mesh* mesh;
	};
}