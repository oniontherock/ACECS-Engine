#ifndef __PANEL_H__
#define __PANEL_H__

#include "SFML/Graphics.hpp"

typedef sf::View PanelView;
typedef sf::RenderTexture PanelScreenTexture;

typedef const char* PanelName;

struct Panel {

	Panel() {
		textureCreate();
		viewCreate();
	};
	Panel(sf::FloatRect _screenRect, sf::FloatRect _viewRect) :
		screenRect(_screenRect), viewRect(_viewRect)
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
	void panelClear(const sf::Color& color);
	void zoomView(float zoomFactor);

	// the Panel's position and dimensions on the screen
	sf::FloatRect screenRect{ 0, 0, 0, 0 };

	// the Panel's position and dimensions in it's drawn environment.
	// as an example, if an object is drawn at 250x250, and the viewRect is 0x0x500x500,
	// then the object will be drawn in the center of the screenRect
	sf::FloatRect viewRect{ 0, 0, 0, 0 };

private:
	// the panel's texture, this is what is actual drawn on, and it's rendered to the main game window
	PanelScreenTexture texture;
	// the panel's view,
	PanelView view;

	void viewUpdate();
};

#endif