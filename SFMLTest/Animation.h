#pragma once

#include "Textures.h"
#include "Constants.h"

#include <SFML/System.hpp>

namespace Engine {

enum class AnimationType
{
	IDLE,
	WALK
};

class Animation
{
public:
	Animation(TextureSet set, unsigned int ticksPerFrame);
	~Animation();

	void Update(unsigned int direction);
	void Render(sf::RenderWindow& window, const sf::Vector2f& position);

	sf::Sprite* GetSprite() const;

private:
	void SetAnimation(AnimationType type, unsigned int direction, unsigned int frame = 0);

	void ChangeDirection(unsigned int direction);
	void AdvanceFrame();

	// Our raw texture data
	TextureData* texData;
	
	// Direction of the moving object, so we know which texture data to use.
	unsigned int m_direction;

	// Current animation type
	AnimationType m_type;

	// How many "counts" this current animation frame has been displaying for.
	unsigned int m_aniCount;

	// The current frame of the animation.
	unsigned int m_aniFrame;

	// How many frames there are for the currently animating set
	unsigned int m_currentFrameSetSize;

	// How many game updates occur before we advance our animation frame
	unsigned int m_ticksPerFrame;
};

} // namespace Engine