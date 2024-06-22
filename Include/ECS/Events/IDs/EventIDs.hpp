#ifndef __EVENT_IDS_H__
#define __EVENT_IDS_H__

// this file simply holds the event IDs, there really isn't much going on in here,
// and it should probably remain unchanged

#include <cstdint>

namespace EntityEvents {

	// an ID representing a certain TYPE of Event, NOT a specific event instance
	typedef uint16_t EventTypeID;

	// EventTypesHolder is a sort of helper struct that holds the EventTypeID of every type of event,
	// an ID is simply an integer assigned uniquely to every child of base class "Event",
	// the way you get the ID of a event type is like this: "EventIDHolder<TYPE>::ID".
	// event IDs are used for a few things, primaryily for iterating through event types in the EventManager
	template <class T>
	struct EventIDs {
		static EventTypeID ID;
	};

	// define EventIDHolder's ID variable as 0 for every type.
	// note that the ID for every type is assigned later, 
	// if you wish to see how this is done, see the "Event.cpp" file, or the "TypeAllocator.hpp" file.
	template <class T>
	EventTypeID EventIDs<T>::ID{ 0 };
};

#endif