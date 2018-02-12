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
		EventMouseClicked(int button, int action, int mods) : Event("mouse_clicked")
		{
			button_ = button;
			action_ = action;
			mods_ = mods;
		}

		int button_;
		int action_;
		int mods_;
	};
}