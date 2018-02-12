#include <iostream>

#include "Engine.h"
#include "Render/Mesh/Sphere.h"
#include "Render/Mesh/Cube.h"
#include "Components/MeshComponent.h"
#include "Components/CameraComponent.h"
#include "Events/EventTypes/EventKeyPressed.h"
#include "Render/Mesh/Quad.h"


void on_key_pressed(Ptah::Event* ev_)
{
	auto ev = static_cast<Ptah::EventKeyPressed*>(ev_);
	std::cout << ev->key_ << std::endl;
}

void init()
{
	Ptah::Engine::Instance().Init();
	Ptah::Engine::Instance().SetWindowTitle("Testing Ptah OpenGL engine");

	Ptah::Engine::Instance().GetEventDispatcher()->AddEventListener("key_pressed", &on_key_pressed);

	Ptah::World world;
	Ptah::Engine::Instance().SetWorld(&world);

	// Cube
	{
		auto entity_cube = world.GetEntityManager().Add("test_cube");
		entity_cube->GetTransform()->SetPos(glm::vec3(0.0f, 0.0f, 0.0f));
		auto mesh_comp = new Ptah::MeshComponent();
		entity_cube->AddComponent<Ptah::MeshComponent>(mesh_comp);
		auto cube = new Ptah::Cube();
		mesh_comp->AddMesh(cube);
	}

	// Sphere
	{
		auto entity_sphere = world.GetEntityManager().Add("test_cube");
		entity_sphere->GetTransform()->SetPos(glm::vec3(-3.5f, 0.0f, 0.0f));
		auto mesh_comp = new Ptah::MeshComponent();
		entity_sphere->AddComponent<Ptah::MeshComponent>(mesh_comp);
		auto sphere = new Ptah::Sphere();
		mesh_comp->AddMesh(sphere);
	}

	// Camera
	auto entity_camera = world.GetEntityManager().Add("player_camera");
	auto camera_comp = new Ptah::CameraComponent();
	camera_comp->SetActive();
	entity_camera->AddComponent<Ptah::CameraComponent>(camera_comp);
	entity_camera->GetTransform()->SetPos(glm::vec3(5.0f, 5.0f, 5.0f));

	Ptah::Engine::Instance().StartLoop();

	Ptah::Engine::Instance().Shutdown();
}

int main()
{
	init();
	return 0;
}
