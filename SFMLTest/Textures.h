#pragma once

#include "Constants.h"

#include <SFML/Graphics.hpp>

namespace Engine {

enum class TextureSet
{
	PLAYER_TEXTURES,

	NUM_TEXTURE_SETS
};

// A strip of textures represented by sprites
/*
struct SpriteStrip
{
	SpriteStrip(const sf::Texture& tex) : texture(tex) {}

	void Insert(const sf::IntRect& rect);
	const sf::Texture& texture;
	std::vector<sf::IntRect> rect;
};
*/

struct DirectionalRects
{
	std::vector<sf::IntRect> up;
	std::vector<sf::IntRect> down;
	std::vector<sf::IntRect> left;
	std::vector<sf::IntRect> right;
};

// TODO: Use autocode generation and compile time constructed objs
// TODO: Fix the raw art strips to support this, positions are currently scattered
struct TextureData
{
	TextureData(const char* spriteSheet);

	const std::string& GetSheet() const { return m_spriteSheet; }
	
	void SetIdle(unsigned int direction, unsigned int frame, unsigned int& size);
	void SetWalking(unsigned int direction, unsigned int frame, unsigned int& size);

	void UpdateSprite(const sf::IntRect& rect);
	const std::vector<sf::IntRect>& GetWalkDirectionStrip(unsigned int direction);
	
	//void AddSprite(const std::vector<sf::Sprite>& list, const sf::Texture& texture, const sf::IntRect& rect);

	std::vector<sf::IntRect> idle;
	DirectionalRects walking;

	sf::Texture texture;

	// The one Sprite we will be using to reprsent this texture. We call setTextureRect
	// to advance the animation to the next frame. The IntRects stored in our DirectionalRects
	// struct contain the frame data.
	// TODO: What about having a sprite for every animation frame and simply referencing it?
	// But then how do I "move" the sprite to render it from Animation.cpp? Just copy the
	// sprite to one owned by Animation.cpp and the set position on it???? No idea.
	sf::Sprite sprite;

	std::string m_spriteSheet;
};

struct PlayerTexData : public TextureData
{
	PlayerTexData();
};

class TextureDataFactory
{
public:
	static TextureData* Create(TextureSet set);
};

} //namespace Engine