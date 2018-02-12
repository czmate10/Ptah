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
		EventWindowResized(int width, int height) : Event("window_resized")
		{
			width_ = width;
			height_ = height;
		}

		int width_;
		int height_;
	};
}