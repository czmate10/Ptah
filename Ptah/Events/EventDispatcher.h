#pragma once
#include <functional>
#include <memory>
#include <map>
#include "Events/Event.h"
#include "Events/EventListener.h"
#include "Events/EventCallbackList.h"

namespace Ptah
{
	class EventDispatcher
	{
		friend class Engine;
		friend class Entity;

	public:
		~EventDispatcher();

		/**
		 * Adds event listener
		 * @param event_name name of the event, example: key_press
		 * @param callback the callback that will be called when this event is triggered
		 */
		EventListener* AddEventListener(const char* event_name, const std::function<void(Event*)>& callback);

		/**
		 * Removes event listener
		 * @param event_listener listener object which add_event_listener returns
		 */
		void RemoveEventListener(EventListener* event_listener);

		/**
		 * Dispatch given event
		 * @param event_name name of the event, example: key_press
		 * @param event_ptr event object, which can contain custom data as well
		 */
		void DispatchEvent(Event* event_ptr);

	protected:
		std::map<unsigned int, EventCallbackList*> callback_map_;

	private:
		EventDispatcher() : callback_map_(std::map<unsigned int, EventCallbackList*>())
		{}
	};
}
