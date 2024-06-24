#include "InputRegistry.hpp"

void initializeInput() {
	InputRegistry::registerInputs();
}

void InputRegistry::registerInputs() {
	InputInterface::registerInput("Left", KeySet{ KeyEvent("A", Held) });
	InputInterface::registerInput("Right", KeySet{ KeyEvent("D", Held) });
	InputInterface::registerInput("Up", KeySet{ KeyEvent("W", Held) });
	InputInterface::registerInput("Down", KeySet{ KeyEvent("S", Held) });
	InputInterface::registerInput("Set Position", KeySet{ KeyEvent("Mouse Left", Held), KeyEvent("LControl", Held) }, InputKeyLogic::And);

	InputInterface::registerInput("Window Close", KeySet{ KeyEvent("Escape", KeyTransition::Released) });
}
