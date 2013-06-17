#include "Textures.h"

#include "Log.h"

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

void TextureData::SetIdle(unsigned int /*direction*/, unsigned int frame, unsigned int& size)
{
	assert(frame < idle.size());
	texture.loadFromFile(GetSheet(), idle[frame]);
	size = idle.size();
}

void TextureData::SetWalking(unsigned int direction, unsigned int frame, unsigned int& size)
{
	if (direction & Direction::DOWN)
	{
		assert(frame < walking.down.size());
		texture.loadFromFile(GetSheet(), walking.down[frame]);
		size = walking.down.size();
	}
	else
	{
		LOGERROR << "Unsupported direction: " << direction;
		size = 0;
	}
}

PlayerTexData::PlayerTexData() : TextureData("resources/Link-LTTP.gif")
{
	idle.push_back(sf::IntRect(90, 13, 16, 22));
		
	walking.down.push_back(sf::IntRect(122, 13, 16, 22));
	walking.down.push_back(sf::IntRect(149, 12, 16, 23));
	walking.down.push_back(sf::IntRect(174, 11, 16, 24));
	walking.down.push_back(sf::IntRect(197, 13, 16, 22));
	walking.down.push_back(sf::IntRect(223, 12, 16, 23));
	walking.down.push_back(sf::IntRect(249, 11, 16, 24));
	walking.down.push_back(sf::IntRect(272, 13, 16, 22));
	walking.down.push_back(sf::IntRect(298, 13, 16, 22));
	
	texture.loadFromFile(GetSheet(), idle[0]);
	sprite.setTexture(texture);
	sprite.setScale(4.0f, 4.0f);
}

} // namespace Engine