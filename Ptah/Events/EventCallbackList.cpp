#include <memory>
#include "Events/EventCallbackList.h"
#include "Events/Event.h"
#include "Events/EventListener.h"

Ptah::EventCallbackList::EventCallbackList()
{
}

Ptah::EventCallbackList::~EventCallbackList()
{
	for (unsigned int i = 0; i < count_; i++)
	{
		delete listeners_[i];
	}
	delete[] listeners_;
}


void Ptah::EventCallbackList::AddEventCallback(EventListener* listener)
{
	auto listeners_new = new EventListener*[count_ + 1];
	for (unsigned int i = 0; i < count_; i++)
	{
		listeners_new[i] = listeners_[i];
	}
	if(listeners_ != nullptr)
		delete[] listeners_;
	listeners_ = listeners_new;
	listeners_[count_] = listener;
	count_++;
}

void Ptah::EventCallbackList::RemoveEventCallback(EventListener* listener)
{
	if(count_ == 1)
	{
		// Last one in the list
		count_ = 0;
		delete listener;
		listeners_ = nullptr;
		return;
	}

	unsigned at = 0;
	for (unsigned int i = 0; i < count_; i++)
	{
		if (listeners_[i] != listener)
		{
			listeners_[at] = listeners_[i];
			at++;
		}
	}
	count_--;
}

void Ptah::EventCallbackList::DispatchEvent(Event* ev)
{
	for (unsigned int i = 0; i < count_; i++)
	{
		listeners_[i]->Call(ev);
	}
}
