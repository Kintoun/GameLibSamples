#include "GameEntity.h"

#include "Constants.h"

#include "Log.h"

namespace Engine {

UnitEntity::UnitEntity() :
	m_movingUp(false), m_movingDown(false), m_movingLeft(false),
	m_movingRight(false), GameEntity()
{
	// TODO: Asset strings should be looked up somewhere
	m_texture.loadFromFile("resources/Zelda3Sheet1.gif", sf::IntRect(152, 653, 20, 30));

	m_sprite.setTexture(m_texture);
	m_pos = sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	m_prevPos = m_pos;
	m_sprite.setPosition(m_pos);
	m_sprite.setScale(2.0f, 2.0f);
	 
	m_baseSpeed = 10.0f;
}

bool UnitEntity::Update()
{
	m_movingUp = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	m_movingDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	m_movingLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
	m_movingRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

	// reset to base speed
	float speed = m_baseSpeed;
	m_velocity = sf::Vector2f();

	if (m_movingUp && (m_movingLeft || m_movingRight)
		|| m_movingDown && (m_movingLeft || m_movingRight))
	{
		speed *= k_diagonalFactor;
	}

	// TODO: I'm sure there is a better mathy way to do this...
	if (m_movingLeft)
		m_velocity += sf::Vector2f(-speed, 0);
	if (m_movingDown)
		m_velocity += sf::Vector2f(0, speed);
	if (m_movingRight)
		m_velocity += sf::Vector2f(speed, 0);
	if (m_movingUp)
		m_velocity += sf::Vector2f(0, -speed);

	m_prevPos = m_pos;
	m_pos += m_velocity;
	//LOGDEBUG << "Position X: " << m_pos.x << " Y: " << m_pos.y;

	return true;
}

bool UnitEntity::Render(sf::RenderWindow& window, float interpolation)
{
	// differnece between last pos and cur, times interp, plus prev pos
	sf::Vector2f renderPos = m_prevPos + ((m_pos - m_prevPos) * interpolation);
	m_sprite.setPosition(renderPos);
	//LOGDEBUG << "Prediction X: " << renderPos.x << " Y: " << renderPos.y;

	window.draw(m_sprite);
	return true;
}

DebugTextEntity::DebugTextEntity(const UnitEntity& player) :
	m_player(player), m_fps(0), GameEntity()
{
	m_font.loadFromFile("resources/fonts/arial.ttf");
	m_fpsText = sf::Text("", m_font, 20);
	m_playerPosText = sf::Text("", m_font, 20);
	m_playerRenderPosText = sf::Text("", m_font, 20);
	
	m_fpsText.setColor(sf::Color::Green);
	m_fpsText.setStyle(sf::Text::Bold);

	m_playerPosText.setColor(sf::Color::Green);
	m_playerPosText.setStyle(sf::Text::Bold);
	m_playerPosText.setPosition(0, 30);

	m_playerRenderPosText.setColor(sf::Color::Green);
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