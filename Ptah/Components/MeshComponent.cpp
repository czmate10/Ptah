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

void Ptah::MeshComponent::OnParentAdded()
{
	transform_ = parent_->GetTransform();
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

		// Set model matrix
		/*program_->set_matrix("model", transform_->get_transform_matrix());

		// Bind the VAO of the mesh
		glBindVertexArray(mesh->get_vao());

		if(!mesh->triangles_.empty())
			glDrawElements(GL_TRIANGLES, mesh->triangles_.size(), GL_UNSIGNED_INT, 0);
		else
			glDrawArrays(GL_TRIANGLES, 0, mesh->vertices_.size());*/

		Engine::Instance().GetRenderer()->PushRenderCommand(mesh, transform_->GetTransformMatrix());
	}
}