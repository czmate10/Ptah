#pragma once
#include "Events/Event.h"

namespace Ptah
{
	/**
	 * Will be called everytime the game updates
	 */
	class EventRender : public Event
	{
	public:
		EventRender(double time) : Event("render")
		{
			time_ = time;
		}

		double time_;
	};
}