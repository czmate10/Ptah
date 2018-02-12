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
		EventEntityCreated(Entity* entity) : Event("entity_created"), entity_(entity)
		{
		}

		Entity* entity_;
	};
}