#pragma once
#include <list>
#include <vector>
#include <memory>

namespace Ptah
{
	class Entity;
	class EntityManager;
	class CameraComponent;

	class World
	{
	public:
		/**
		 * Caution: the engine will not free any world object
		 */
		World();
		~World();

		inline EntityManager& GetEntityManager()
		{
			return *entity_manager_;
		}

	protected:
		EntityManager* entity_manager_ = nullptr;
	};
}