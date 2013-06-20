#include "Direction.h"

namespace Engine {

void DirectionToFacing(unsigned int direction, Facing& facing)
{
	if (direction & Direction::UP)
		facing = Facing::NORTH;
	if (direction & Direction::DOWN)
		facing = Facing::SOUTH;
	if (direction & Direction::LEFT)
		facing = Facing::WEST;
	if (direction & Direction::RIGHT)
		facing = Facing::EAST;
}

bool IsDiagonalDirection(unsigned int direction)
{
	return (direction & Direction::LEFT || direction & Direction::RIGHT)
		&& (direction & Direction::DOWN || direction & Direction::UP);
}

} // namespace Engine