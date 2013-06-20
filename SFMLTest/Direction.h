#pragma once

namespace Engine {

// TODO: Maybe I should just enumerate out UP_LEFT etc so I can use this as a strongly typed
// enum
// Directions can combine
enum Direction
{
	UP		= 0x0001,
	DOWN	= 0x0002,
	LEFT	= 0x0004,
	RIGHT	= 0x0008
};

// You may only have 1 facing
enum class Facing : unsigned int
{
	NORTH = 0,
	SOUTH,
	WEST,
	EAST
};

void DirectionToFacing(unsigned int direction, Facing& facing);
bool IsDiagonalDirection(unsigned int direction);

} // namespace Engine