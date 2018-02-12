#pragma once
#include <list>
#include <vector>
#include <memory>
#include <map>
#include <unordered_map>

#include "Entities/Entity.h"

namespace Ptah
{
	class Entity;

	class EntityManager final
	{
		// We only want world to have entity_manager
		friend class World;

		// list of entities
		using entity_list = std::list<Entity*>;

	public:
		/**
		 * Create a new game_object with given name
		 * @param name name of the object
		 */
		Entity* Add(std::string name);

		/**
		 * Clones object along with all of its components
		 * @param other_object object to clone
		 * @return new object
		 */
		Entity* Clone(Entity& other_object);

		/**
		 * Get object by its name.
		 * You should refrain from using it every update..
		 * @param name name of the object
		 * @return object found
		 */
		Entity* FindByName(std::string name);

		/**
		 * Get object by its name.
		 * @param id of the object
		 * @return object found
		 */
		Entity* FindById(uint32_t id);

	protected:
		World& world_;
		entity_list entities_;

		uint32_t last_id_ = 0;
		inline uint32_t AllocateNewId()
		{
			return last_id_++;
		}

	private:
		EntityManager(World& world);
		~EntityManager();
	};
}