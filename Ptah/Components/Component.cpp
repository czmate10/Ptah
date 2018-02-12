#include "Components/Component.h"
#include "Engine.h"
#include "Events/Event.h"
#include "Events/EventDispatcher.h"

Ptah::Component::Component()
{
}

Ptah::Component::~Component()
{
	for (auto it = listeners_.begin(); it != listeners_.end(); it++)
	{
		if (*it == nullptr)
			continue;

		Engine::Instance().GetEventDispatcher()->RemoveEventListener(*it);
	}
}

void Ptah::Component::AddEventListener(const char* name, std::function<void(Ptah::Event*)> callback)
{
	listeners_.push_back(Engine::Instance().GetEventDispatcher()->AddEventListener(name, callback));
}
