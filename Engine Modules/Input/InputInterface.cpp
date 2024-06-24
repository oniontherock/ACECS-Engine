#include "InputInterface.hpp"

#include "Input Events/InputManager.hpp"

bool InputInterface::getInputActive(const InputName& name) {
	try {

		const uint16_t& indexFromName = InputManager::getIndexFromName(name);

		if (indexFromName < InputManager::inputs.size()) {
			return InputManager::inputs[indexFromName].isActive;
		}
		else {
			throw (std::invalid_argument(name));
		}
	}
	catch (const std::invalid_argument& e) {
		std::cout << "ERROR, INVALID INPUT NAME: " << "\"" << e.what() << "\"" << std::endl;
		return false;
	}
}

sf::Vector2i InputInterface::getMousePosition() {
	return InputManager::mouseData.position;
}
float InputInterface::getMouseScrollAmount() {
	return InputManager::mouseData.scrollAmount;
}

void InputInterface::updateMousePosition(sf::Vector2i position) {
	InputManager::mouseData.position = position;
}
void InputInterface::updateMousePosition(uint16_t x, uint16_t y) {
	InputManager::mouseData.position = sf::Vector2i(x, y);
}
void InputInterface::updateMouseScrollAmount(float scrollAmount) {
	InputManager::mouseData.scrollAmount = scrollAmount;
}

void InputInterface::registerInput(const InputName& name, const KeySet& keys) {
	KeyRecorder::registerKeySet(keys);
	InputManager::namesToIndexesMap.insert({ name, uint16_t(InputManager::inputs.size()) });
	InputManager::inputs.push_back(InputEvent(name, keys));
}

void InputInterface::registerInput(const InputName& name, const KeySet& keys, InputKeyLogic keyLogic) {
	KeyRecorder::registerKeySet(keys);
	InputManager::namesToIndexesMap.insert({ name, uint16_t(InputManager::inputs.size()) });
	InputManager::inputs.push_back(InputEvent(name, keys, keyLogic));
}

void InputInterface::updateInput() {
	KeyRecorder::updateKeys();
	InputManager::updateInputEvents();
}

void InputInterface::handleEvents(sf::RenderWindow& window) {

	sf::Event event;

	while (window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::MouseMoved:
			updateMousePosition(sf::Vector2i(window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y))));
			break;
		case sf::Event::MouseWheelScrolled:
			updateMouseScrollAmount(event.mouseWheelScroll.delta);
			break;
		}
	}
}
