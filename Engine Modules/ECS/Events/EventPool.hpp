#ifndef __EVENT_POOL_H__
#define __EVENT_POOL_H__

#include "../TypeDefinitions.hpp"
#include "Event.hpp"
#include "EventIDs.hpp"

class EventPool {
	static std::vector<std::vector<EntityEvents::Event*>> eventPool;

public:
	static void eventPoolInitialize();
	template <class T>
	static inline T* eventPoolTake() {

		EntityEvents::EventTypeID eventId = EntityEvents::EventIDs<T>::ID;

		if (eventPool[eventId].size() == 0) {
			eventPoolGive(new T(), eventId);
		}

		EntityEvents::Event* item = eventPool[eventId].back();
		eventPool[eventId].pop_back();

		item->clear();

		return static_cast<T*>(item);
	}
	static inline void eventPoolGive(EntityEvents::Event* item, EntityEvents::EventTypeID eventId) {
		eventPool[eventId].push_back(item);
	}
	template <class T>
	static inline void eventPoolGive(EntityEvents::Event* item) {
		eventPoolGive(item, EntityEvents::EventIDs<T>::ID);
	}
	template <class T>
	static inline void eventPoolGive(T* item, EntityEvents::EventTypeID eventId) {
		eventPool[eventId].push_back(item);
	}
};

#endif