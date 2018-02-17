#include <iostream>

#include <GLFW/glfw3.h>

#include "Engine.h"
#include "Render/Mesh/Sphere.h"
#include "Render/Mesh/Cube.h"
#include "Components/MeshComponent.h"
#include "Components/CameraComponent.h"
#include "Events/EventTypes/EventTick.h"
#include "Events/EventTypes/EventKeyPressed.h"
#include "Events/EventTypes/EventCursorMoved.h"
#include "Render/Mesh/Quad.h"
#include "Components/LightComponent.h"

// Constants for quick calculations
const float PI_HALF = glm::pi<float>()/2;

// Constants to control movement speed
const float MOVE_SPEED = 0.05f;
const float MOUSE_SENS = 0.001f;

// Our camera object
Ptah::Entity* entity_camera;

// Variables for looking around
float mouse_last_x = -1;
float mouse_last_y = -1;
bool mouse_first = true;

// Camera rotation
void on_cursor_moved(Ptah::Event* ev_)
{
	auto ev = static_cast<Ptah::EventCursorMoved*>(ev_);
	float x = (float)ev->mouse_x;
	float y = (float)ev->mouse_y;

	float offset_x = (x - mouse_last_x) * MOUSE_SENS;
	float offset_y = (y - mouse_last_y) * MOUSE_SENS;
	mouse_last_x = x;
	mouse_last_y = y;

	// It's silly to solve it like this, but in a test application it should suffice
	if(mouse_first)
	{
		mouse_first = false;
		return;
	}

	auto rotation = entity_camera->GetTransform()->GetRotation();
	rotation.x += offset_x;
	rotation.y -= offset_y;

	if(rotation.y > PI_HALF)
		rotation.y = PI_HALF;
	else if(rotation.y < -PI_HALF)
		rotation.y = -PI_HALF;


	entity_camera->GetTransform()->SetRotation(rotation);
}

// Camera movement
void on_tick(Ptah::Event* ev_)
{
	auto ev = static_cast<Ptah::EventTick*>(ev_);
	auto timeF = (float)ev->time;
	auto transform = entity_camera->GetTransform();
	
	if(Ptah::Engine::Instance().GetWindow()->GetKey(GLFW_KEY_E) == GLFW_PRESS)
		transform->SetPos(transform->GetPos() + (transform->GetUp() * MOVE_SPEED * timeF));

	if(Ptah::Engine::Instance().GetWindow()->GetKey(GLFW_KEY_Q) == GLFW_PRESS)
		transform->SetPos(transform->GetPos() - (transform->GetUp() * MOVE_SPEED * timeF));
	
	if(Ptah::Engine::Instance().GetWindow()->GetKey(GLFW_KEY_W) == GLFW_PRESS)
		transform->SetPos(transform->GetPos() + (transform->GetFront() * MOVE_SPEED * timeF));
	
	if(Ptah::Engine::Instance().GetWindow()->GetKey(GLFW_KEY_S) == GLFW_PRESS)
		transform->SetPos(transform->GetPos() - (transform->GetFront() * MOVE_SPEED * timeF));

	if(Ptah::Engine::Instance().GetWindow()->GetKey(GLFW_KEY_D) == GLFW_PRESS)
		transform->SetPos(transform->GetPos() + (transform->GetRight() * MOVE_SPEED * timeF));

	if(Ptah::Engine::Instance().GetWindow()->GetKey(GLFW_KEY_A) == GLFW_PRESS)
		transform->SetPos(transform->GetPos() - (transform->GetRight() * MOVE_SPEED * timeF));
}

// Close window when user presses escape
void on_key_pressed(Ptah::Event* ev_)
{
	auto ev = static_cast<Ptah::EventKeyPressed*>(ev_);

	if(ev->key == GLFW_KEY_ESCAPE)
		Ptah::Engine::Instance().Shutdown();
}

void init()
{
	Ptah::Engine::Instance().Init();
	Ptah::Engine::Instance().SetWindowTitle("Testing Ptah OpenGL engine");
	
	Ptah::Engine::Instance().GetEventDispatcher()->AddEventListener("tick", &on_tick);
	Ptah::Engine::Instance().GetEventDispatcher()->AddEventListener("key_pressed", &on_key_pressed);
	Ptah::Engine::Instance().GetEventDispatcher()->AddEventListener("cursor_moved", &on_cursor_moved);

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
		auto entity_sphere = world.GetEntityManager().Add("test_sphere");
		entity_sphere->GetTransform()->SetPos(glm::vec3(-3.5f, 0.0f, 0.0f));
		auto mesh_comp = new Ptah::MeshComponent();
		entity_sphere->AddComponent<Ptah::MeshComponent>(mesh_comp);
		auto sphere = new Ptah::Sphere();
		mesh_comp->AddMesh(sphere);
	}

	// Light #1
	{
		auto entity_light = world.GetEntityManager().Add("test_light01");
		entity_light->GetTransform()->SetPos(glm::vec3(10.0f, 10.0f, 10.0f));
		auto light_comp = new Ptah::LightComponent(Ptah::LightType::POINT, glm::vec3(1.0f, 1.0f, 1.0f));
		entity_light->AddComponent<Ptah::LightComponent>(light_comp);
	}

	// Camera
	entity_camera = world.GetEntityManager().Add("player_camera");
	Ptah::CameraComponent* camera_comp = new Ptah::CameraComponent();
	camera_comp->SetActive();
	entity_camera->AddComponent<Ptah::CameraComponent>(camera_comp);
	entity_camera->GetTransform()->SetPos(glm::vec3(0.0f, 0.0f, 3.0f));
	entity_camera->GetTransform()->SetRotation(glm::vec3(-glm::pi<float>()/2.0f, 0.0f, 0.0f));

	Ptah::Engine::Instance().StartLoop();

	Ptah::Engine::Instance().Shutdown();
}

int main()
{
	init();
	return 0;
}
