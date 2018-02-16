#include "Components/LightComponent.h"
#include "Entities/Entity.h"
#include "Render/RenderCommand.h"

Ptah::LightComponent::LightComponent(LightType type, glm::vec3 color) : Component(), type_(type), color_(color)
{
	this->AddEventListener("pre_render", std::bind(&Ptah::LightComponent::PreRender, this, std::placeholders::_1));
}

Ptah::LightComponent::~LightComponent()
{

}

void Ptah::LightComponent::PreRender(Event* ev)
{
	RenderCommandLight cmd = {};
	cmd.type = type_;
	cmd.color = color_;
	cmd.position = parent_->GetTransform()->GetTransformMatrix();
	cmd.direction = parent_->GetTransform()->GetRotation();
}