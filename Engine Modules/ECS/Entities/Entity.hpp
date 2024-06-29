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
		componentsMap = std::vector<Components::Component*>(0);
	};
	Entity(EntityID id, EntityUpdateType _updateType) : ID(id), updateType(_updateType) {
		initializeComponents();
		initializeEvents();
	};
	~Entity() {};

	inline void clear() {
		clearComponents();
		clearEvents();
	}

	inline void initializeComponents() {
		componentsMap = std::vector<Components::Component*>(Components::totalComponents);

		for (uint16_t i = 0; i < Components::totalComponents; i++) {
			componentsMap[i] = nullptr;
		}
	};

	inline void initializeEvents() {
		auto& allEvents = EntityEvents::allEvents;

		for (uint16_t i = 0; i < allEvents.size(); i++) {
			eventsMap.push_back(allEvents[i]);
		}
	};

	EntityUpdateType updateType;

	EntityID ID;

	std::vector<Components::Component*> componentsMap;

	std::vector<EntityEvents::Event*> eventsMap;
	bool hasAnyEvent = false;


	template <class T>
	inline T* getComponent() {
		return static_cast<T*>(componentsMap[Components::ComponentIDs<T>::ID]);
	}
	template <class T>
	inline bool hasComponent() {
		return componentsMap[Components::ComponentIDs<T>::ID] != nullptr;
	}
	template <class T>
	inline void addComponent(Components::Component* component) {
		componentsMap[Components::ComponentIDs<T>::ID] = component;
	}
	template <class T>
	inline void removeComponent() {
		delete componentsMap[Components::ComponentIDs<T>::ID];
		componentsMap[Components::ComponentIDs<T>::ID] = nullptr;
	}

	template <class T>
	inline T* getEvent() {
		return static_cast<T*>(eventsMap[EntityEvents::EventIDs<T>::ID]);
	}
	template <class T>
	inline bool hasEvent() {
		return eventsMap[EntityEvents::EventIDs<T>::ID]->isActive;
	}
	// sets an event to active and returns the event so it's members may be modified
	template <class T>
	inline T* addEvent() {
		hasAnyEvent = true;
		eventsMap[EntityEvents::EventIDs<T>::ID]->isActive = true;
		return getEvent<T>();
	}
	// sets an event to active
	template <class T>
	inline void addEventNoReturn() {
		eventsMap[EntityEvents::EventIDs<T>::ID]->isActive = true;
	}
	template <class T>
	inline void removeEvent() {
		eventsMap[EntityEvents::EventIDs<T>::ID]->isActive = false;
	}

	inline void update() {
		updateComponents();
		if (hasAnyEvent) clearEvents();
	}
	inline void updateComponents() {
		for (uint16_t i = 0; i < Components::totalComponents; i++) {

			if (componentsMap[i] == nullptr) continue;
			if (!componentsMap[i]->hasSystem) continue;

			componentsMap[i]->system(*this);
		}
	}

	inline void clearComponents() {
		std::cout << componentsMap[0] << std::endl;
		for (uint16_t i = 0; i < Components::totalComponents; i++) {

			bool notNull = componentsMap[i] != nullptr;

			if (notNull) {
				delete componentsMap[i];
				componentsMap[i] = nullptr;
			}
		}
	}
	inline void clearEvents() {
		for (uint16_t i = 0; i < eventsMap.size(); i++) {
			eventsMap[i]->isActive = false;
		}

		hasAnyEvent = false;
	}
};
