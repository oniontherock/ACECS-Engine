#include "Panel.hpp"

void Panel::textureCreate() {
	texture.create(screenRect.width, screenRect.height);
}
void Panel::viewCreate() {
	view = PanelView(viewRect);
}
inline void Panel::vertexArrayDraw(const sf::VertexArray& vertexArray, const sf::RenderStates& states) {
	texture.draw(vertexArray, states);
}
void Panel::panelRender(sf::RenderWindow& renderWindowMain) {
	viewUpdate();
	texture.display();

	sf::Sprite sprite(texture.getTexture());
	sprite.setPosition(screenRect.getPosition());

	renderWindowMain.draw(sprite);
}
void Panel::panelClear() {
	texture.clear(clearColor);
}
void Panel::zoomView(float zoomFactor) {
	sf::Vector2f newSize = viewRect.getSize() * zoomFactor;

	sf::Vector2f cornerChangeDist = viewRect.getSize() - newSize;

	viewRect.width = newSize.x;
	viewRect.height = newSize.y;

	viewRect.left += (cornerChangeDist.x / 2.f);
	viewRect.top += (cornerChangeDist.y / 2.f);
}

void Panel::viewUpdate() {
	view.setCenter(viewRect.getPosition() + (viewRect.getSize() / 2.f));
	view.setSize(viewRect.getSize());
	texture.setView(view);
}

