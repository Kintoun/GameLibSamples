#include "GameEntity.h"

#include "Constants.h"
#include "InputHandler.h"
#include "Events.h"

#include "Log.h"

namespace Engine {

UnitEntity::UnitEntity() :
	GameEntity(), m_animation(TextureSet::PLAYER_TEXTURES, 2), m_moveDirection(0)
{
	m_pos = sf::Vector2f(k_windowWidth / 2, k_windowHeight / 2);
	m_prevPos = m_pos;
	 
	m_baseSpeed = 11.0f;
}

bool UnitEntity::Update()
{
	Event event = Keyboard::KeyboardToEvent();
	if (event & EventType::ATTACKING)
	{
	}
	m_moveDirection = Keyboard::KeyboardToDirection();

	// reset to base speed
	float speed = m_baseSpeed;
	m_velocity = sf::Vector2f();

	// moving diagonally
	if (IsDiagonalDirection(m_moveDirection))
	{
		speed *= k_diagonalFactor;
	}

	// TODO: I'm sure there is a better mathy way to do this...
	if (m_moveDirection & Direction::LEFT)
	{
		m_velocity += sf::Vector2f(-speed, 0);
	}
	if (m_moveDirection & Direction::DOWN)
	{
		m_velocity += sf::Vector2f(0, speed);
	}
	if (m_moveDirection & Direction::RIGHT)
	{
		m_velocity += sf::Vector2f(speed, 0);
	}
	if (m_moveDirection & Direction::UP)
	{
		m_velocity += sf::Vector2f(0, -speed);
	}

	m_prevPos = m_pos;
	m_pos += m_velocity;
	//LOGDEBUG << "Position X: " << m_pos.x << " Y: " << m_pos.y;

	// It's OK for us not to get a new direction.
	DirectionToFacing(m_moveDirection, m_facing);

	// Pass entity state to animation system so it knows what to animate
	m_animation.Update(m_facing, event);

	return true;
}

bool UnitEntity::Render(sf::RenderWindow& window, float interpolation)
{
	// differnece between last pos and cur, times interp, plus prev pos
	sf::Vector2f renderPos = m_prevPos + ((m_pos - m_prevPos) * interpolation);
	m_animation.Render(window, renderPos);
	//LOGDEBUG << "Prediction X: " << renderPos.x << " Y: " << renderPos.y;
	
	return true;
}

const sf::Vector2f& UnitEntity::GetRenderPos() const
{
	return m_animation.GetSprite().getPosition();
}

DebugTextEntity::DebugTextEntity(const UnitEntity& player) :
	m_player(player), m_fps(0), GameEntity()
{
	m_font.loadFromFile("resources/fonts/arial.ttf");
	m_fpsText = sf::Text("", m_font, 20);
	m_playerPosText = sf::Text("", m_font, 20);
	m_playerRenderPosText = sf::Text("", m_font, 20);
	
	m_fpsText.setFillColor(sf::Color::Green);
	m_fpsText.setStyle(sf::Text::Bold);

	m_playerPosText.setFillColor(sf::Color::Green);
	m_playerPosText.setStyle(sf::Text::Bold);
	m_playerPosText.setPosition(0, 30);

	m_playerRenderPosText.setFillColor(sf::Color::Green);
	m_playerRenderPosText.setStyle(sf::Text::Bold);
	m_playerRenderPosText.setPosition(0, 60);
}

bool DebugTextEntity::Update()
{
	if (m_fps > 0)
	{
		std::stringstream ss;
		ss << m_fps;
		m_fpsText.setString(ss.str());
	}

	const auto& playerPos = m_player.GetPos();
	std::stringstream playerPosStr;
	playerPosStr << "Pos X: " << playerPos.x << " Y: " << playerPos.y;
	m_playerPosText.setString(playerPosStr.str());

	// Render Pos of course is updated every render frame

	return true;
}

bool DebugTextEntity::Render(sf::RenderWindow& window, float /*interpolation*/)
{
	// Render Pos of course is updated every render frame
	const auto& playerRenderPos = m_player.GetRenderPos();
	std::stringstream playerRenderPosStr;
	playerRenderPosStr << "Render Pos X: " << playerRenderPos.x << " Y: " << playerRenderPos.y;
	m_playerRenderPosText.setString(playerRenderPosStr.str());

	window.draw(m_fpsText);
	window.draw(m_playerPosText);
	window.draw(m_playerRenderPosText);

	return true;
}

} // namespace Engine