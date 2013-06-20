#pragma once

#include "Textures.h"
#include "Constants.h"
#include "Events.h"

#include <SFML/System.hpp>

namespace Engine {

class Animation
{
public:
	Animation(TextureSet set, unsigned int ticksPerFrame);
	~Animation();

	void Update(Facing facing, Event event);
	void Render(sf::RenderWindow& window, const sf::Vector2f& position);

	const sf::Sprite& GetSprite() const;

private:
	AnimationType EventToAnimationType(Event event);
	bool IsUninterruptableAnimation(AnimationType type);
	void SetAnimation(AnimationType type, Facing facing, unsigned int frame = 0);
	void UpdateSprite(const sf::IntRect& rect);

	// Our renderable obj.
	sf::Sprite m_sprite;

	// Our raw texture data. The sprite sheet and the IntRects for each
	// frame of animation.
	TextureData* m_texData;
	
	// facing of the moving object, so we know which texture data to use.
	Facing m_facing;

	// Current animation type
	AnimationType m_type;

	// How many times the current animation has looped
	unsigned int m_aniLoops;

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