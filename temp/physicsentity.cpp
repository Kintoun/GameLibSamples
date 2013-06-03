#include "physicsentity.h"

PhysicsEntity::PhysicsEntity() : 
previousposition_(), currentposition_(), previousvelocity_(), currentvelocity_(), acceleration_(), maxspeed_()
{
}

void PhysicsEntity::SetPosition(float pos_x, float pos_y)
{
	previousposition_ = Vec2f(pos_x, pos_y);
	currentposition_ = Vec2f(pos_x, pos_y);
}

void PhysicsEntity::SetVelocity(float vel_x, float vel_y)
{
	currentvelocity_ = Vec2f(vel_x, vel_y);
	previousvelocity_ = Vec2f(vel_x, vel_y);
}

void PhysicsEntity::SetAcceleration(float acc_x, float acc_y)
{
	acceleration_ = Vec2f(acc_x, acc_y);
}

void PhysicsEntity::SetMaxSpeed(float speed_x, float speed_y)
{
	maxspeed_ = Vec2f(speed_x, speed_y);
}

Vec2f PhysicsEntity::GetNextPosition(float dt) const
{
	return Vec2f(
		currentposition_.x + ((previousvelocity_.x + currentvelocity_.x) * 0.5f * dt),
		currentposition_.y + ((previousvelocity_.y + currentvelocity_.y) * 0.5f * dt));
}

void PhysicsEntity::Integrate(float dt)
{
	previousvelocity_ = currentvelocity_;

	if(acceleration_.x > 0)
	{
		if(currentvelocity_.x < maxspeed_.x)
			currentvelocity_.x += acceleration_.x * dt;
	}
	else if(acceleration_.x < 0)
	{
		if(currentvelocity_.x > -maxspeed_.x)
			currentvelocity_.x += acceleration_.x * dt;
	}

	if(acceleration_.y > 0)
	{
		if(currentvelocity_.y < maxspeed_.y)
			currentvelocity_.y += acceleration_.y * dt;
	}
	else if(acceleration_.y < 0)
	{
		if(currentvelocity_.y > -maxspeed_.y)
			currentvelocity_.y += acceleration_.y * dt;
	}

	previousposition_ = currentposition_;
	currentposition_.x += (previousvelocity_.x + currentvelocity_.x) * 0.5f * dt;
	currentposition_.y += (previousvelocity_.y + currentvelocity_.y) * 0.5f * dt;
}