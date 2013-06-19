#include "Animation.h"

#include "Log.h"

#include "cassert"

namespace Engine {

Animation::Animation(TextureSet set, unsigned int ticksPerFrame) : 
	m_direction(0), m_aniCount(0), m_aniFrame(0), m_currentFrameSetSize(0),
	m_ticksPerFrame(ticksPerFrame)
{
	// TODO: Read scale from texData
	m_texData = TextureDataFactory::Create(set);
	m_sprite.setTexture(m_texData->texture);
	m_sprite.setScale(4.0f, 4.0f);

	SetAnimation(AnimationType::IDLE, Direction::DOWN);
}

Animation::~Animation()
{
	delete m_texData;
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
	if (m_texData)
	{
		m_sprite.setPosition(position);
		window.draw(m_sprite);
	}
}

void Animation::ChangeDirection(unsigned int direction)
{
	if (direction == 0)
	{
		// User previous direction as our "facing"
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
	// Nothing to advance if we don't have additional frames.
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

DirectionIndex MakeDirectionIndexable(unsigned int direction, unsigned int prevDirection)
{
	if (direction & Direction::UP)
		return DirectionIndex::UP_IDX;
	if (direction & Direction::DOWN)
		return DirectionIndex::DOWN_IDX;
	if (direction & Direction::LEFT)
		return DirectionIndex::LEFT_IDX;
	if (direction & Direction::RIGHT)
		return DirectionIndex::RIGHT_IDX;
	return DirectionIndex::DOWN_IDX; // by default no direction shows us "facing down"
}

void Animation::SetAnimation(AnimationType type, unsigned int direction, unsigned int frame)
{
//	LOGINFO << "SetAnimation type: " << static_cast<int>(type) << " direction: "
//		<< direction << " frame: " << frame;

	// new frame, reset our count
	m_aniCount = 0;

	// Lookup the texture rect for this type, direction, frame
	DirectionIndex dirIndex = MakeDirectionIndexable(direction, m_direction);
	AnimationStrip& animStrip = m_texData->m_animations[type][dirIndex];
	m_currentFrameSetSize = animStrip.size();

	assert(frame < m_currentFrameSetSize);
	UpdateSprite(animStrip[frame]);

	m_type = type;
}

} //namespace Engine