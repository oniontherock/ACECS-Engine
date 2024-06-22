#ifndef __KEY_RECORDER_H__
#define __KEY_RECORDER_H__

#include <set>
#include <vector>

#include "SFML/Graphics.hpp"

enum KeyTransition {
	Pressed,
	Held,
	Released
};

struct InputEvent {
	sf::Event::EventType inputEventType;

	KeyTransition transitionType;
};

namespace InputRecorder {

	std::set<InputEvent> prevInputs;
	std::set<InputEvent> inputs;

	void updateInputs(sf::RenderWindow& window, sf::Event& event) {
		while (window.pollEvent(event)) {
			
		}
	}

	KeyTransition getKeyTransition(InputEvent input) {
		//if ()
	}
}


#endif