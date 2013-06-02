#include "GameEntity.h"

#include "Constants.h"

namespace Engine {

UnitEntity::UnitEntity() :
	m_movingUp(false), m_movingDown(false), m_movingLeft(false),
	m_movingRight(false), GameEntity()
{
	// TODO: Asset strings should be looked up somewhere
	m_texture.loadFromFile("resources/Zelda3Sheet1.gif", sf::IntRect(152, 653, 20, 30));

	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	m_sprite.setScale(2.0f, 2.0f);

	m_speed = 0.2f;
}

bool UnitEntity::Update(float interpolation)
{
	m_movingUp = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	m_movingDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	m_movingLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
	m_movingRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

	if (m_movingLeft)
		m_sprite.move(-m_speed * interpolation, 0);
	if (m_movingDown)
		m_sprite.move(0, m_speed * interpolation);
	if (m_movingRight)
		m_sprite.move(m_speed * interpolation, 0);
	if (m_movingUp)
		m_sprite.move(0, -m_speed * interpolation);
	return true;
}

bool UnitEntity::Render(sf::RenderWindow& window)
{
	window.draw(m_sprite);
	return true;
}

TextEntity::TextEntity(const char* font) :
	GameEntity()
{
	m_font.loadFromFile(font);
	m_text = sf::Text("###", m_font, 250);
}

} // namespace Engine