
#include <set>
#include <iostream>

#include "../Engine Modules/Input/InputInterface.hpp"

//#include "SFML/Graphics.hpp"


int main() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Window");
	window.setFramerateLimit(60);

	InputInterface::registerInput("Left", KeySet{ KeyEvent("A", Held), KeyEvent("LControl", Held) }, InputKeyLogic::And);
	InputInterface::registerInput("Right", KeySet{ KeyEvent("D", Held), KeyEvent("LControl", Held) }, InputKeyLogic::And);
	InputInterface::registerInput("Up", KeySet{ KeyEvent("W", Held), KeyEvent("LControl", Held) }, InputKeyLogic::And);
	InputInterface::registerInput("Down", KeySet{ KeyEvent("S", Held), KeyEvent("LControl", Held) }, InputKeyLogic::And);

	InputInterface::registerInput("Window Close", KeySet{ KeyEvent("Escape", KeyTransition::Released) });

	float x = 640;
	float y = 360;

	while (window.isOpen()) {

		float mouseScrollAmount = 0.f;
		sf::Vector2i mousePosition = sf::Mouse::getPosition();

		InputInterface::updateMouseScrollAmount(0.f);

		sf::Event event;

		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseMoved:
				InputInterface::updateMousePosition(event.mouseMove.x, event.mouseMove.y);
				break;
			case sf::Event::MouseWheelScrolled:
				InputInterface::updateMouseScrollAmount(event.mouseWheelScroll.delta);
				break;
			}
		}

		InputInterface::updateInput();

		x += float(InputInterface::getInputActive("Right") - InputInterface::getInputActive("Left")) / 0.1f;
		y += float(InputInterface::getInputActive("Down") - InputInterface::getInputActive("Up")) / 0.1f;

		if (InputInterface::getInputActive("Window Close")) {
			window.close();
		}


		window.clear(sf::Color::Black);

		sf::CircleShape circle(64);

		circle.setPosition(x, y);
		circle.setFillColor(sf::Color::White);

		window.draw(circle);
	
		window.display();
	}

	return 0;
}
