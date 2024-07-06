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

typedef std::unique_ptr<EntityComponents::Component> ComponentPtr;
typedef std::unique_ptr<EntityEvents::Event> EventPtr;

struct Entity {
	explicit Entity() {
		updateType = EntityUpdateType::Frame;
		ID = 0;
	};
	Entity(Entity& other) = delete;
	Entity& operator= (const Entity& other) = delete;
	//~Entity() = default;
	
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
		componentsVector = std::vector<ComponentPtr>(EntityComponents::totalComponents);
	};

	inline void eventsInitialize() {
		auto& allEvents = EntityEvents::allEvents;

		for (uint16_t i = 0; i < allEvents.size(); i++) {


			std::unique_ptr<Duplicatable> duplicatablePtr = allEvents[i]->duplicate();
			// get the raw pointer behind the duplicatablePtr
			Duplicatable* rawPointer = duplicatablePtr.get();
			// release the duplicatablePtr
			duplicatablePtr.release();

			eventsVector.push_back(std::unique_ptr<EntityEvents::Event>(static_cast<EntityEvents::Event*>(rawPointer)));
			//std::cout << (*eventsVector[i].get()). << std::endl;
		}
	};

	EntityUpdateType updateType;

	EntityID ID;

	std::vector<ComponentPtr> componentsVector;

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
		componentsVector[EntityComponents::ComponentIDs<T>::ID] = ComponentPtr(component);
	}
	// checks if the entity has the component, and if not, adds it
	template <class T>
	inline void entityComponentAddNoOverride(EntityComponents::Component* component) {
		if (entityComponentHas<T>()) return;

		componentsVector[EntityComponents::ComponentIDs<T>::ID] = ComponentPtr(component);
	}
	template <class T>
	inline void entityComponentTerminate() {
		componentsVector[EntityComponents::ComponentIDs<T>::ID].reset();
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
		componentsVector.clear();
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
