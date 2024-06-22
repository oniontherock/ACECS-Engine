#include <cstdint>
#include <iostream>
#include <functional>

#include "../ECS/Components/Component.hpp"
#include "../ECS/Components/ComponentManager.hpp"

#include "../ECS/Entities/Entity.hpp"
#include "../ECS/Entities/EntityManager.hpp"

#include "../ECS/Systems/SystemManager.hpp"

#include "../User/Registry.hpp"

int main() {

	Components::initialize();
	EntityEvents::initialize();
	SystemRegistry::createSystems();

	EntityManager::updateEntities();

	return 0;
}
