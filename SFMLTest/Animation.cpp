#include "Animation.h"

#include "Log.h"

namespace Engine {

Animation::Animation(TextureSet set, unsigned int ticksPerFrame) : 
	m_direction(0), m_aniCount(0), m_aniFrame(0), m_currentFrameSetSize(0),
	m_ticksPerFrame(ticksPerFrame)
{
	texData = TextureDataFactory::Create(set);
	SetAnimation(AnimationType::IDLE, Direction::DOWN);
}

Animation::~Animation()
{
	delete texData;
}

void Animation::Update(unsigned int direction)
{
	if (direction != m_direction)
	{
		ChangeDirection(direction);
	}
	else
	{	
		AdvanceFrame();
	}
}

void Animation::Render(sf::RenderWindow& window, const sf::Vector2f& position)
{
	if (texData)
	{
		texData->sprite.setPosition(position);
		window.draw(texData->sprite);
	}
}

void Animation::ChangeDirection(unsigned int direction)
{
	// Idle
	if (direction == 0)
	{
		// previous direction shall be our "facing"
		SetAnimation(AnimationType::IDLE, m_direction);
	}
	else
	{
		SetAnimation(AnimationType::WALK, direction);
	}

	m_aniFrame = 0;
	m_direction = direction;
}

void Animation::AdvanceFrame()
{
	if (m_currentFrameSetSize > 1)
	{
		m_aniCount++;
		if (m_aniCount >= m_ticksPerFrame)
		{
			m_aniFrame = ++m_aniFrame % m_currentFrameSetSize;
			SetAnimation(m_type, m_direction, m_aniFrame);
		}
	}
}

sf::Sprite* Animation::GetSprite() const
{
	if (texData)
		return &texData->sprite;
	return NULL;
}

void Animation::SetAnimation(AnimationType type, unsigned int direction, unsigned int frame)
{
	// new frame, reset our count
	m_aniCount = 0;

//	LOGINFO << "SetAnimation type: " << static_cast<int>(type) << " direction: "
//		<< direction << " frame: " << frame;

	switch(type)
	{
	case AnimationType::IDLE:
		texData->SetIdle(direction, frame, m_currentFrameSetSize);
		break;
	case AnimationType::WALK:
		texData->SetWalking(direction, frame, m_currentFrameSetSize);
		break;
	default:
		LOGERROR << "Unsupported animation type: " << static_cast<int>(type);
		break;
	}

	m_type = type;
}

} //namespace Engine