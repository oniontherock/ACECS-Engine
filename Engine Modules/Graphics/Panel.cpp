#include "Panel.hpp"
#include "../Input/InputInterface.hpp"

Panel::Panel(PanelRect _screenRect, PanelRect _viewRect, sf::Color _clearColor) :
	screenRect(_screenRect), viewRect(_viewRect), clearColor(_clearColor), viewRectSizeOriginal(_viewRect.getSize())
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

void Panel::viewZoomScale(float zoomFactor) {
	viewZoom *= zoomFactor;

	viewRect.left += (viewRect.getSize().x - (viewRect.getSize().x * zoomFactor)) / 2.f;
	viewRect.top += (viewRect.getSize().y - (viewRect.getSize().y * zoomFactor)) / 2.f;
}
void Panel::viewZoomSet(float zoomValue) {
	viewZoomScale(zoomValue / viewZoom);
}
float Panel::viewZoomGet() const {
	return viewZoom;
}

void Panel::viewMove(float moveX, float moveY) {
	viewRect.left += moveX;
	viewRect.top += moveY;
}
void Panel::viewMove(sf::Vector2f moveVec) {
	viewMove(moveVec.x, moveVec.y);
}

void Panel::viewUpdate() {

	sf::Vector2f newSize = viewRectSizeOriginal * viewZoom;

	viewRect.width = newSize.x;
	viewRect.height = newSize.y;

	view.setCenter(viewRect.getPosition() + (viewRect.getSize() / 2.f));
	view.setSize(viewRect.getSize());
	texture.setView(view);
}

const PanelView& Panel::viewGet() {
	return view;
}

sf::Vector2f Panel::panelMousePositionGet() {
	sf::Vector2f mousePos = sf::Vector2f(InputInterface::windowMousePositionGet());

	return mousePos - screenRect.getPosition();
}

sf::Vector2f Panel::viewMousePositionGet() {
	sf::Vector2f mousePos = panelMousePositionGet();

	float ratioX = viewRect.getSize().x / screenRect.getSize().x;
	float ratioY = viewRect.getSize().y / screenRect.getSize().y;

	sf::Vector2f viewCenter = viewRect.getPosition();
	mousePos += viewCenter;

	sf::Vector2f axis = mousePos - viewCenter;

	mousePos = sf::Vector2f(viewCenter.x + (axis.x * ratioX), viewCenter.y + (axis.y * ratioY));

	return mousePos;
}

uint16_t Panel::allocatedPanelIdsTotal = 0;

