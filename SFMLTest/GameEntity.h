#pragma once

#include "Textures.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

namespace Engine {
class GameEntity
{
public:
	GameEntity() : m_baseSpeed(0.0f), k_diagonalFactor(0.7071f) {}

	// Sets the state of an obj. Includes position, speed, direction, etc.
	// Called once per game tick NOT once per render call.
	virtual bool Update() = 0;

	// Based on the game tick position, determines the interpolated position
	// and renders the obj at that position. Does not alter the actual
	// position of the obj, that is the job of Update()
	virtual	bool Render(sf::RenderWindow& window, float interpolation) = 0;

	const sf::Vector2f& GetPos() const { return m_pos; }

protected:
	// Position
	sf::Vector2f m_pos;
	
	// Previous position for the purpose of interpolation
	sf::Vector2f m_prevPos;
	
	// Our actual velocity (i.e. less if moving diagonal)
	sf::Vector2f m_velocity;
	// Our base speed
	float m_baseSpeed;
	const float k_diagonalFactor;
};

class UnitEntity : public GameEntity
{
public:
	UnitEntity();

	virtual bool Update() override;
	virtual bool Render(sf::RenderWindow& window, float interpolation) override;
	//virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	const sf::Vector2f& GetRenderPos() const { return m_sprite.getPosition(); }

private:
	bool m_movingUp;
	bool m_movingDown;
	bool m_movingLeft;
	bool m_movingRight;

	PlayerTexData texData;
	
	sf::Texture m_texture;

	// The drawable obj. Note that the sprites position is NOT
	// the objs position. The sprite is used for rendering,
	// the position is in the position vector.
	sf::Sprite m_sprite;

	std::vector<sf::Vector2u> m_walkVec;
};

class DebugTextEntity : public GameEntity
{
public:
	DebugTextEntity(const UnitEntity& player);

	virtual bool Update() override;
	virtual bool Render(sf::RenderWindow& window, float interpolation) override;

	void SetFps(unsigned int fps) { m_fps = fps; }

private:
	// Used for position debug text
	const UnitEntity& m_player;

	sf::Font m_font;
	sf::Text m_fpsText;
	sf::Text m_playerPosText;
	sf::Text m_playerRenderPosText;

	unsigned int m_fps;
};

} // namespace Engine