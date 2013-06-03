#ifndef RENDERENTITY_H
#define RENDERENTITY_H
#include <SFML/Graphics.hpp>
#include "vec.h"

class RenderEntity
{
public:
	RenderEntity();
	RenderEntity(const sf::Texture &texture);
	void Draw(sf::RenderWindow &window, const Vec2f &previousposition, const Vec2f &currentposition, float interpolation);
	sf::Sprite &GetSprite() { return sprite_; }
	Vec2f GetRenderPosition() const { return renderposition_; }
private:
	sf::Sprite sprite_;
	Vec2f renderposition_;
};

#endif