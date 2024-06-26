#pragma once
#include <cstdint>
#include <vector>
#include <set>


#include "../Components/Component.hpp"
#include "../Components/IDs/ComponentIDs.hpp"

#include "../Events/Event.hpp"
#include "../Events/IDs/EventIDs.hpp"

#include "../TypeDefinitions.hpp"


struct Entity {
	Entity() = default;
	Entity(EntityID id, EntityUpdateType _updateType) : ID(id), updateType(_updateType) {};
	~Entity() {
		clearComponents();
		clearEvents();
	}

	EntityUpdateType updateType;

	EntityID ID;

	std::unordered_map<Components::ComponentTypeID, Components::Component*> componentsMap;
	std::unordered_map<EntityEvents::EventTypeID, EntityEvents::Event*> eventsMap;

	template <class T>
	inline void addComponent(Components::Component* component) {
		componentsMap.insert({ Components::ComponentIDs<T>::ID, component });
	}
	template <class T>
	inline void removeComponent() {
		componentsMap.erase(Components::ComponentIDs<T>::ID);
	}
	template <class T>
	inline T* getComponent() {
		return static_cast<T*>(componentsMap[Components::ComponentIDs<T>::ID]);
	}
	template <class T>
	inline bool hasComponent() {
		return componentsMap.count(Components::ComponentIDs<T>::ID);
	}

	template <class T>
	inline void addEvent(EntityEvents::Event* event) {
		eventsMap.insert({ EntityEvents::EventIDs<T>::ID, event });
	}
	template <class T>
	inline void removeEvent() {
		eventsMap.erase(EntityEvents::EventIDs<T>::ID);
	}
	template <class T>
	inline T* getEvent() {
		return static_cast<T*>(eventsMap[EntityEvents::EventIDs<T>::ID]);
	}
	template <class T>
	inline bool hasEvent() {
		return eventsMap.count(EntityEvents::EventIDs<T>::ID);
	}

	inline void update() {
		updateComponents();
		clearEvents();
	}

	inline void updateComponents() {
		for (const auto& [key, value] : componentsMap) {
			value->system(*this);
		}
	}

	inline void clearComponents() {
		for (const auto& [key, value] : componentsMap) {
			delete value;
		}
		componentsMap.clear();
	}

	inline void clearEvents() {
		for (const auto& [key, value] : eventsMap) {
			delete value;
		}

		eventsMap.clear();
	}
};
