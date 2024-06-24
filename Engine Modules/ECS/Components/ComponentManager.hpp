#ifndef _COMPONENT_MANAGER_H__
#define _COMPONENT_MANAGER_H__

#include <array>
#include <unordered_map>

#include "../Entities/Entity.hpp"
#include "../Entities/EntityManager.hpp"

#include "Component.hpp"
#include "IDs/ComponentIDs.hpp"

#include "../TypeDefinitions.hpp"

typedef std::unordered_map<EntityID, Components::Component*> ComponentMap;

namespace ComponentManager {
	// accessing convention:
	// componentArray[ComponentType][EntityID]
	inline std::array<ComponentMap, MAX_COMPONENT_TYPES> componentArray;

	template <class T>
	inline Components::ComponentTypeID getComponentTypeID() {
		return Components::ComponentIDs<T>::ID;
	}

	// returns whether an entity has the componentType or not
	template <class T>
	inline bool entityHasComponent(EntityID entityID) {
		return EntityManager::entities[entityID]->componentTypesList.find(getComponentTypeID<T>()) != EntityManager::entities[entityID]->componentTypesList.end();
	}

	// casts a component to T
	template <class T>
	inline T* castComponent(Components::Component* baseComponent) {
		return static_cast<T*>(baseComponent);
	}

	// retrieves a component from componentArray, includes a check to make sure that the entity has the component
	template <class T>
	inline Components::Component* getComponentSafe(EntityID entityID) {
		if (!entityHasComponent<T>(entityID)) return nullptr;

		return componentArray[static_cast<uint16_t>(getComponentTypeID<T>())][entityID];
	}

	// retrieves a component from componentArray
	template <class T>
	inline Components::Component* getComponentUnsafe(EntityID entityID) {
		return componentArray[static_cast<uint16_t>(getComponentTypeID<T>())][entityID];
	}
	
	// retrieves a component from the component array and casts it to T, includes a check to make sure that the entity has the component
	template <class T>
	inline T* getComponentCastedSafe(EntityID entityID) {
		return castComponent<T>(getComponentSafe<T>(entityID));
	}

	// retrieves a component from the component array and casts it to T
	template <class T>
	inline T* getComponentCastedUnsafe(EntityID entityID) {
		return castComponent<T>(getComponentUnsafe<T>(entityID));
	}

	// adds a component to the ComponentMap corresponding to the componentType
	template <class T>
	inline void addComponent(EntityID entityID, Components::Component* component) {
		componentArray[static_cast<uint16_t>(getComponentTypeID<T>())][entityID] = component;

		EntityManager::entities[entityID]->componentTypesList.insert(getComponentTypeID<T>());
		if (SystemManager::typeHasSystem(getComponentTypeID<T>())) {
			EntityManager::entities[entityID]->componentTypesWithSystemsList.insert(getComponentTypeID<T>());
		}
	}

	// deletes a component and removes it from the corresponding ComponentMap, includes a safety check
	template <class T>
	inline void removeComponentSafe(EntityID entityID) {
		if (!entityHasComponent(entityID, getComponentTypeID<T>())) return;

		delete componentArray[static_cast<uint16_t>(getComponentTypeID<T>())][entityID];
		componentArray[static_cast<uint16_t>(getComponentTypeID<T>())].erase(entityID);

		EntityManager::entities[entityID]->componentTypesList.erase(getComponentTypeID<T>());
		EntityManager::entities[entityID]->componentTypesWithSystemsList.erase(getComponentTypeID<T>());
	}
};

#endif