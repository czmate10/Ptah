#pragma once
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "Components/Component.h"

namespace Ptah
{
	class TransformComponent : public Component
	{
		friend class Entity;
	public:
		static const char* name;

		~TransformComponent();

		TransformComponent* Clone();

		/**
		 * Returns the model matrix
		 */
		glm::mat4 GetTransformMatrix();

		glm::vec3 GetPos();

		glm::vec3 GetRotation();

		glm::vec3 GetScale();

		/**
		 * Sets rotation
		 * Uses degrees, and calculated radians from those.
		 * @param rotation_new rotation
		 */
		void SetRotation(glm::vec3 rotation_new);

		/**
		 * Sets position
		 * @param pos_new pos
		 */
		void SetPos(glm::vec3 pos_new);

		/**
		 * Sets scale
		 * @param scale_new scale
		 */
		void SetScale(glm::vec3 scale_new);

		/**
		 * Re-calculate transformation matrix
		 */
		void Recalculate();

	protected:
		glm::vec3 pos_;
		glm::vec3 rotation_;
		glm::vec3 scale_;
		glm::mat4 transform_;

	private:
		TransformComponent();
	};
}
