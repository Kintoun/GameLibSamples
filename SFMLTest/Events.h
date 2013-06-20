#pragma once

namespace Engine {

typedef unsigned int Event;

enum EventType
{
	NO_EVENT = 0,

	MOVING = 0x0001,
	ATTACKING = 0x0002
};

} // namespace Engine