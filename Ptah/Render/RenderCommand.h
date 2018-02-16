#pragma once
#include "glm/glm.hpp"

namespace Ptah
{
	class Mesh;
	class Material;
	enum LightType;

	struct RenderCommandMesh
	{
		glm::mat4 transform;
		Material* material;
		Mesh* mesh;
	};

	struct RenderCommandLight
	{
		LightType type;
		glm::mat4 position;
		glm::vec3 direction;
		glm::vec3 color;
	};
}
