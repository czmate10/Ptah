#include "Render/Mesh/Plane.h"

Ptah::Plane::Plane() {
	vertices_ = std::vector<glm::vec3> {
			glm::vec3( 0.5f,  0.0f,  0.5f),
			glm::vec3(-0.5f,  0.0f,  0.5f),
			glm::vec3(-0.5f,  0.0f, -0.5f),
			glm::vec3( 0.5f,  0.0f,  0.5f),
			glm::vec3(-0.5f,  0.0f, -0.5f),
			glm::vec3( 0.5f,  0.0f, -0.5f),

	};
	normals_ = std::vector<glm::vec3>{
			glm::vec3( 0.0f,  1.0f,  0.0f),
			glm::vec3( 0.0f,  1.0f,  0.0f),
			glm::vec3( 0.0f,  1.0f,  0.0f),
			glm::vec3( 0.0f,  1.0f,  0.0f),
			glm::vec3( 0.0f,  1.0f,  0.0f),
			glm::vec3( 0.0f,  1.0f,  0.0f),
	};
	uvs_ = std::vector<glm::vec2> {
			glm::vec2(1.0f, 0.0f),
			glm::vec2(0.0f, 0.0f),
			glm::vec2(0.0f, 1.0f),
			glm::vec2(1.0f, 0.0f),
			glm::vec2(0.0f, 1.0f),
			glm::vec2(1.0f, 1.0f),
	};

	this->Finalize();
}
