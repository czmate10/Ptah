#pragma once
#include "Events/Event.h"

namespace Ptah
{
	/**
	 * Will be called when the user scrolls their mouse wheel
	 */
	class EventMouseScrolled : public Event
	{
	public:
		EventMouseScrolled(double offset_x, double offset_y) : Event("mouse_scrolled")
		{
			offset_x_ = offset_x;
			offset_y_ = offset_y;
		}

		double offset_x_;
		double offset_y_;
	};
}