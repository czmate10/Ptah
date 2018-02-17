#include "Components/TransformComponent.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include <iostream>

const char* Ptah::TransformComponent::name = "Transform Component";

glm::mat4 Ptah::TransformComponent::GetTransformMatrix()
{
	return transform_;
}

glm::vec3 Ptah::TransformComponent::GetPos()
{
	return pos_;
}

glm::vec3 Ptah::TransformComponent::GetRotation()
{
	return rotation_;
}

glm::vec3 Ptah::TransformComponent::GetScale()
{
	return scale_;
}

void Ptah::TransformComponent::SetPos(glm::vec3 pos_new)
{
	pos_ = pos_new;
	Recalculate();
}

void Ptah::TransformComponent::SetRotation(glm::vec3 rotation_new)
{
	rotation_ = rotation_new;
	Recalculate();
}

void Ptah::TransformComponent::SetScale(glm::vec3 scale_new)
{
	scale_ = scale_new;
	Recalculate();
}

void Ptah::TransformComponent::Recalculate()
{
	// Calculate front
	glm::vec3 front;
	front.x = glm::cos(rotation_.y) * glm::cos(rotation_.x);
	front.y = glm::sin(rotation_.y);
	front.z = glm::cos(rotation_.y) * glm::sin(rotation_.x);
	front_ = glm::normalize(front);

	right_ = glm::normalize(glm::cross(front_, up_));


	transform_ = glm::mat4();

	transform_ = glm::translate(transform_, pos_);	
	
	transform_ = glm::rotate(transform_, rotation_.x, glm::vec3(1, 0, 0));
	transform_ = glm::rotate(transform_, rotation_.y, glm::vec3(0, 1, 0));
	transform_ = glm::rotate(transform_, rotation_.z, glm::vec3(0, 0, 1));
	
	transform_ = glm::scale(transform_, scale_);
}

Ptah::TransformComponent *Ptah::TransformComponent::Clone() {
	auto new_comp = new TransformComponent();
	new_comp->pos_ = pos_;
	new_comp->rotation_ = rotation_;
	new_comp->scale_ = scale_;
	new_comp->Recalculate();
	return new_comp;
}

Ptah::TransformComponent::TransformComponent() 
	: transform_(glm::mat4(1.0f))
	, pos_(glm::vec3(0.0f, 0.0f, 0.0f))
	, rotation_(glm::vec3(0.0f, 0.0f, 0.0f))
	, scale_(glm::vec3(1.0f, 1.0f, 1.0f))
	, up_(glm::vec3(0.0f, 1.0f, 0.0f))
{
}

Ptah::TransformComponent::~TransformComponent()
{
}
