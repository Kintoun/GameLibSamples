#include "Textures.h"

#include "Log.h"
#include "Animation.h"

#include "cassert"

namespace Engine {

TextureData* TextureDataFactory::Create(TextureSet set)
{
	switch(set)
	{
	case TextureSet::PLAYER_TEXTURES:
		return new PlayerTexData();
	default:
		return NULL;
	}
}

TextureData::TextureData(const char* spriteSheet) :
	m_spriteSheet(spriteSheet)
{	
}

PlayerTexData::PlayerTexData() : TextureData("resources/Link-LTTP.gif")
{
	// TODO: Handle failure
	texture.loadFromFile(m_spriteSheet);
	//sprite.setTexture(texture);
	//sprite.setScale(4.0f, 4.0f);

	// Idle
	DirectionalStrips idleDirStrip;
	AnimationStrip idleUpStrip;
	AnimationStrip idleDownStrip;
	AnimationStrip idleLeftStrip;
	AnimationStrip idleRightStrip;
	// TODO: Add idle animations for every direction
	idleUpStrip.push_back(sf::IntRect(7, 239, 17, 22));
	idleDownStrip.push_back(sf::IntRect(7, 209, 16, 22));
	idleLeftStrip.push_back(sf::IntRect(225+19, 209, -19, 23));
	idleRightStrip.push_back(sf::IntRect(225, 209, 19, 23));
	idleDirStrip[DirectionIndex::UP_IDX] = idleUpStrip;
	idleDirStrip[DirectionIndex::DOWN_IDX] = idleDownStrip;
	idleDirStrip[DirectionIndex::LEFT_IDX] = idleLeftStrip;
	idleDirStrip[DirectionIndex::RIGHT_IDX] = idleRightStrip;

	// Walking
	DirectionalStrips walkDirStrip;

	// Walking Up
	AnimationStrip upStrip;
	//upStrip.push_back(sf::IntRect(7, 239, 17, 22)); // Idle
	upStrip.push_back(sf::IntRect(78, 239, 17, 22)); // 3
	upStrip.push_back(sf::IntRect(55, 239, 17, 22)); // 2
	upStrip.push_back(sf::IntRect(32, 237, 17, 24)); // 1
	
	
	upStrip.push_back(sf::IntRect(101, 238, 17, 23)); // 4
	upStrip.push_back(sf::IntRect(126, 239, 17, 22)); // 5
	upStrip.push_back(sf::IntRect(148, 237, 17, 24)); // 6
	upStrip.push_back(sf::IntRect(172, 240, 17, 22)); // 7
	walkDirStrip[DirectionIndex::UP_IDX] = upStrip;

	// Walking Down
	AnimationStrip downStrip;
	//downStrip.push_back(sf::IntRect(7, 209, 16, 22)); // Idle
	downStrip.push_back(sf::IntRect(33, 209, 16, 22));
	downStrip.push_back(sf::IntRect(59, 208, 16, 23));
	downStrip.push_back(sf::IntRect(82, 207, 16, 24));
	downStrip.push_back(sf::IntRect(106, 209, 16, 22));
	downStrip.push_back(sf::IntRect(131, 209, 16, 22));
	downStrip.push_back(sf::IntRect(154, 208, 16, 23));
	downStrip.push_back(sf::IntRect(175, 207, 16, 24));
	//downStrip.push_back(sf::IntRect(198, 209, 16, 22)); // repeat of 1st frame
	walkDirStrip[DirectionIndex::DOWN_IDX] = downStrip;

	// Walking Right
	AnimationStrip rightStrip;
	//rightStrip.push_back(sf::IntRect(225, 209, 19, 23)); // Idle
	rightStrip.push_back(sf::IntRect(249, 208, 19, 24));
	rightStrip.push_back(sf::IntRect(277, 208, 18, 24));
	rightStrip.push_back(sf::IntRect(301, 209, 19, 23));
	rightStrip.push_back(sf::IntRect(326, 209, 19, 23));
	rightStrip.push_back(sf::IntRect(351, 208, 19, 24));
	//rightStrip.push_back(sf::IntRect(376, 208, 19, 24)); // Duplicate sprite
	rightStrip.push_back(sf::IntRect(402, 208, 18, 24));
	rightStrip.push_back(sf::IntRect(425, 209, 19, 23));
	walkDirStrip[DirectionIndex::RIGHT_IDX] = rightStrip;

	// Walking Left
	AnimationStrip leftStrip;
	// This is left texture mapped inversely across the Y-axis
	//leftStrip.push_back(sf::IntRect(225+19, 209, -19, 23)); // Idle
	leftStrip.push_back(sf::IntRect(249+19, 208, -19, 24));
	leftStrip.push_back(sf::IntRect(277+19, 208, -18, 24));
	leftStrip.push_back(sf::IntRect(301+19, 209, -19, 23));
	leftStrip.push_back(sf::IntRect(326+19, 209, -19, 23));
	leftStrip.push_back(sf::IntRect(351+19, 208, -19, 24));
	//leftStrip.push_back(sf::IntRect(376+19, 208, -19, 24)); // Duplicate sprite
	leftStrip.push_back(sf::IntRect(402+19, 208, -18, 24));
	leftStrip.push_back(sf::IntRect(425+19, 209, -19, 23));
	walkDirStrip[DirectionIndex::LEFT_IDX] = leftStrip;

	m_animations[AnimationType::IDLE] = idleDirStrip;
	m_animations[AnimationType::WALK] = walkDirStrip;

	/*
	// left is same as right just flipped
	std::for_each(walking.left.begin(), walking.left.end(), [](sf::Sprite& ptr)
	{
		ptr.setScale(-4.0, 4.0);
	});
	*/
}

} // namespace Engine