#pragma once
#include "Events/Event.h"

namespace Ptah
{
	/**
	 * Will be called when the user presses/releases/holds a key
	 */
	class EventKeyPressed : public Event
	{
	public:
		EventKeyPressed(int key, int scancode, int action, int mods) : Event("key_pressed")
		{
			key_ = key;
			scancode_ = scancode;
			action_ = action;
			mods_ = mods;
		}

		int key_;
		int scancode_;
		int action_;
		int mods_;
	};
}