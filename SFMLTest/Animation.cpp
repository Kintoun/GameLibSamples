#include "Animation.h"

#include "Log.h"

#include "cassert"

namespace Engine {

Animation::Animation(TextureSet set, unsigned int ticksPerFrame) : 
	m_facing(Facing::SOUTH), m_aniLoops(0), m_aniCount(0), m_aniFrame(0),
	m_currentFrameSetSize(0), m_ticksPerFrame(ticksPerFrame)
{
	// TODO: Read scale from texData
	m_texData = TextureDataFactory::Create(set);
	m_sprite.setTexture(m_texData->texture);
	m_sprite.setScale(4.0f, 4.0f);

	SetAnimation(AnimationType::IDLE, Facing::SOUTH);
}

Animation::~Animation()
{
	delete m_texData;
}

void Animation::Update(Facing facing, Event event)
{
	AnimationType type = EventToAnimationType(event);

	// Are we changing to a new animation based on input?
	if ((facing != m_facing || type != m_type)
		&& (!IsUninterruptableAnimation(m_type) 
			|| (IsUninterruptableAnimation(m_type) && m_aniLoops > 0)))
	{
		// Set to new animation type and facing
		m_type = type;
		m_facing = facing;
		m_aniFrame = 0;
		m_aniLoops = 0;
		SetAnimation(m_type, m_facing, m_aniFrame);
	}
	else
	{
		// Same animation and facing, just advance frame if needed
		if (m_currentFrameSetSize > 1)
		{
			m_aniCount++;
			if (m_aniCount >= m_ticksPerFrame)
			{
				// Advance frame and set new animation frame.
				if (++m_aniFrame >= m_currentFrameSetSize)
				{
					m_aniLoops++;
					m_aniFrame = 0;
				}
				SetAnimation(m_type, m_facing, m_aniFrame);
			}
		}
	}
}

void Animation::Render(sf::RenderWindow& window, const sf::Vector2f& position)
{
	if (m_texData)
	{
		m_sprite.setPosition(position);
		window.draw(m_sprite);
	}
}

AnimationType Animation::EventToAnimationType(Event event)
{
	// Priority matters here!
	if (event & EventType::ATTACKING)
		return AnimationType::ATTACK;
	if (event & EventType::MOVING)
		return AnimationType::WALK;
	if (event == EventType::NO_EVENT)
		return AnimationType::IDLE;
	else
	{
		LOGERROR << "Unable to process EventType: " << event;
		return AnimationType::IDLE;
	}
}

// TODO: Turn this into a static data structure lookup "AnimationTypeData"
bool Animation::IsUninterruptableAnimation(AnimationType type)
{
	switch (type)
	{
	case AnimationType::ATTACK:
		return true;
	case AnimationType::WALK:
	case AnimationType::IDLE:
		return false;
	default:
		LOGERROR << "Unknown AnimationType: " << static_cast<int>(type);
		return false;
	}
}

const sf::Sprite& Animation::GetSprite() const
{
	return m_sprite;
}

void Animation::UpdateSprite(const sf::IntRect& rect)
{
	// TODO: Origin should be configurable, not hardcoded here.
	m_sprite.setTextureRect(rect);
	m_sprite.setOrigin(std::abs(rect.width)/2, std::abs(rect.height));
}

void Animation::SetAnimation(AnimationType type, Facing facing, unsigned int frame)
{
//	LOGINFO << "SetAnimation type: " << static_cast<int>(type) << " facing: "
//		<< facing << " frame: " << frame;

	// new frame, reset our count
	m_aniCount = 0;

	// Lookup the texture rect for this type, facing, frame
	AnimationStrip& animStrip = m_texData->m_animations[type][facing];
	m_currentFrameSetSize = animStrip.size();

	assert(frame < m_currentFrameSetSize);
	UpdateSprite(animStrip[frame]);
}

} //namespace Engine