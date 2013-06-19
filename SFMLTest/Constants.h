#pragma once

// TODO: Get rid of this file, it is dumb
namespace Engine {

enum Direction
{
	UP		= 0x0001,
	DOWN	= 0x0002,
	LEFT	= 0x0004,
	RIGHT	= 0x0008
};

enum DirectionIndex
{
	NONE = -1,

	UP_IDX = 0,
	DOWN_IDX,
	LEFT_IDX,
	RIGHT_IDX,

	NUM_IDX
};

extern const unsigned int k_windowWidth;
extern const unsigned int k_windowHeight;

} //namespace Engine