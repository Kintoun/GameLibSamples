#pragma once

#include "Textures.h"
#include "Constants.h"

#include <SFML/System.hpp>

namespace Engine {

class Animation
{
public:
	Animation(TextureSet set, unsigned int ticksPerFrame);
	~Animation();

	void Update(unsigned int direction);
	void Render(sf::RenderWindow& window, const sf::Vector2f& position);

	const sf::Sprite& GetSprite() const;

private:
	void ChangeDirection(unsigned int direction);
	void AdvanceFrame();
	void SetAnimation(AnimationType type, unsigned int direction, unsigned int frame = 0);
	const std::vector<sf::IntRect>& GetAnimationStrip(AnimationType type, unsigned int direction);
	void UpdateSprite(const sf::IntRect& rect);

	// Our renderable obj.
	sf::Sprite m_sprite;

	// Our raw texture data. The sprite sheet and the IntRects for each
	// frame of animation.
	TextureData* m_texData;
	
	// Direction of the moving object, so we know which texture data to use.
	unsigned int m_direction;

	// Current animation type
	AnimationType m_type;

	// How many "counts" this current animation frame has been displaying for.
	unsigned int m_aniCount;

	// The current frame of the animation.
	unsigned int m_aniFrame;

	// How many frames there are for the currently animating set
	// TODO: Get rid of this, use a boost::circularList
	unsigned int m_currentFrameSetSize;

	// How many game updates occur before we advance our animation frame
	unsigned int m_ticksPerFrame;
};

} // namespace Engine