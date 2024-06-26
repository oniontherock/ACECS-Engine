#pragma once
#include <cstdint>
#include <vector>
#include <set>
#include <queue>
#include <optional>


#include "../Components/Component.hpp"
#include "../Components/IDs/ComponentIDs.hpp"

#include "../Events/Event.hpp"
#include "../Events/IDs/EventIDs.hpp"

#include "../TypeDefinitions.hpp"


struct Entity {
	Entity() {
		updateType = EntityUpdateType::Frame;
		ID = 0;
	};
	Entity(EntityID id, EntityUpdateType _updateType) : ID(id), updateType(_updateType) {
		initializeEventsMap();
	};
	~Entity() {
		clearComponents();
		clearEvents();
	};

	inline void initializeEventsMap() {
		std::queue<EntityEvents::Event*> allEvents = EntityEvents::getAllEvents();

		while (allEvents.size() > 0) {
			eventsMap.push_back(allEvents.front());
			allEvents.pop();
		}
	};

	EntityUpdateType updateType;

	EntityID ID;

	std::vector<Components::Component*> componentsMap;
	std::set<Components::ComponentTypeID> componentsWithSystems;

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

		uint16_t ID = Components::ComponentIDs<T>::ID;

		if (ID >= componentsMap.size()) {
			componentsMap.resize(uint16_t(ID + 1), nullptr);
		}

		componentsMap[ID] = component;
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
		for (uint16_t i = 0; i < componentsMap.size(); i++) {

			if (componentsMap[i] == nullptr) return;
			if (!componentsMap[i]->hasSystem) return;

			std::invoke(Components::systems[i], *this);
		}
	}

	inline void clearComponents() {
		for (const auto& curComponent : componentsMap) {
			if (curComponent == nullptr) continue;
			delete curComponent;
		}
		componentsMap.clear();
	}
	inline void clearEvents() {
		for (uint16_t i = 0; i < eventsMap.size(); i++) {
			eventsMap[i]->isActive = false;
		}

		hasAnyEvent = false;
	}
};
