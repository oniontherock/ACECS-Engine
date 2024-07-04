#ifndef __PANEL_H__
#define __PANEL_H__

#include "SFML/Graphics.hpp"

typedef sf::View PanelView;
typedef sf::RenderTexture PanelScreenTexture;
typedef sf::FloatRect PanelRect;

typedef const char* PanelName;

struct Panel {

	Panel() {
		textureCreate();
		viewCreate();
	};
	Panel(PanelRect _screenRect, PanelRect _viewRect, sf::Color _clearColor) :
		screenRect(_screenRect), viewRect(_viewRect), clearColor(_clearColor)
	{
		textureCreate();
		viewCreate();
	}

	void textureCreate();
	void viewCreate();
	template <typename T>
	inline void objectDraw(const T& drawableObject) {
		texture.draw(drawableObject);
	}
	void vertexArrayDraw(const sf::VertexArray& vertexArray, const sf::RenderStates& states);
	void panelRender(sf::RenderWindow& renderWindowMain);
	void panelClear();
	void zoomView(float zoomFactor);

	// the Panel's position and dimensions on the screen
	PanelRect screenRect{ 0, 0, 0, 0 };

	// the Panel's position and dimensions in it's drawn environment.
	// as an example, if an object is drawn at 250x250, and the viewRect is 0x0x500x500,
	// then the object will be drawn in the center of the screenRect
	PanelRect viewRect{ 0, 0, 0, 0 };
private:
	// the panel's texture, this is what is actual drawn on, and it's rendered to the main game window
	PanelScreenTexture texture;
	// the panel's view,
	PanelView view;
	// color to be used when clearing
	sf::Color clearColor;

	void viewUpdate();

	static inline uint16_t allocatedPanelIdsTotal = 0;
};

#endif