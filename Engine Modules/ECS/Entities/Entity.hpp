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

struct Entity {
	explicit Entity() {
		updateType = EntityUpdateType::Frame;
		ID = 0;
	};
	Entity(Entity& other) = delete;
	Entity& operator= (const Entity& other) = delete;
	
	void entityCreate(EntityID id, EntityUpdateType _updateType) {
		ID = id;
		updateType = _updateType;

		componentsInitialize();
		eventsInitialize();
	}
	void entityCreateFromOther(Entity& other) {
		
		terminate();
		
		entityCreate(other.ID, other.updateType);

		componentsVector = std::move(other.componentsVector);
		eventsVector = std::move(other.eventsVector);
	}

	inline void componentsInitialize() {
		componentsVector = std::vector<ComponentUniquePtr>(EntityComponents::totalComponents);
	};

	inline void eventsInitialize() {
		auto& allEvents = EntityEvents::allEvents;

		for (uint16_t i = 0; i < allEvents.size(); i++) {
			eventsVector.push_back(Duplicatable::duplicateAndConvertToType<EntityEvents::Event>(allEvents[i]));
		}
	};

	EntityUpdateType updateType;

	EntityID ID;

	std::vector<ComponentUniquePtr> componentsVector;

	std::vector<EventPtr> eventsVector;
	bool hasAnyEvent = false;


	template <class T>
	inline T* entityComponentGet() {
		return static_cast<T*>(componentsVector[EntityComponents::ComponentIDs<T>::ID].get());
	}
	template <class T>
	inline bool entityComponentHas() {
		return static_cast<bool>(componentsVector[EntityComponents::ComponentIDs<T>::ID]);
	}
	template <class T>
	inline void entityComponentAdd(EntityComponents::Component* component) {
		componentsVector[EntityComponents::ComponentIDs<T>::ID] = ComponentUniquePtr(component);
	}
	// checks if the entity has the component, and if not, adds it
	template <class T>
	inline void entityComponentAddNoOverwrite(EntityComponents::Component* component) {
		if (entityComponentHas<T>()) return;

		entityComponentAdd<T>(component);
	}
	template <class T>
	inline void entityComponentTerminate() {
		componentsVector[EntityComponents::ComponentIDs<T>::ID].reset();
	}
	inline bool entityComponentHasAtIndex(EntityComponents::ComponentTypeID index) {
		return static_cast<bool>(componentsVector[index]);
	}
	inline void entityComponentAddAtIndex(EntityComponents::Component* component, EntityComponents::ComponentTypeID index) {
		componentsVector[index] = ComponentUniquePtr(component);
	}
	// checks if the entity has the component, and if not, adds it
	inline void entityComponentAddAtIndexNoOverwrite(EntityComponents::Component* component, EntityComponents::ComponentTypeID index) {
		if (entityComponentHasAtIndex(index)) return;

		entityComponentAddAtIndex(component, index);
	}

	template <class T>
	inline T* entityEventGet() {
		return static_cast<T*>(eventsVector[EntityEvents::EventIDs<T>::ID].get());
	}
	template <class T>
	inline bool entityEventHas() {
		return eventsVector[EntityEvents::EventIDs<T>::ID]->isActive;
	}
	// sets an event to active
	template <class T>
	inline void entityEventAdd() {
		hasAnyEvent = true;

		eventsVector[EntityEvents::EventIDs<T>::ID]->isActive = true;
		return;
	}
	// sets an event to active and returns the event so it's members may be modified
	template <class T>
	inline T* entityEventAddAndReturn() {
		entityEventAdd<T>();
		return entityEventGet<T>();
	}
	template <class T>
	inline void entityEventDeactivate() {
		eventsVector[EntityEvents::EventIDs<T>::ID]->isActive = false;
	}

	inline void entityUpdate() {
		componentsUpdate();
		// deactivating all events is basically just clearing the entity's events
		if (hasAnyEvent) eventsAllDeactivate();
	}
	inline void componentsUpdate() {
		for (uint16_t i = 0; i < EntityComponents::totalComponents; i++) {

			if (componentsVector[i] == nullptr) continue;
			if (!componentsVector[i]->hasSystem) continue;

			componentsVector[i]->system(*this);
		}
	}

	inline void componentsAllTerminate() {
		for (EntityComponents::ComponentTypeID i = 0; i < EntityComponents::totalComponents; i++) {
			componentsVector[i].reset();
		}
	}

	inline void eventsAllDeactivate() {
		for (uint16_t i = 0; i < eventsVector.size(); i++) {
			eventsVector[i]->isActive = false;
		}

		hasAnyEvent = false;
	}

	inline void eventsAllTerminate() {
		for (uint16_t i = 0; i < eventsVector.size(); i++) {

			if (eventsVector[i] != nullptr) {
				eventsVector[i].reset();
			}
		}

		hasAnyEvent = false;
	}

	inline void terminate() {
		componentsAllTerminate();
		eventsAllTerminate();
	}
};
