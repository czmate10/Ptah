#include "Components/CameraComponent.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Engine.h"
#include "TransformComponent.h"
#include "Render/Program.h"
#include "Entities/Entity.h"
#include "Events/EventTypes/EventTick.h"

Ptah::CameraComponent::CameraComponent() : type(camera_type::PERSPECTIVE)
{
	// Setup projection with default values
	this->UpdateProjection(type, fov, aspect, near, far);
}

void Ptah::CameraComponent::UpdateView()
{
	auto transform = GetParent()->GetTransform();
	view_ = glm::lookAt(transform->GetPos(), transform->GetPos() + transform->GetFront(), transform->GetUp());
}

void Ptah::CameraComponent::UpdateProjection(Ptah::camera_type type, float fov, float aspect, float near, float far)
{
	this->type = type;
	this->fov = fov;
	this->aspect = aspect;
	this->near = near;
	this->far = far;

	projection_ = glm::perspective(glm::radians(fov), aspect, near, far);
}

Ptah::Component *Ptah::CameraComponent::Clone()
{
	auto new_camera = new CameraComponent();
	new_camera->UpdateProjection(type, fov, aspect, near, far);
	return new_camera;
}

void Ptah::CameraComponent::SetActive()
{
	Engine::Instance().SetCamera(this);
}
