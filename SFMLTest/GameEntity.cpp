#include "GameEntity.h"

#include "Constants.h"

namespace Engine {

PlayerEntity::PlayerEntity() : GameEntity()
{
	// TODO: Asset strings should be looked up somewhere
	m_texture.loadFromFile("resources/Zelda3Sheet1.gif", sf::IntRect(152, 653, 20, 30));

	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	m_sprite.setScale(2.0f, 2.0f);
}

bool PlayerEntity::Update()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		m_sprite.move(-10,0);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		m_sprite.move(0,10);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		m_sprite.move(10,0);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		m_sprite.move(0,-10);
	return true;
}

bool PlayerEntity::Render(sf::RenderWindow& window)
{
	window.draw(m_sprite);
	return true;
}

} // namespace Engine