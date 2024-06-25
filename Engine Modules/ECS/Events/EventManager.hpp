#ifndef __EVENT_MANAGER_H__
#define __EVENT_MANAGER_H__
#include <array>
#include <unordered_map>

#include "../Entities/Entity.hpp"
#include "../Entities/EntityManager.hpp"
#include "Event.hpp"
#include "IDs/EventIDs.hpp"
#include "../TypeDefinitions.hpp"

typedef std::unordered_map<EntityID, EntityEvents::Event*> EventMap;

namespace EventManager {

	// accessing convention:
	// eventArray[EventType][EntityID]
	inline std::array<EventMap, MAX_EVENT_TYPES> eventArray;

	template <class T>
	inline EntityEvents::EventTypeID getEventTypeID() {
		return EntityEvents::EventIDs<T>::ID;
	}

	// returns whether an entity has the eventType or not
	template <typename T>
	inline bool entityHasEvent(EntityID entityID) {
		return EntityManager::entities[entityID]->eventTypesList.find(getEventTypeID<T>()) != EntityManager::entities[entityID]->eventTypesList.end();
	}

	// casts a event to T
	template <typename T>
	inline T* castEvent(EntityEvents::Event* baseEvent) {
		return static_cast<T*>(baseEvent);
	}

	// retrieves a event from eventArray, includes a check to make sure that the entity has the event
	template <class T>
	inline EntityEvents::Event* getEventSafe(EntityID entityID) {
		if (!entityHasEvent(entityID, getEventTypeID<T>())) return nullptr;

		return eventArray[static_cast<uint16_t>(getEventTypeID<T>())][entityID];
	}

	// retrieves a event from eventArray
	template <class T>
	inline EntityEvents::Event* getEventUnsafe(EntityID entityID) {
		return eventArray[static_cast<uint16_t>(getEventTypeID<T>())][entityID];
	}

	// retrieves a event from the event array and casts it to T, includes a check to make sure that the entity has the event
	template <typename T>
	inline T* getEventCastedSafe(EntityID entityID) {
		return castEvent<T>(getEventSafe<T>(entityID));
	}

	// retrieves a event from the event array and casts it to T
	template <typename T>
	inline T* getEventCastedUnsafe(EntityID entityID) {
		return castEvent<T>(getEventUnsafe<T>(entityID));
	}

	// adds a event to the EventMap corresponding to the eventType
	template <class T>
	inline void addEvent(EntityID entityID, EntityEvents::Event* event) {
		eventArray[static_cast<uint16_t>(getEventTypeID<T>())][entityID] = event;

		EntityManager::entities[entityID]->eventTypesList.insert(getEventTypeID<T>());
	}

	// deletes a event and removes it from the corresponding EventMap, includes a safety check
	template <class T>
	inline void removeEventSafe(EntityID entityID) {
		if (!entityHasEvent(entityID, getEventTypeID<T>())) return;

		EntityEvents::EventTypeID eventId = static_cast<uint16_t>(getEventTypeID<T>());

		delete eventArray[eventId][entityID];
		eventArray[eventId].erase(entityID);

		EntityManager::entities[entityID]->eventTypesList.erase(getEventTypeID<T>());
	}

	// deletes a event and removes it from the corresponding EventMap
	template <class T>
	inline void removeEventUnsafe(EntityID entityID) {

		EntityEvents::EventTypeID eventId = static_cast<uint16_t>(getEventTypeID<T>());

		delete eventArray[eventId][entityID];
		eventArray[eventId].erase(entityID);

		EntityManager::entities[entityID]->eventTypesList.erase(getEventTypeID<T>());
	}

	// deletes a event and removes it from the corresponding EventMap
	inline void removeEventUnsafe(EntityID entityID, EntityEvents::EventTypeID eventId) {


		delete eventArray[eventId][entityID];
		eventArray[eventId].erase(entityID);

		EntityManager::entities[entityID]->eventTypesList.erase(eventId);
	}

	inline void removeEntityEvents(EntityID entityID) {
		for (EntityEvents::EventTypeID curEventType : EntityManager::entities[entityID]->eventTypesList) {
			removeEventUnsafe(entityID, curEventType);
		}
	}

	inline void removeAllEvents() {
		std::for_each(
			EntityManager::entities.begin(), EntityManager::entities.end(),
			[](std::pair<EntityID, Entity*> pair) {
				removeEntityEvents(pair.second->ID);
			}
		);
	}

};

#endif