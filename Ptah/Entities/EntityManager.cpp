#include "Entities/EntityManager.h"
#include "Engine.h"
#include "Events/EventTypes/EventEntityCreated.h"

Ptah::EntityManager::EntityManager(World& world) : world_(world){}

Ptah::EntityManager::~EntityManager()
{
	for(auto it = entities_.begin(); it != entities_.end(); it++)
	{
		if((*it) != nullptr)
			delete (*it);
	}
}

Ptah::Entity* Ptah::EntityManager::Add(std::string name)
{
	auto obj = new Entity(name, world_);
	obj->id_ = AllocateNewId();
	entities_.emplace_back(obj);
	Engine::Instance().GetEventDispatcher()->DispatchEvent(new EventEntityCreated(obj));
	return obj;
}

Ptah::Entity* Ptah::EntityManager::FindById(uint32_t id)
{
	for(auto it = entities_.begin(); it != entities_.end(); it++)
	{
		if((*it)->GetId() == id)
			return (*it);
	}
	throw std::out_of_range("No entity was found with the given ID!");
}

Ptah::Entity* Ptah::EntityManager::FindByName(std::string name)
{
	for(auto it = entities_.begin(); it != entities_.end(); it++)
	{
		if((*it)->GetName() == name)
			return (*it);
	}
	throw std::out_of_range("No entity was found with the given ID!");
}

Ptah::Entity* Ptah::EntityManager::Clone(Entity &other_object)
{
	auto obj = new Entity(other_object);
	obj->id_ = AllocateNewId();
	entities_.emplace_back(obj);
	Engine::Instance().GetEventDispatcher()->DispatchEvent(new EventEntityCreated(obj));
	return obj;
}