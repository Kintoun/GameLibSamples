#pragma once

#include "Constants.h"

#include <SFML/Graphics.hpp>

namespace Engine {

enum class TextureSet
{
	PLAYER_TEXTURES,

	NUM_TEXTURE_SETS
};

struct CardinalRects
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
	
	std::vector<sf::IntRect> idle;
	CardinalRects walking;

	sf::Texture texture;
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