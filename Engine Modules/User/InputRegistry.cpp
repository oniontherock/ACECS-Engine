#include "InputRegistry.hpp"

void initializeInput() {
	InputRegistry::registerInputs();
}

void InputRegistry::registerInputs() {
	//Input::Interface inputInterface{};

	//inputInterface.registerInput("Left", KeySet{ KeyEvent("A", Held) });
	//inputInterface.registerInput("Right", KeySet{ KeyEvent("D", Held) });
	//inputInterface.registerInput("Up", KeySet{ KeyEvent("W", Held) });
	//inputInterface.registerInput("Down", KeySet{ KeyEvent("S", Held) });
	//inputInterface.registerInput("Set Position", KeySet{ KeyEvent("Mouse Left", Held), KeyEvent("LControl", Held) }, InputKeyLogic::And);

	//inputInterface.registerInput("Window Close", KeySet{ KeyEvent("Escape", KeyTransition::Pressed) });
}
