#pragma once
#include "Render/Mesh/Mesh.h"

namespace Ptah
{
	class Sphere : public Mesh {
	public:
		Sphere(unsigned int segments_x = 16, unsigned int segments_y = 16);
	};
}