#pragma once
#include "Events/Event.h"

namespace Ptah
{
	/**
	 * Will be called every time the user moves their cursor on the window
	 */
	class EventCursorMoved : public Event
	{
	public:
		EventCursorMoved(double mouse_x, double mouse_y) : Event("cursor_moved")
		{
			mouse_x_ = mouse_x;
			mouse_y_ = mouse_y;
		}

		double mouse_x_;
		double mouse_y_;
	};
}