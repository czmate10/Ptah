#include <iostream>
#include <sstream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Engine.h"
#include "Render/Renderer.h"
#include "Render/Program.h"
#include "Events/Event.h"
#include "Events/EventDispatcher.h"
#include "Events/EventTypes/EventTick.h"
#include "Events/EventTypes/EventRender.h"
#include "Components/CameraComponent.h"
#include "Resources/Resources.h"
#include "Events/EventTypes/EventEntityCreated.h"


Ptah::Engine Ptah::Engine::instance_;

Ptah::Engine::Engine() : window_(new Ptah::Window()), renderer_(new Ptah::Renderer()), event_dispatcher_(new Ptah::EventDispatcher())
{
	renderer_->AttachWindow(window_);
}

Ptah::Engine::~Engine()
{
	delete window_;
	delete renderer_;
	delete event_dispatcher_;
}

Ptah::Engine& Ptah::Engine::Instance()
{
	return instance_;
}

void Ptah::Engine::Init()
{
	glfwInit();

	window_->Create();
	window_->MakeCurrent();

	glewExperimental = GL_TRUE;
	glewInit();

	Ptah::Resources::LoadCommon();
}

void Ptah::Engine::Shutdown()
{
	glfwTerminate();
	window_->Close();
}

void Ptah::Engine::StartLoop()
{
	double fps_last_check = glfwGetTime();
	unsigned int fps_count = 0;
	double previous_clock = glfwGetTime();
	double lag = 0.0;
	while (!window_->ShouldClose())
	{
		const double current_clock = glfwGetTime();
		const double elapsed_clock = current_clock - previous_clock;
		previous_clock = current_clock;
		lag += elapsed_clock;

		// poll events
		glfwPollEvents();

		while(lag >= MS_PER_UPDATE)
		{
			// update
			event_dispatcher_->DispatchEvent(new EventTick(current_clock));
			lag -= MS_PER_UPDATE;
		}

		// render
		renderer_->Render(lag / MS_PER_UPDATE);

		fps_count++;
		if(current_clock - fps_last_check > 1.0)
		{
			fps_last_check = current_clock;
			std::ostringstream fps_string;
			fps_string << "FPS: " << fps_count;

			window_->SetTitle(fps_string.str().c_str());
			fps_count = 0;
		}
	}
}

void Ptah::Engine::SetWindowTitle(const char* title)
{
	window_->SetTitle(title);
}