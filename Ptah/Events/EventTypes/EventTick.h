#pragma once
#include "Events/Event.h"

namespace Ptah
{
	/**
	 * Will be called everytime the game updates
	 */
	class EventTick : public Event
	{
	public:
		EventTick(double time_) : Event("tick")
		{
			time = time_;
		}

		double time;
	};
}