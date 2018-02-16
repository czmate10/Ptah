#include "Components/MeshComponent.h"
#include "Engine.h"
#include "Render/Renderer.h"
#include "Entities/Entity.h"

Ptah::MeshComponent::MeshComponent() : Component()
{
	this->AddEventListener("pre_render", std::bind(&Ptah::MeshComponent::PreRender, this, std::placeholders::_1));
}

Ptah::MeshComponent::~MeshComponent()
{

}

void Ptah::MeshComponent::AddMesh(Ptah::Mesh *mesh)
{
	meshes_.push_back(mesh);
}

void Ptah::MeshComponent::PreRender(Event* ev)
{
	for(unsigned int i = 0; i < meshes_.size(); ++i)
	{
		auto mesh = meshes_[i];

		RenderCommandMesh cmd = {};
		cmd.mesh = mesh;
		cmd.material = material_;
		cmd.transform = parent_->GetTransform()->GetTransformMatrix();

		Engine::Instance().GetRenderer()->AddMesh(cmd);
	}
}