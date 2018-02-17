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
		EventKeyPressed(int key_, int scancode_, int action_, int mods_) : Event("key_pressed")
		{
			key = key_;
			scancode = scancode_;
			action = action_;
			mods = mods_;
		}

		int key;
		int scancode;
		int action;
		int mods;
	};
}