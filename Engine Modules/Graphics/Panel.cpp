#include "Panel.hpp"

Panel::Panel(PanelRect _screenRect, PanelRect _viewRect, sf::Color _clearColor) :
	screenRect(_screenRect), viewRect(_viewRect), clearColor(_clearColor)
{
	textureCreate();
	viewCreate();
}

void Panel::textureCreate() {
	texture.create(unsigned int(screenRect.width), unsigned int(screenRect.height));
}
void Panel::viewCreate() {
	view = PanelView(viewRect);
}
inline void Panel::vertexArrayDraw(const sf::VertexArray& vertexArray, const sf::RenderStates& states) {
	texture.draw(vertexArray, states);
}
void Panel::panelDrawObjects() {
	panelUpdate();
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
void Panel::viewZoom(float zoomFactor) {
	sf::Vector2f newSize = viewRect.getSize() * zoomFactor;

	sf::Vector2f cornerChangeDist = viewRect.getSize() - newSize;

	viewRect.width = newSize.x;
	viewRect.height = newSize.y;

	viewRect.left += (cornerChangeDist.x / 2.f);
	viewRect.top += (cornerChangeDist.y / 2.f);
}
void Panel::viewMove(float moveX, float moveY) {
	viewRect.left += moveX;
	viewRect.top += moveY;
}
void Panel::viewMove(sf::Vector2f moveVec) {
	viewMove(moveVec.x, moveVec.y);
}

void Panel::viewUpdate() {
	view.setCenter(viewRect.getPosition() + (viewRect.getSize() / 2.f));
	view.setSize(viewRect.getSize());
	texture.setView(view);
}

uint16_t Panel::allocatedPanelIdsTotal = 0;

