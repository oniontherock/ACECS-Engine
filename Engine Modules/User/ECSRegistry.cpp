#include "ECSRegistry.hpp"

void ECSRegistry::initializeECS() {
	Components::initialize();
	EntityEvents::initialize();
}
void ECSRegistry::terminateECS() {
	for (uint16_t i = 0; i < EntityEvents::allEvents.size(); i++) {
		delete EntityEvents::allEvents[i];
	}
	EntityManager::deleteAllEntities();
}

#pragma region Events
/*
registers all events
registering an event gives it an ID which dictates it's update order, lower ID, sooner update.

the order of registry is very important, as it heavily dictates the behavior of events,
for example:

REGISTER(Event, EventA)
REGISTER(Event, EventB)

in this example, EventA is ALWAYS updated BEFORE EventB,
which is very important, because if EventA sends and event, EventB will always receive it,
but if the order were swapped, EventB would never receive it
*/
void EntityEvents::initialize() {
	/// registry convention:
	TypeIDAllocator<Event>::registerType<EventIDs<EventExample>>();
}

#pragma endregion Events
#pragma region Components
/*
registers all components,
registering a component gives it an ID which dictates it's update order, lower ID, sooner update.

the order of registry is very important, as it heavily dictates the behavior of components,
for example:

REGISTER(Component, ComponentA)
REGISTER(Component, ComponentB)

in this example, ComponentA is ALWAYS updated BEFORE ComponentB,
which is very important, because if ComponentA sends and event, ComponentB will always receive it,
but if the order were swapped, ComponentB would never receive it
*/


void Components::initialize() {
	/// registry convention:
	TypeIDAllocator<Component>::registerType<ComponentIDs<ComponentExample>>();
}

#pragma endregion Components
#pragma region Systems

#include "../Input.hpp"

using namespace Components;
using namespace EntityEvents;

Input::Interface inputInterface{};

void ComponentExample::system(Entity& entity) {

}

#pragma endregion Systems
