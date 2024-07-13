#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__

#include <map>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <iostream>

#include "SFML/Graphics.hpp"

#include "../Key Events/KeyRecorder.hpp"
#include "InputEventDefinitions.hpp"

struct MouseData {
	sf::Vector2i position;
	float scrollAmount = 0.f;
};

namespace InputManager {

	extern std::vector<InputEvent> inputs;
	extern std::map<InputName, uint16_t> namesToIndexesMap;
	
	extern MouseData mouseData;

	bool keySetContains(const KeySet& set, const KeyEvent& keyEvent);

	bool inputEventIsActive(const InputEvent& inputEvent, const KeySet& keySet);

	void inputEventsUpdate();

	// registers an InputEvent to inputs
	void inputRegister(const InputName& name, const KeySet& keys);
	// registers an InputEvent to inputs
	void inputRegister(const InputName& name, const KeySet& keys, const InputKeyLogic keyLogic);

	uint16_t inputIndexFind(const InputName& name);
}



#endif