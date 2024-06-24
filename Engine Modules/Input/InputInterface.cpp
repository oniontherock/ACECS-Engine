#include "InputInterface.hpp"

#include "Input Events/InputManager.hpp"

bool InputInterface::getInputActive(InputName name) {
	return InputManager::inputs[InputManager::getIndexFromName(name)].isActive;
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

void InputInterface::registerInput(InputName name, KeySet keys) {
	KeyRecorder::registerKeySet(keys);
	InputManager::namesToIndexesMap.insert({ name, uint16_t(InputManager::inputs.size()) });
	InputManager::inputs.push_back(InputEvent(name, keys));
}

void InputInterface::registerInput(InputName name, KeySet keys, InputKeyLogic keyLogic) {
	KeyRecorder::registerKeySet(keys);
	InputManager::namesToIndexesMap.insert({ name, uint16_t(InputManager::inputs.size()) });
	InputManager::inputs.push_back(InputEvent(name, keys, keyLogic));
}

void InputInterface::updateInput() {
	KeyRecorder::updateKeys();
	InputManager::updateInputEvents();
}
