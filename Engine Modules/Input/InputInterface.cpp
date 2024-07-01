#include "InputInterface.hpp"

#include "Input Events/InputManager.hpp"

bool Input::Interface::inputGetActive(const InputName& name) {
	try {

		const uint16_t& indexFromName = InputManager::inputIndexFind(name);

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

sf::Vector2i Input::Interface::mousePositionGet() {
	return InputManager::mouseData.position;
}
float Input::Interface::mouseScrollAmountGet() {
	return InputManager::mouseData.scrollAmount;
}

void Input::Interface::mousePositionUpdate(sf::Vector2i position) {
	InputManager::mouseData.position = position;
}
void Input::Interface::mousePositionUpdate(uint16_t x, uint16_t y) {
	InputManager::mouseData.position = sf::Vector2i(x, y);
}
void Input::Interface::mouseScrollAmountUpdate(float scrollAmount) {
	InputManager::mouseData.scrollAmount = scrollAmount;
}

void Input::Interface::inputRegister(const InputName& name, const KeySet& keys) {
	KeyRecorder::keySetRegister(keys);
	InputManager::namesToIndexesMap.insert({ name, uint16_t(InputManager::inputs.size()) });
	InputManager::inputs.push_back(InputEvent(name, keys));
}

void Input::Interface::inputRegister(const InputName& name, const KeySet& keys, InputKeyLogic keyLogic) {
	KeyRecorder::keySetRegister(keys);
	InputManager::namesToIndexesMap.insert({ name, uint16_t(InputManager::inputs.size()) });
	InputManager::inputs.push_back(InputEvent(name, keys, keyLogic));
}

void Input::Interface::inputUpdate() {
	KeyRecorder::keysUpdate();
	InputManager::inputEventsUpdate();
}

void Input::Interface::eventsProcess(sf::RenderWindow& window) {

	sf::Event event;

	while (window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::MouseMoved:
			mousePositionUpdate(sf::Vector2i(window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y))));
			break;
		case sf::Event::MouseWheelScrolled:
			mouseScrollAmountUpdate(event.mouseWheelScroll.delta);
			break;
		}
	}
}
