#include "renderentity.h"

RenderEntity::RenderEntity() : sprite_(), renderposition_()
{
}

RenderEntity::RenderEntity(const sf::Texture &texture)
{
	sprite_ = sf::Sprite(texture);
}

void RenderEntity::Draw(sf::RenderWindow &window, const Vec2f &previousposition, const Vec2f &currentposition, float interpolation)
{
	renderposition_ = Vec2f(
		previousposition.x + ((currentposition.x - previousposition.x) * interpolation),
		previousposition.y + ((currentposition.y - previousposition.y) * interpolation));
	sprite_.SetPosition(renderposition_.x, renderposition_.y);
	window.Draw(sprite_);
}