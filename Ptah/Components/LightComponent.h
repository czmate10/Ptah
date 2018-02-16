#pragma once
#include <glm/detail/type_vec3.hpp>
#include "Components/Component.h"
#include "Render/Light.h"

namespace Ptah
{
	class LightComponent : public Component
	{
	public:
		LightComponent(LightType type, glm::vec3 color);

		~LightComponent();

		void OnParentAdded()
		{}

		LightComponent* Clone()
		{
			return new LightComponent(type_, color_);
		}

		/**
		 * Registers light to be rendered by the global renderer
		 * Should be called by event-system only
		 */
		void PreRender(Event* ev);

	private:
		LightType type_;
		glm::vec3 color_;
	};
}
