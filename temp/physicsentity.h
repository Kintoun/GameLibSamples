#ifndef PHYSICSENTITY_H
#define PHYSICSENTITY_H
#include "vec.h"

class PhysicsEntity
{
public:
	PhysicsEntity();
	Vec2f GetPreviousPosition() const { return previousposition_; }
	Vec2f GetPosition() const { return currentposition_; }
	Vec2f GetNextPosition(float dt) const;
	Vec2f GetPreviousVelocity() const { return previousvelocity_; }
	Vec2f GetVelocity() const { return currentvelocity_; }
	Vec2f GetAcceleration() const { return acceleration_; }
	void SetVelocity(float vel_x, float vel_y);
	void SetPosition(float pos_x, float pos_y);
	void SetAcceleration(float acc_x, float acc_y);
	void SetMaxSpeed(float speed_x, float speed_y);
	void Integrate(float dt);
private:
	Vec2f previousposition_;
	Vec2f currentposition_;
	Vec2f previousvelocity_;
	Vec2f currentvelocity_;
	Vec2f acceleration_;
	Vec2f maxspeed_;
};

#endif