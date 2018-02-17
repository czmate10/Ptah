#pragma once
#include "Events/Event.h"

namespace Ptah
{
	/**
	 * Will be called everytime the game updates
	 */
	class EventPreRender : public Event
	{
	public:
		EventPreRender(double time_) : Event("pre_render")
		{
			time = time_;
		}

		double time;
	};
}