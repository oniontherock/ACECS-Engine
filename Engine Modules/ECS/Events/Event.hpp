#ifndef __EVENT_H__
#define __EVENT_H__

#include <cstdint>
#include <vector>
#include <queue>
#include <iostream>

#include "../Duplicatable/Duplicatable.hpp"

namespace EntityEvents {

	struct Event : public Duplicatable {
		// resets all the event's data to it's default values
		virtual void clear() = 0;
	};

	void eventIDsInitialize();
}

typedef std::unique_ptr<EntityEvents::Event> EventUniquePtr;
typedef std::shared_ptr<EntityEvents::Event> EventSharedPtr;

#endif