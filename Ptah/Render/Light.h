#pragma once

namespace Ptah
{
	enum LightType
	{
		// Ambient light with no position or direction, useful to simulate light in very dark places
		AMBIENT,

		// Directional light with a given direction but no given point in space, useful for sun
		DIRECTIONAL,

		// Pointlight with position but no direction, emits light in all directions
		POINT,

		// Spotlight with a position and a direction, emits light in a given direciton
		SPOT
	};
}