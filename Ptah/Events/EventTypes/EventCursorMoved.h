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
		EventCursorMoved(double mouse_x_, double mouse_y_) : Event("cursor_moved")
		{
			mouse_x = mouse_x_;
			mouse_y = mouse_y_;
		}

		double mouse_x;
		double mouse_y;
	};
}