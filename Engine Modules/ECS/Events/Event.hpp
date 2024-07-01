#ifndef __EVENT_H__
#define __EVENT_H__
#include <cstdint>
#include <vector>
#include <queue>


namespace EntityEvents {

	struct Event {
		bool isActive = false;
	};

	void eventIDsInitialize();
}


#endif