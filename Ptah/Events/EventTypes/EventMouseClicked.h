#pragma once
#include "Events/Event.h"

namespace Ptah
{
	/**
	 * Will be called when the user clicks one of their mouse buttons
	 */
	class EventMouseClicked : public Event
	{
	public:
		EventMouseClicked(int button_, int action_, int mods_) : Event("mouse_clicked")
		{
			button = button_;
			action = action_;
			mods = mods_;
		}

		int button;
		int action;
		int mods;
	};
}