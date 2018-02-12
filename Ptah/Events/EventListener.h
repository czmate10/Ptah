#pragma once

namespace Ptah
{
	/**
	 * Storage class for listening functions
	 */
	class EventListener
	{
	public:
		EventListener(const char* name, const std::function<void(Event*)>& callback)
		{
			name_ = name;
			callback_ = callback;
		}

		inline void Call(Event* ev) const
		{
			callback_(ev);
		}

		inline const char* GetName() const
		{
			return name_;
		}

	private:
		const char* name_;
		std::function<void(Event*)> callback_;
	};
}