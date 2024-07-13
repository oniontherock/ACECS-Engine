#pragma once
#include <cstdint>
#include <array>
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <optional>

#include "../Components/Component.hpp"
#include "../Components/ComponentIDs.hpp"

#include "../Events/Event.hpp"
#include "../Events/EventIDs.hpp"

#include "../TypeDefinitions.hpp"

#include "../../GameWorld/LevelTypeDefinitions.hpp"

struct Entity {
	explicit Entity();
	Entity(Entity& other) = delete;
	Entity& operator= (const Entity& other) = delete;
	
	void entityCreate(EntityId _Id, EntityUpdateType _updateType);
	void entityCreate(EntityId _Id, EntityUpdateType _updateType, LevelPosition _levelId);
	// terminates this entity, then sets all data to that of the other entity, and finally terminates the other entity.
	void entityBecomeOther(Entity& other);

	void componentsInitialize();
	void eventsInitialize();

	EntityUpdateType updateType;

	// the Id of this entity, every entity has a unique Id.
	// Ids are used to access entities in the EntityManager's "entities" vector
	EntityId Id;
	// the id of the level that this entity belongs to,
	// if all three components are equal to the max uint32_t value, then this entity does not belong to a level
	LevelPosition levelId;

	std::vector<ComponentUniquePtr> componentsVector;

	std::vector<EventPtr> eventsVector;
	bool hasAnyEvent = false;


	template <class T>
	T* entityComponentGet() {
		return static_cast<T*>(componentsVector[EntityComponents::ComponentIDs<T>::ID].get());
	}
	template <class T>
	bool entityComponentHas() {
		return static_cast<bool>(componentsVector[EntityComponents::ComponentIDs<T>::ID]);
	}
	template <class T>
	void entityComponentAdd(EntityComponents::Component* component) {
		componentsVector[EntityComponents::ComponentIDs<T>::ID] = ComponentUniquePtr(component);
	}
	// checks if the entity has the component, and if not, adds it
	template <class T>
	void entityComponentAddNoOverwrite(EntityComponents::Component* component) {
		if (entityComponentHas<T>()) return;

		entityComponentAdd<T>(component);
	}
	template <class T>
	void entityComponentTerminate() {
		componentsVector[EntityComponents::ComponentIDs<T>::ID].reset();
	}
	bool entityComponentHasAtIndex(EntityComponents::ComponentTypeID index);
	void entityComponentAddAtIndex(EntityComponents::Component* component, EntityComponents::ComponentTypeID index);
	// checks if the entity has the component, and if not, adds it
	void entityComponentAddAtIndexNoOverwrite(EntityComponents::Component* component, EntityComponents::ComponentTypeID index);


	template <class T>
	T* entityEventGet() {
		return static_cast<T*>(eventsVector[EntityEvents::EventIDs<T>::ID].get());
	}
	template <class T>
	bool entityEventHas() {
		return eventsVector[EntityEvents::EventIDs<T>::ID]->isActive;
	}
	// sets an event to active
	template <class T>
	void entityEventAdd() {
		hasAnyEvent = true;

		eventsVector[EntityEvents::EventIDs<T>::ID]->isActive = true;
		return;
	}
	// sets an event to active and returns the event so it's members may be modified
	template <class T>
	T* entityEventAddAndReturn() {
		entityEventAdd<T>();
		return entityEventGet<T>();
	}
	template <class T>
	void entityEventDeactivate() {
		eventsVector[EntityEvents::EventIDs<T>::ID]->isActive = false;
	}


	void entityUpdate();
	void componentsUpdate();
	void componentsAllTerminate();
	void eventsAllDeactivate();
	void eventsAllTerminate();
	void terminate();
};
