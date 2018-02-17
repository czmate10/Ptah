#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include "Components/Component.h"

namespace Ptah
{
	enum camera_type
	{
		PERSPECTIVE,
		ORTHOGRAPHIC
	};

	class CameraComponent : public Component {
	public:
		camera_type type = camera_type::PERSPECTIVE;
		float fov = 60.0f;
		float aspect = 800.0f/600.0f;
		float near = 0.3f;
		float far = 1000.0f;

		CameraComponent();
		Component* Clone();

		/**
		 * Updates view matrix
		 * Called on render event by global renderer
		 */
		void UpdateView();

		/**
		 * Returns the view matrix
		 */
		inline glm::mat4 GetViewMatrix()
		{
			return view_;
		}

		/**
		 * Returns the projection matrix
		 */
		inline glm::mat4 GetProjectionMatrix()
		{
			return projection_;
		}

		/**
		 * Updates projection matrix
		 */
		void UpdateProjection(Ptah::camera_type type, float fov, float aspect, float near, float far);

		/**
		 * Sets this camera component as active camera
		 */
		void SetActive();

	protected:
		glm::mat4 projection_;
		glm::mat4 view_;
	};
}