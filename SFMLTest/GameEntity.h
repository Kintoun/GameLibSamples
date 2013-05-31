#pragma once

#include <SFML/Graphics.hpp>

namespace Engine {

//class sf::RenderWindow;
class GameEntity
{
public:
	GameEntity() : x(0), y(0) {}

	virtual bool Update() = 0;
	virtual	bool Render(sf::RenderWindow& window) = 0;

	// Position
	int x;
	int y;
};

class PlayerEntity : public GameEntity
{
public:
	PlayerEntity();

	virtual bool Update();
	virtual bool Render(sf::RenderWindow& window);

private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};

} // namespace Engine