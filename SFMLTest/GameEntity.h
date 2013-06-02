#pragma once

#include <SFML/Graphics.hpp>

namespace Engine {

//class sf::RenderWindow;
class GameEntity
{
public:
	GameEntity() : m_posx(0), m_posy(0), m_speed(0.0f), diagonalFactor(0.7071f) {}

	virtual bool Update(float interpolation) = 0;
	virtual	bool Render(sf::RenderWindow& window) = 0;

	// Position
	int m_posx;
	int m_posy;

	// Rendering
	// diagonal speed is spd = sqrt(spd_x^2 + spd_y^2)
	// or just 0.7071 * speed
	float m_speed;
	const float diagonalFactor;
};

class TextEntity : public GameEntity
{
public:
	TextEntity(const char * font);

	virtual bool Update(float interpolation) { return true; }
	virtual bool Render(sf::RenderWindow& window) { return true; }

private:
	sf::Font m_font;
	sf::Text m_text;
};

class UnitEntity : public GameEntity
{
public:
	UnitEntity();

	virtual bool Update(float interpolation);
	virtual bool Render(sf::RenderWindow& window);

private:
	bool m_movingUp;
	bool m_movingDown;
	bool m_movingLeft;
	bool m_movingRight;

	sf::Texture m_texture;
	sf::Sprite m_sprite;
};

} // namespace Engine