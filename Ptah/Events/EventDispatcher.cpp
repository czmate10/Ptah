#include "Events/EventDispatcher.h"

Ptah::EventDispatcher::~EventDispatcher() {
	for(auto it = callback_map_.begin(); it != callback_map_.end();)
	{
		if(it->second != nullptr)
			delete it->second;
		it = callback_map_.erase(it);
	}
}

Ptah::EventListener* Ptah::EventDispatcher::AddEventListener(const char* event_name,
                                                                                 const std::function<void(Event*)>& callback)
{
	auto event_id = Event::GetIdFromName(event_name);
	if(callback_map_.find(event_id) == callback_map_.end())
	{
		callback_map_[event_id] = new EventCallbackList();
	}

	auto listener = new EventListener(event_name, callback);
	callback_map_[event_id]->AddEventCallback(listener);
	return listener;
}

void Ptah::EventDispatcher::RemoveEventListener(EventListener* event_listener)
{
	auto event_id = Event::GetIdFromName(event_listener->GetName());
	if(callback_map_.find(event_id) == callback_map_.end())
		return;

	auto list = callback_map_.at(event_id);
	if (list == nullptr)
		return;

	list->RemoveEventCallback(event_listener);
}

void Ptah::EventDispatcher::DispatchEvent(Event* event_ptr)
{
	auto pair = callback_map_.find(event_ptr->GetId());
	if (pair == callback_map_.end())
		return;

	auto list = pair->second;
	list->DispatchEvent(event_ptr);
	delete event_ptr;
}
