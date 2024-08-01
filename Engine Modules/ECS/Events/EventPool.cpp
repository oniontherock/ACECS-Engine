#include "EventPool.hpp"


std::vector<std::vector<EntityEvents::Event*>> EventPool::eventPool{};

void EventPool::eventPoolInitialize() {

	using Pool1D = std::vector<EntityEvents::Event*>;
	using Pool2D = std::vector<Pool1D>;

	// set levelGrid to columns, where each column is a row, and each row a slice, and each slice a unique_ptr to nullptr
	eventPool = Pool2D(MAX_EVENT_TYPES, Pool1D(0, nullptr));
}

