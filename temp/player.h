#ifndef PLAYER_H
#define PLAYER_H
#include "physicsentity.h"
#include "renderentity.h"

class Player
{
public:
	Player(const sf::Texture &texture, float pos_x, float pos_y, float speed_x, float speed_y);
	void Update(float dt);
	void Draw(sf::RenderWindow& window, float interpolation);
	Vec2f GetPosition() const { return physicsstate_.GetPosition(); }
	Vec2f GetRenderPosition() const { return renderstate_.GetRenderPosition(); }
	//PhysicsEntity &GetPhysicsState() const { return &physicsstate_; } // probably can't be const
	//RenderEntity &GetRenderState() const { return &renderstate_; }
private:
	PhysicsEntity physicsstate_;
	RenderEntity renderstate_;
};

#endif