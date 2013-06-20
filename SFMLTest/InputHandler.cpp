#include "InputHandler.h"

#include "Direction.h"
#include "Events.h"

#include <SFML/Window/Keyboard.hpp>

namespace Keyboard {

unsigned int KeyboardToDirection()
{
	unsigned int direction = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		direction |= Engine::Direction::UP;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		direction |= Engine::Direction::DOWN;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		direction |= Engine::Direction::LEFT;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		direction |= Engine::Direction::RIGHT;
	return direction;
}

unsigned int KeyboardToEvent()
{
	unsigned int event = Engine::EventType::NO_EVENT;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		event |= Engine::EventType::ATTACKING;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		event |= Engine::EventType::MOVING;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		event |= Engine::EventType::MOVING;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		event |= Engine::EventType::MOVING;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		event |= Engine::EventType::MOVING;

	return event;
}

} // namespace Keyboard