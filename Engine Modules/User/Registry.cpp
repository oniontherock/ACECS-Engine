#include "Registry.hpp"

#pragma region Systems

using namespace Components;
using namespace EntityEvents;
using EID = EntityID;

using namespace ComponentManager;
using namespace EntityManager;
using namespace EventManager;

/// System convention:

///static System createSystemConvention() {
///	return [](EID ID) {
///		// data goes here
///	};
///}

void SystemRegistry::createSystems() {
	
	/// add system convention
	/// SystemManager::addSystem(createSystemConvention(), getComponentTypeID<ComponentConvention>());
}
#pragma endregion Systems
#pragma region Events
/*
registers all eventss
registering an event gives it an ID which dictates it's update order, lower ID, sooner update.

the order of registry is very important, as it heavily dictates the behavior of events,
for example:

REGISTER(Event, EventA)
REGISTER(Event, EventB)

in this example, EventtA is ALWAYS updated BEFORE EventB,
which is very important, because if EventA sends and event, EventB will always recieve it,
but if the order were swapped, EventB would never recieve it
*/
void EntityEvents::initialize() {
	/// registry convention:
	///REGISTER_EVENT_ID(Event, EventConvention);
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
which is very important, because if ComponentA sends and event, ComponentB will always recieve it,
but if the order were swapped, ComponentB would never recieve it
*/
void Components::initialize() {
	/// registry convention:
	///REGISTER_COMPONENT_ID(Component, ComponentConvention);
}
#pragma endregion Components
