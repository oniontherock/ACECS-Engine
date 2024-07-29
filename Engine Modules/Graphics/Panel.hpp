#ifndef __PANEL_H__
#define __PANEL_H__

#include "../Input/InputInterface.hpp"
#include "SFML/Graphics.hpp"
#include "WindowHolder.hpp"
#include <functional>

typedef sf::View PanelView;
typedef sf::RenderTexture PanelScreenTexture;
typedef sf::FloatRect PanelRect;

enum PanelTypes : uint16_t;

typedef PanelTypes PanelName;

struct Panel {

	Panel() = default;
	Panel(PanelRect _screenRect, PanelRect _viewRect, sf::Color _clearColor);
	virtual ~Panel() {};

	void textureCreate();
	void viewCreate();

	template <typename T>
	inline void objectDraw(const T& drawableObject) {
		texture.draw(drawableObject);
	}
	void vertexArrayDraw(const sf::VertexArray& vertexArray, const sf::RenderStates& states);

	void viewZoomScale(float zoomFactor);
	void viewZoomSet(float zoomValue);
	float viewZoomGet() const;
	void viewMove(float moveX, float moveY);
	void viewMove(sf::Vector2f moveVec);

	void panelDrawObjects();
	void panelRender(sf::RenderWindow& renderWindowMain);
	// clears the panel with a transparent color
	void panelClear();


	// gets the mouse position relative to the panel's window position
	sf::Vector2f panelMousePositionGet();
	// gets the mouse position relative to the panel's view position
	sf::Vector2f viewMousePositionGet();

	const PanelView& viewGet();

	// the Panel's position and dimensions on the screen
	PanelRect screenRect{ 0, 0, 0, 0 };

	// the Panel's position and dimensions in it's drawn environment.
	// as an example, if an object is drawn at 250x250, and the viewRect is 0x0x500x500,
	// then the object will be drawn in the center of the screenRect
	PanelRect viewRect{ 0, 0, 0, 0 };

	// color used when clearing panel
	sf::Color clearColor;
private:
	// the panel's texture, this is what is actual drawn on, and it's rendered to the main game window
	PanelScreenTexture texture;
	// the panel's view,
	PanelView view;

	sf::Vector2f viewRectSizeOriginal;

	float viewZoom = 1.f;

	virtual void panelUpdate() = 0;

	void viewUpdate();

	static uint16_t allocatedPanelIdsTotal;
};

typedef std::unique_ptr<Panel> PanelPtr;

#endif