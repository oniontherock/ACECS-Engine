#pragma once
#include <cstdint>
#include <array>
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
	Entity() {
		updateType = EntityUpdateType::Frame;
		ID = 0;
		componentsMap = std::vector<EntityComponents::Component*>(0);
	};
	Entity(EntityID id, EntityUpdateType _updateType) : ID(id), updateType(_updateType) {
		componentsInitialize();
		eventsInitialize();
	};
	~Entity() {};

	inline void componentsInitialize() {
		componentsMap = std::vector<EntityComponents::Component*>(EntityComponents::totalComponents);

		for (uint16_t i = 0; i < EntityComponents::totalComponents; i++) {
			componentsMap[i] = nullptr;
		}
	};

	inline void eventsInitialize() {
		auto& allEvents = EntityEvents::allEvents;

		for (uint16_t i = 0; i < allEvents.size(); i++) {
			eventsMap.push_back(allEvents[i]);
		}
	};

	EntityUpdateType updateType;

	EntityID ID;

	std::vector<EntityComponents::Component*> componentsMap;

	std::vector<EntityEvents::Event*> eventsMap;
	bool hasAnyEvent = false;


	template <class T>
	inline T* entityComponentGet() {
		return static_cast<T*>(componentsMap[EntityComponents::ComponentIDs<T>::ID]);
	}
	template <class T>
	inline bool entityComponentHas() {
		return componentsMap[EntityComponents::ComponentIDs<T>::ID] != nullptr;
	}
	template <class T>
	inline void entityComponentAdd(EntityComponents::Component* component) {
		componentsMap[EntityComponents::ComponentIDs<T>::ID] = component;
	}
	template <class T>
	inline void entityComponentTerminate() {
		delete componentsMap[EntityComponents::ComponentIDs<T>::ID];
		componentsMap[EntityComponents::ComponentIDs<T>::ID] = nullptr;
	}

	template <class T>
	inline T* entityEventGet() {
		return static_cast<T*>(eventsMap[EntityEvents::EventIDs<T>::ID]);
	}
	template <class T>
	inline bool entityEventHas() {
		return eventsMap[EntityEvents::EventIDs<T>::ID]->isActive;
	}
	// sets an event to active
	template <class T>
	inline void entityEventActivate() {
		hasAnyEvent = true;
		eventsMap[EntityEvents::EventIDs<T>::ID]->isActive = true;
		return;
	}
	// sets an event to active and returns the event so it's members may be modified
	template <class T>
	inline T* entityEventActivateAndReturn() {
		entityEventActivate<T>();
		return entityEventGet<T>();
	}
	template <class T>
	inline void entityEventDeactivate() {
		eventsMap[EntityEvents::EventIDs<T>::ID]->isActive = false;
	}

	inline void entityUpdate() {
		componentsUpdate();
		// deactivating all events is basically just clearing the entity's events
		if (hasAnyEvent) eventsAllDeactivate();
	}
	inline void componentsUpdate() {
		for (uint16_t i = 0; i < EntityComponents::totalComponents; i++) {

			if (componentsMap[i] == nullptr) continue;
			if (!componentsMap[i]->hasSystem) continue;

			componentsMap[i]->system(*this);
		}
	}

	inline void eventsAllDeactivate() {
		for (uint16_t i = 0; i < eventsMap.size(); i++) {
			eventsMap[i]->isActive = false;
		}

		hasAnyEvent = false;
	}

	inline void componentsAllTerminate() {
		for (uint16_t i = 0; i < EntityComponents::totalComponents; i++) {

			if (componentsMap[i] != nullptr) {
				delete componentsMap[i];
				componentsMap[i] = nullptr;
			}
		}
	}

	inline void eventsAllTerminate() {
		for (uint16_t i = 0; i < eventsMap.size(); i++) {

			if (eventsMap[i] != nullptr) {
				delete eventsMap[i];
				eventsMap[i] = nullptr;
			}
		}

		hasAnyEvent = false;
	}

	inline void terminate() {
		componentsAllTerminate();
		eventsAllTerminate();
	}
};
