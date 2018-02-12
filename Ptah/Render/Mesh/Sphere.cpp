#define _USE_MATH_DEFINES
#include <cmath>
#include "Render/Mesh/Sphere.h"


Ptah::Sphere::Sphere(unsigned int segments_x, unsigned int segments_y)
{
	for (unsigned int y = 0; y <= segments_y; y++)
	{
		auto seg_y = (float)y / (float)segments_y;
		auto pos_y = (float)std::cos(seg_y * M_PI);

		for (unsigned int x = 0; x <= segments_x; x++)
		{
			auto seg_x = (float)x / (float)segments_y;
			auto pos_x = (float)std::cos(seg_x * M_PI * 2.0f) * (float)std::sin(seg_y * M_PI);
			auto pos_z = (float)std::sin(seg_x * M_PI * 2.0f) * (float)std::sin(seg_y * M_PI);

			auto vec = glm::vec3(pos_x, pos_y, pos_z);
			vertices_.emplace_back(vec);
			uvs_.emplace_back(glm::vec2(seg_x, seg_y));
			normals_.emplace_back(vec);

			triangles_.emplace_back((y + 1) * (segments_x + 1) + x);
			triangles_.emplace_back(y * (segments_x + 1) + x);
			triangles_.emplace_back(y * (segments_x + 1) + x + 1);

			triangles_.emplace_back((y + 1) * (segments_x + 1) + x);
			triangles_.emplace_back(y * (segments_x + 1) + x + 1);
			triangles_.emplace_back((y + 1) * (segments_x + 1) + x + 1);
		}
	}

	this->Finalize();
}