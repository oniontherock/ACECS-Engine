#ifndef __KEY_RECORDER_H__
#define __KEY_RECORDER_H__

#include <cstdint>
#include <set>

#include "SFML/Graphics.hpp"


enum InputTransition : uint8_t {
	Released,
	Held,
	Pressed,
};

// PrimitiveInput is basically just a dumb input,
// it only knows it's event type, and nothing about transitions.
// it's used by the InputRecorder to create more intelligent InputEvents
typedef sf::Event::EventType PrimitiveInput;

struct InputEvent {

	InputEvent() = default;
	InputEvent(PrimitiveInput _inputEventType) : inputEventType(_inputEventType) {};
	InputEvent(PrimitiveInput _inputEventType, InputTransition _transitionType) : inputEventType(_inputEventType), transitionType(_transitionType) {};

	PrimitiveInput inputEventType;

	InputTransition transitionType = Pressed;
};

// records input and assigns it a transition type
namespace InputRecorder {


	// set of inputs from the previous frame
	std::set<PrimitiveInput> inputsPrimitivePrev;
	// set of inputs from the current frame
	std::set<PrimitiveInput> inputsPrimitive;

	std::set<InputEvent> inputEvents;

	// records every input in "event"
	inline void updateInputs(sf::RenderWindow& window, sf::Event& event) {
		
		inputsPrimitivePrev = inputsPrimitive;

		while (window.pollEvent(event)) {
			
			if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed) {
				inputsPrimitive.insert(event.type);
			}
			else if (event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonReleased) {
				inputsPrimitive.erase(event.type);
			}
		}

		std::set<PrimitiveInput> inputsPrimitiveUnion;
		std::set_union(inputsPrimitive.begin(), inputsPrimitive.end(), inputsPrimitivePrev.begin(), inputsPrimitivePrev.end(), inputsPrimitiveUnion);

		inputEvents.clear();
		for (PrimitiveInput curInput : inputsPrimitiveUnion) {
			inputEvents.insert(getInputEvent(curInput));
		}

	}

	// sets an InputEvent's transitionType,
	inline InputEvent getInputEvent(PrimitiveInput input) {

		bool pressedPrev = inputsPrimitivePrev.count(input);
		bool pressedNow = inputsPrimitive.count(input);

		// we get the keyTransition by getting the difference in key presses between now and last frame
		// this works because:
		// 0 - 1 = -1|Released
		// 1 - 1 = 0|Held
		// 1 - 0 = 1|Pressed
		uint8_t keyTransition = (pressedNow - pressedPrev) + 1;
	
		return InputEvent(input, static_cast<InputTransition>(keyTransition));
	}
}


#endif