#pragma once
#include <memory>
#include <vector>
#include <functional>

namespace Ptah
{
	class Entity;
	class Event;
	class EventListener;

	/**
	 * Components are attached to entities to define the behaviour of the object
	 */
	class Component
	{
		friend class Entity;
	public:
		Component();

		/**
		 * Frees up event listeners
		 */
		virtual ~Component();

		/**
		 * Returns a clone of this component
		 * Should not use any resource of this component
		 * Every component should implement this function
		 * @return clone of this component
		 */
		virtual Component* Clone() = 0;

		/**
		 * Called when a parent is attached to the component
		 */
		virtual void OnParentAdded() {};

		/**
		 * Use this to hook into the global eventsystem
		 * These event listeners will automatically be removed when the component is freed
		 * @param name event name
		 * @param callback callback function, use std::bind
		 */
		void AddEventListener(const char* name, std::function<void(Ptah::Event*)> callback);

		/**
		 * Get parent entity
		 * @return
		 */
		inline Entity* GetParent()
		{
			return parent_;
		}

	protected:
		Entity* parent_;
		std::vector<EventListener*> listeners_;
	};
}