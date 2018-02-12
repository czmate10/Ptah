#pragma once
#include <sstream>
#include <map>
#include "Components/TransformComponent.h"
#include <typeindex>

namespace Ptah
{
	class World;
	class Component;

	class Entity
	{
		friend class EntityManager;
		friend class World;

	public:
		~Entity();

		/**
		 * Get name of object
		 * @return name of object
		 */
		inline std::string GetName()
		{
			return name_;
		}

		/**
		 * Adds a component to the entity
		 */
		template <class ComponentType>
		void AddComponent(Component* comp)
		{
			comp->parent_ = this;
			comp->OnParentAdded();
			components_[typeid(ComponentType)].push_back(comp);
		}

		/**
		 * entity_manager should set the id of an entity
		 * @return id of the entity
		 */
		inline uint32_t GetId()
		{
			return id_;
		}

		/**
		 * Returns the requested component.
		 * Returns nullptr if no component was found with given type
		 */
		template <class ComponentType>
		ComponentType* GetComponent()
		{
			auto it = components_.find(typeid(ComponentType));
			if(it != components_.end())
			{
				return static_cast<ComponentType*>(it->second.front());
			}
			return nullptr;
		}

		/**
		 * Returns every component with the given type
		 * Returns empty std::vector if no component was found with given type
		 */
		template <class ComponentType>
		std::vector<ComponentType*> GetComponents()
		{
			auto it = components_.find(typeid(ComponentType));
			if(it != components_.end())
			{
				return it->second
			}
			return std::vector<ComponentType*>();
		}

		std::map<std::type_index, std::vector<Component*>> GetAllComponents()
		{
			return components_;
		}

		/**
		 * Returns the transform component
		 * You can get it via get_component as well, this is to speed up development
		 * @return transform component
		 */
		inline TransformComponent* GetTransform()
		{
			return GetComponent<Ptah::TransformComponent>();
		}

		/**
		 * Returns a debug string representing this entity
		 * @return debug string
		 */
		std::string GetDebugString();


	protected:
		uint32_t id_ = 0;
		std::string name_ = "unknown";
		World& world_;
		std::map<std::type_index, std::vector<Component*>> components_;

		/**
		 * Should only be constructed through a world object
		 * @param name name of the object
		 * @param world world object which this game_object will reside in
		 */
		Entity(std::string name, World& world);

		/**
		 * Should only be constructed through a world object
		 * Copies a game_object and all components it has
		 */
		Entity(const Entity& other);

	private:
		/**
		 * Adds an internal component
		 * Internal components, such as the transform component can only be initialized from within the entity class
		 */
		template <class ComponentType>
		ComponentType* AddComponentInternal()
		{
			ComponentType* comp = new ComponentType();
			comp->parent_ = this;
			comp->OnParentAdded();
			components_[typeid(ComponentType)].push_back(comp);
			return comp;
		}
	};
}
