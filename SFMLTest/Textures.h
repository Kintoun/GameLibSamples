#pragma once

#include "Direction.h"

#include <SFML/Graphics.hpp>

namespace Engine {

enum class AnimationType
{
	IDLE,
	WALK,
	ATTACK
};

enum class TextureSet
{
	PLAYER_TEXTURES,

	NUM_TEXTURE_SETS
};

typedef std::vector<sf::IntRect> AnimationStrip;
typedef std::map<Facing, AnimationStrip> DirectionalStrips;
typedef std::map<AnimationType, DirectionalStrips> Animations;

// TODO: Use autocode generation and compile time constructed objs
// TODO: Fix the raw art strips to support this, positions are currently scattered
struct TextureData
{
	TextureData(const char* spriteSheet);

	Animations m_animations;

	sf::Texture texture;
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