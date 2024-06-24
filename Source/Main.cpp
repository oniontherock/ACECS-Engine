#include <set>
#include <iostream>

#include "../Engine Modules/ECS.hpp"
#include "../Engine Modules/Input.hpp"

#include "../Engine Modules/User/ECSRegistry.hpp"
#include "../Engine Modules/User/InputRegistry.hpp"

int main() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Window");
	window.setFramerateLimit(60);

	initializeECS();
	initializeInput();

	float x = 640;
	float y = 360;


	while (window.isOpen()) {
		InputInterface::handleEvents(window);
		InputInterface::updateInput();

		if (InputInterface::getInputActive("Set Position")) {

			auto mousePos = InputInterface::getMousePosition();

			x = mousePos.x;
			y = mousePos.y;
		}

		x += float(InputInterface::getInputActive("Right") - InputInterface::getInputActive("Left")) / 0.1f;
		y += float(InputInterface::getInputActive("Down") - InputInterface::getInputActive("Up")) / 0.1f;

		if (InputInterface::getInputActive("Window Close")) {
			window.close();
		}


		window.clear(sf::Color::Black);

		sf::CircleShape circle(64);

		circle.setOrigin(64, 64);
		circle.setPosition(x, y);
		circle.setFillColor(sf::Color::White);

		window.draw(circle);
	
		window.display();
	}

	return 0;
}
