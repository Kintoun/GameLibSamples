#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Test");
	//window.setFramerateLimit(60);

	const int ticksPerSec = 25;
	const int skipTicks = 1000 / ticksPerSec;
	// don't update more than 5 times per loop if falling behind on updating game state
    const int maxFrameSkip = 5;
    
	sf::Texture texture;
	texture.loadFromFile("resources/Zelda3Sheet1.gif", sf::IntRect(152, 653, 20, 30));
	sf::Texture bgtexture;
	bgtexture.loadFromFile("resources/lttp_map39.png", sf::IntRect(200, 200, WINDOW_WIDTH, WINDOW_HEIGHT));

	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	sprite.setScale(2.0f, 2.0f);

	sf::Sprite background;
	background.setTexture(bgtexture);
	//background.setPosition(-200, -200);
	background.setScale(2.0f, 2.0f);

	sf::Clock clock;
	bool running = true;
	unsigned int nextGameTick = clock.getElapsedTime().asMilliseconds();
	
	int loops = 0;
    while (running)
    {
		loops = 0;
		while (running && clock.getElapsedTime().asMilliseconds() > nextGameTick && loops++ < maxFrameSkip)
		{
			// event handling
			// updating
			sf::Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
					case sf::Event::Closed:
						running = false;
						break;

					case sf::Event::KeyPressed:
						if (event.key.code == sf::Keyboard::Escape)
						{
							running = false;
						}
						break;

					default:
						break;
				}
			}

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				sprite.move(-10,0);
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				sprite.move(0,10);
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				sprite.move(10,0);
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				sprite.move(0,-10);

			nextGameTick += skipTicks;
		}

        window.clear();
		window.draw(background);
        window.draw(sprite);
        window.display();
    }

	window.close();

    return 0;
}