#ifndef __INPUT_INTERFACE_H__
#define __INPUT_INTERFACE_H__

#include "../SFMLInclude/SFML/Graphics.hpp"
#include "Input Events/InputEventDefinitions.hpp"
#include "Key Events/KeyEventDefinitions.hpp"

namespace Input {
	class Interface {
	public:
		bool getInputActive(const InputName& name);

		sf::Vector2i getMousePosition();
		float getMouseScrollAmount();

		void updateMouseScrollAmount(float scrollAmount);
		void updateMousePosition(sf::Vector2i position);
		void updateMousePosition(uint16_t x, uint16_t y);

		// registers an InputEvent to inputs
		void registerInput(const InputName& name, const KeySet& keys);
		// registers an InputEvent to inputs
		void registerInput(const InputName& name, const KeySet& keys, InputKeyLogic keyLogic);

		void updateInput();

		void handleEvents(sf::RenderWindow& window);
	};
}

#endif