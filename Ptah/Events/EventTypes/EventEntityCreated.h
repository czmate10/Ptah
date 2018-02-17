#pragma once
#include "Events/Event.h"

namespace Ptah
{
	class Entity;

	/**
	 * Will be called everytime the game updates
	 */
	class EventEntityCreated : public Event
	{
	public:
		EventEntityCreated(Entity* entity_) : Event("entity_created"), entity(entity_)
		{
		}

		Entity* entity;
	};
}