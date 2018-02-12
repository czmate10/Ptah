#pragma once

namespace Ptah
{
	class Event;
	class EventListener;

	/**
	 * Container for event_listeners
	 */
	class EventCallbackList
	{
	public:
		EventCallbackList();

		~EventCallbackList();

		void AddEventCallback(EventListener* listener);

		void RemoveEventCallback(EventListener* listener);

		void DispatchEvent(Event* ev);

	private:
		EventListener** listeners_ = nullptr;
		unsigned int count_ = 0;
	};
}
