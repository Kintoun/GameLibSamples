#pragma once

#include <SFML/Graphics.hpp>

namespace Engine {

// TODO: Oh god this screams for auto code generation
struct PlayerTexData
{
	PlayerTexData() : aniFrame(0), aniDuration(2), aniDurCur(9999)
	{
		idleFrames = 1;
		idleRects[0] = sf::IntRect(90,13, 16, 22);
		
		walkDownFrames = 8;
		walkDownRects[0] = sf::IntRect(122,13, 16, 22);
		walkDownRects[1] = sf::IntRect(149,12, 16, 23);
		walkDownRects[2] = sf::IntRect(174,11, 16, 24);
		walkDownRects[3] = sf::IntRect(197,13, 16, 22);
		walkDownRects[4] = sf::IntRect(223,12, 16, 23);
		walkDownRects[5] = sf::IntRect(249,11, 16, 24);
		walkDownRects[6] = sf::IntRect(272,13, 16, 22);
		walkDownRects[7] = sf::IntRect(298,13, 16, 22);
	}

	const char* GetSheet() { return "resources/Link-LTTP.gif"; }

	unsigned int idleFrames;
	sf::IntRect idleRects[1];
	
	unsigned int walkDownFrames;
	sf::IntRect walkDownRects[8];

	unsigned int aniFrame;
	unsigned int aniDurCur;
	const unsigned int aniDuration;
};

} //namespace Engine