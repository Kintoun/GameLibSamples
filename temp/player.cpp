#include "player.h"

Player::Player(const sf::Texture &texture, float pos_x, float pos_y, float speed_x, float speed_y)
{
	physicsstate_ = PhysicsEntity();
	physicsstate_.SetMaxSpeed(speed_x, speed_y);
	physicsstate_.SetPosition(pos_x, pos_y);
	renderstate_ = RenderEntity(texture);
}

void Player::Update(float dt)
{
	// Handle input
	Vec2f force = Vec2f(0, 500.f);
	if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Left))
	{
		force.x = -500.f;
	}
	else if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Right))
	{
		force.x = 500.f;
	}

	if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Up))
	{
		force.y = -5000.f;
	}
	else if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Down))
	{
		force.y = 500.f;
	}

	if(physicsstate_.GetNextPosition(dt).x < 0.0f || physicsstate_.GetPosition().x > 480.0f)
	{
		physicsstate_.SetPosition(0, physicsstate_.GetPosition().y);
		physicsstate_.SetVelocity(60.0f, 0.f);
		//physicsstate_.SetVelocity(physicsstate_.GetVelocity().x * physicsstate_.GetBounce() * -1.f, physicsstate_.GetVelocity().y * (1.f - physicsstate_.GetFriction()));
		/*force.x = 0;
		physicsstate_.SetPosition(0, physicsstate_.GetPosition().y);
		physicsstate_.SetVelocity(0, physicsstate_.GetVelocity().y);
		physicsstate_.SetAcceleration(0, physicsstate_.GetAcceleration().y);*/
		//force.x = physicsstate_->GetAcceleration().x * -1.f;
		//physicsstate_->SetVelocity(physicsstate_->GetVelocity().x * -0.5f, physicsstate_->GetVelocity().y);
	}
	if(physicsstate_.GetPosition().y + 10.f > 272.f)
	{
		physicsstate_.SetPosition(physicsstate_.GetPosition().x, 262.f);
		physicsstate_.SetVelocity(physicsstate_.GetVelocity().x, physicsstate_.GetVelocity().y * 0.3f * -1.f);
	}

	physicsstate_.SetAcceleration(force.x, force.y);
	physicsstate_.Integrate(dt);
}

void Player::Draw(sf::RenderWindow& window, float interpolation)
{
	renderstate_.Draw(window, physicsstate_.GetPreviousPosition(), physicsstate_.GetPosition(), interpolation);
}