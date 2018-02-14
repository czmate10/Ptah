#include <iostream>
#include "Entities/Entity.h"
#include "Components/TransformComponent.h"

Ptah::Entity::Entity(std::string name, World& world)
		: name_(name)
		, world_(world)
{
	transform_component_ = new Ptah::TransformComponent();
	transform_component_->parent_ = this;
	transform_component_->OnParentAdded();
	components_[typeid(Ptah::TransformComponent)].push_back(transform_component_);
}

Ptah::Entity::Entity(const Entity& other)
		: name_(other.name_)
		, world_(other.world_)
		, components_(other.components_)
{
	for(auto kv : other.components_)
	{
		for(auto comp : kv.second)
		{
			auto obj = comp->Clone();
			obj->parent_ = this;
			obj->OnParentAdded();
			components_[kv.first].push_back(obj);
		}
	}
}

Ptah::Entity::~Entity()
{
	for(auto kv : components_)
		for(auto comp : kv.second)
			if(comp != nullptr)
				delete comp;
}

std::string Ptah::Entity::GetDebugString()
{
	std::stringstream ret;
	ret << "Entity ID " << GetId() << " (" << GetName() << ")";
	return ret.str();
}