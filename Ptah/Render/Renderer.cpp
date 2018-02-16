#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"
#include "Engine.h"
#include "Window.h"
#include "Render/Program.h"
#include "Events/Event.h"
#include "Events/EventTypes/EventPreRender.h"
#include "Events/EventTypes/EventRender.h"
#include "Resources/Resources.h"
#include "Mesh/Mesh.h"
#include "Components/CameraComponent.h"


Ptah::Renderer::Renderer()
{

}

void Ptah::Renderer::Render(double dt)
{
	// Call pre-render event, mesh components use this to push render commands
	Engine::Instance().GetEventDispatcher()->DispatchEvent(new EventPreRender(dt));


	// Clear the screen
	glClearColor(0.07f, 0.07f, 0.07f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	// TODO: remove this from here
	auto prog = Resources::GetProgram("default");
	prog->Use();

	// Camera stuff
	// TODO: we should only update view and projection matrix when they change
	auto camera = Engine::Instance().GetCamera();
	assert(camera);
	camera->UpdateView();
	prog->SetMatrix4("view", camera->GetViewMatrix());
	prog->SetMatrix4("projection", camera->GetProjectionMatrix());


	// Draw meshes
	for(unsigned int i = 0; i < render_commands_meshes_.size(); ++i)
	{
		prog->SetMatrix4("model", render_commands_meshes_[i].transform);
		RenderMesh(render_commands_meshes_[i].mesh);
	}

	ClearRenderCommands();
}

void Ptah::Renderer::RenderMesh(Mesh* mesh_ptr)
{
	glBindVertexArray(mesh_ptr->GetVao());
	if(!mesh_ptr->triangles_.empty())
		glDrawElements(GL_TRIANGLES, mesh_ptr->triangles_.size(), GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, mesh_ptr->vertices_.size());
}

void Ptah::Renderer::AddMesh(RenderCommandMesh cmd)
{
	render_commands_meshes_.push_back(cmd);
}

void Ptah::Renderer::AddLight(RenderCommandLight cmd)
{
	render_commands_lights_.push_back(cmd);
}

void Ptah::Renderer::ClearRenderCommands()
{
	render_commands_meshes_.clear();
	render_commands_lights_.clear();
}
