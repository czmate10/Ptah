#pragma once
#include "Events/Event.h"

namespace Ptah
{
	/**
	 * Will be called everytime the game updates
	 */
	class EventWindowResized : public Event
	{
	public:
		EventWindowResized(int width_, int height_) : Event("window_resized")
		{
			width = width_;
			height = height_;
		}

		int width;
		int height;
	};
}