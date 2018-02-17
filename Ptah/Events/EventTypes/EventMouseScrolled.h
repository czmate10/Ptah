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
		EventMouseScrolled(double offset_x_, double offset_y_) : Event("mouse_scrolled")
		{
			offset_x = offset_x_;
			offset_y = offset_y_;
		}

		double offset_x;
		double offset_y;
	};
}