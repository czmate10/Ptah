#include "Quad.h"

Ptah::Quad::Quad()
{
	vertices_ = std::vector<glm::vec3> {
		glm::vec3(-1.0f,  1.0f,  0.0f),
		glm::vec3(-1.0f, -1.0f,  0.0f),
		glm::vec3( 1.0f,  1.0f,  0.0f),
		glm::vec3( 1.0f, -1.0f,  0.0f),
	};

	uvs_ = std::vector<glm::vec2> {
		glm::vec2(0.0f, 1.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(1.0f, 0.0f),
	};
}