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
	MouseData() {};

	sf::Vector2i position;
	float scrollAmount = 0.f;
};

namespace InputManager {

	inline std::vector<InputEvent> inputs;
	inline std::map<InputName, uint16_t> namesToIndexesMap;
	
	inline MouseData mouseData;

	inline bool keySetContains(const KeySet& set, const KeyEvent& keyEvent) {
		for (const auto& curSetKeyEvent : set) {
			if (keyEvent == curSetKeyEvent) {
				return true;
			}
		}

		return false;
	}

	inline bool inputEventIsActive(const InputEvent& inputEvent, const KeySet& keySet) {
		for (KeyEvent curInputKey : inputEvent.linkedKeyEvents) {
			if (keySetContains(keySet, curInputKey)) {
				if (inputEvent.keyLogic == Or) {
					return true;
				}
			}
			else if (inputEvent.keyLogic == And) {
				return false;
			}
		}

		// return whether the keyLogic is equal to And because if it is and, and we made it to the end, then we never found anything false,
		// if it's not And, then it means it's Or and we never found anything true
		return inputEvent.keyLogic == And;
	}

	inline void inputEventsUpdate() {
		for (InputEvent& curInput : inputs) {
			curInput.isActive = false;
		}

		KeySet keys = KeyRecorder::keysGet();

		for (InputEvent& curInputEvent : inputs) {
			curInputEvent.isActive = inputEventIsActive(curInputEvent, keys);
		}
	}

	// registers an InputEvent to inputs
	inline void inputRegister(const InputName& name, const KeySet& keys) {
		inputs.push_back(InputEvent(name, keys));
	}
	// registers an InputEvent to inputs
	inline void inputRegister(const InputName& name, const KeySet& keys, const InputKeyLogic keyLogic) {
		inputs.push_back(InputEvent(name, keys, keyLogic));
	}

	inline uint16_t inputIndexFind(const InputName& name) {
		return namesToIndexesMap[name];
	}
}



#endif