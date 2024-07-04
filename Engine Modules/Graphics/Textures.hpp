#ifndef __TEXTURES_H__
#define __TEXTURES_H__

#include "SFML/Graphics.hpp"

struct NonCopyable {
protected:
	NonCopyable() {}
	~NonCopyable() {}
private:
	NonCopyable(const NonCopyable&) {}
	NonCopyable& operator=(const NonCopyable&) {}
};

// A simple texture atlas, it is basically just a regular sf::Texture
struct TextureAtlas : NonCopyable {

	TextureAtlas() = default;
	TextureAtlas(sf::Texture _texture) :
		texture(_texture)
	{}

	sf::Texture texture;
};

// similar to a TextureAtlas, but has uniformly sized sub-images, and contains extra information about the texture's dimensions
struct TextureSheet : public TextureAtlas {

	TextureSheet() = default;
	TextureSheet(sf::Texture _texture, sf::Vector2u _frameDimensions, uint16_t _frameCount) {
		texture = _texture;
		sheetDimensions = _frameDimensions;
		frameCount = _frameCount;
		initializeFrameDimensions();
	}
	TextureSheet(sf::Texture _texture, uint16_t _frameDimensionsX, uint16_t _frameDimensionsY, uint16_t _frameCount) {
		texture = _texture;
		sheetDimensions = sf::Vector2u(_frameDimensionsX, _frameDimensionsY);
		frameCount = _frameCount;
		initializeFrameDimensions();
	}

	inline void initializeFrameDimensions() {
		frameDimensions = sf::Vector2u(texture.getSize().x / sheetDimensions.x, texture.getSize().y / sheetDimensions.y);
	}

	// the dimensions of each individual frame in pixels, not to be confused with sheetDimensions
	sf::Vector2u frameDimensions;

	// the dimensions of the sprite sheet in frames, keep in mind this is NOT just the texture's dimensions,
	// the x component is the amount of X frames, and the y component is the amount of Y frames.
	// so if we have a SpriteSheet/TextureSheet that is an animation with rows 3 frames wide, and columns 4 frames long, then this will be 3x4
	sf::Vector2u sheetDimensions;

	// the actual amount of frames in the sheet,
	// this exists because the sheet may have a few blank cells in it's last row, and we can use this to avoid those blank rows
	uint16_t frameCount;
};

#endif