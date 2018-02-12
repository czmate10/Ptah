#pragma once
#include <functional>

namespace Ptah
{
	class Event
	{
	public:
		/**
		 * Converts name to id
		 */
		static inline unsigned int GetIdFromName(std::string name)
		{
			return std::hash<std::string>{}(name);
		}

		/**
		 * @param event_name Name of the event
		 */
		explicit Event(const char* event_name)
		{
			event_name_ = event_name;
			id_ = Event::GetIdFromName(event_name);
		}

		/**
		 * @param event_name Name of the event
		 * @param custom_data Custom data, type is void*
		 */
		Event(const char* event_name, void* custom_data)
		{
			event_name_ = event_name;
			id_ = Event::GetIdFromName(event_name);
			custom_data_ = custom_data;
		}

		/**
		 * Gets event name
		 */
		inline const char* GetName() const
		{
			return event_name_;
		}

		/**
		 * Gets event id, which is automatically generated from its name
		 */
		inline unsigned int GetId() const
		{
			return id_;
		}

		/**
		 * Sets custom data of the object
		 */
		inline void SetCustomData(void* custom_data)
		{
			custom_data_ = custom_data;
		}

		/**
		 * Gets custom data of the object
		 */
		inline void* GetCustomData() const
		{
			return custom_data_;
		}
	private:
		const char* event_name_;
		unsigned int id_;
		void* custom_data_ = nullptr;
	};
}