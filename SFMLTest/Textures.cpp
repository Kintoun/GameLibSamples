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

	UpdateSprite(idle[frame]);
	size = idle.size();
}

void TextureData::SetWalking(unsigned int direction, unsigned int frame, unsigned int& size)
{
	const std::vector<sf::IntRect>& animStrip = GetWalkDirectionStrip(direction);
	size = animStrip.size();
	assert(frame < size);

	UpdateSprite(animStrip[frame]);
}

void TextureData::UpdateSprite(const sf::IntRect& rect)
{
	sprite.setTextureRect(rect);
	sprite.setOrigin(std::abs(rect.width)/2, std::abs(rect.height));
}

const std::vector<sf::IntRect>& TextureData::GetWalkDirectionStrip(unsigned int direction)
{
	assert(direction != 0);
	if (direction & Direction::UP)
	{
		return walking.up;
	}
	else if (direction & Direction::DOWN)
	{
		return walking.down;
	}
	else if (direction & Direction::LEFT)
	{
		return walking.left;
	}
	else if (direction & Direction::RIGHT)
	{
		return walking.right;
	}
	else
	{
		return idle;
		LOGERROR << "Unsupported direction: " << direction;
	}
}

/*
void SpriteStrip::Insert(const sf::IntRect& rect)
{
	sf::Sprite sprite(texture, rect);
	sprite.setOrigin(rect.width/2, rect.height/2);
	sprites.push_back(sprite);
}
*/

PlayerTexData::PlayerTexData() : TextureData("resources/Link-LTTP.gif")
{
	// TODO: Handle failure
	texture.loadFromFile(GetSheet());
	sprite.setTexture(texture);
	sprite.setScale(4.0f, 4.0f);

	idle.push_back(sf::IntRect(7, 209, 16, 22));
	
	walking.up.push_back(sf::IntRect(7, 239, 17, 22));
	walking.up.push_back(sf::IntRect(32, 237, 17, 24));
	walking.up.push_back(sf::IntRect(55, 239, 17, 22));
	walking.up.push_back(sf::IntRect(78, 239, 17, 22));
	walking.up.push_back(sf::IntRect(101, 238, 17, 23));
	walking.up.push_back(sf::IntRect(126, 239, 17, 22));
	walking.up.push_back(sf::IntRect(148, 237, 17, 24));
	walking.up.push_back(sf::IntRect(172, 240, 17, 22));

	walking.down.push_back(sf::IntRect(7, 209, 16, 22));
	walking.down.push_back(sf::IntRect(33, 209, 16, 22));
	walking.down.push_back(sf::IntRect(59, 208, 16, 23));
	walking.down.push_back(sf::IntRect(82, 207, 16, 24));
	walking.down.push_back(sf::IntRect(106, 209, 16, 22));
	walking.down.push_back(sf::IntRect(131, 209, 16, 22));
	walking.down.push_back(sf::IntRect(154, 208, 16, 23));
	walking.down.push_back(sf::IntRect(175, 207, 16, 24));
	walking.down.push_back(sf::IntRect(198, 209, 16, 22));

	walking.right.push_back(sf::IntRect(225, 209, 19, 23));
	walking.right.push_back(sf::IntRect(249, 208, 19, 24));
	walking.right.push_back(sf::IntRect(277, 208, 18, 24));
	walking.right.push_back(sf::IntRect(301, 209, 19, 23));
	walking.right.push_back(sf::IntRect(326, 209, 19, 23));
	walking.right.push_back(sf::IntRect(351, 208, 19, 24));
	walking.right.push_back(sf::IntRect(376, 208, 19, 24));
	walking.right.push_back(sf::IntRect(402, 208, 18, 24));
	walking.right.push_back(sf::IntRect(425, 209, 19, 23));

	walking.left.push_back(sf::IntRect(225+19, 209, -19, 23));
	walking.left.push_back(sf::IntRect(249+19, 208, -19, 24));
	walking.left.push_back(sf::IntRect(277+19, 208, -18, 24));
	walking.left.push_back(sf::IntRect(301+19, 209, -19, 23));
	walking.left.push_back(sf::IntRect(326+19, 209, -19, 23));
	walking.left.push_back(sf::IntRect(351+19, 208, -19, 24));
	walking.left.push_back(sf::IntRect(376+19, 208, -19, 24));
	walking.left.push_back(sf::IntRect(402+19, 208, -18, 24));
	walking.left.push_back(sf::IntRect(425+19, 209, -19, 23));

	/*
	// left is same as right just flipped
	std::for_each(walking.left.begin(), walking.left.end(), [](sf::Sprite& ptr)
	{
		ptr.setScale(-4.0, 4.0);
	});
	*/

	UpdateSprite(idle[0]);
}

} // namespace Engine