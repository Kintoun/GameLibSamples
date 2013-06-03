#include <SFML/Graphics.hpp>

#include "Time.h"
#include "GameEntity.h"

#include "Constants.h"
#include <sstream>
#include "Log.h"

bool HandleWindowEvents(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				return false;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
					return false;
				break;

			default:
				break;
		}
	}
	return true;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Test");

	// How often we will update the game state
	const int ticksPerSec = 25;
	// Don't update more than 5 times per loop if falling behind on updating game state
    const int maxFrameSkip = 5;
	
	// FPS cap
	//window.setFramerateLimit(60);
    
	Engine::UnitEntity player;
	sf::Texture bgtexture;
	bgtexture.loadFromFile("resources/lttp_map39.png", sf::IntRect(200, 200, WINDOW_WIDTH, WINDOW_HEIGHT));

	sf::Sprite background;
	background.setTexture(bgtexture);
	//background.setPosition(-200, -200);
	background.setScale(2.0f, 2.0f);

	// Debug text
	Engine::DebugTextEntity debugText(player);
	unsigned int frameCount = 0;

	Engine::GameClock clock(ticksPerSec);
	clock.Start();
	auto fpsTimer = clock.Now();
	bool running = true;
	
	float interpolation;
	int loops = 0;
    while (running)
    {
		frameCount++;

		loops = 0;
		while (running && clock.IsReady() && loops++ < maxFrameSkip)
		{
			LOGDEBUG << "Game Tick " << clock.GetGameTick();

			// event handling
			// updating
			running = HandleWindowEvents(window);
			player.Update();
			debugText.Update();

			clock.Advance();
		}
		
		interpolation = clock.GetInterpolation();
		LOGDEBUG << "Interp is: " << interpolation;
		
		auto now = clock.Now();
		auto elapsed = now - fpsTimer;
		if (elapsed > std::chrono::seconds(1))
		{
			debugText.SetFps(frameCount);
			fpsTimer = now;
			frameCount = 0;
		}

        window.clear();
		//window.draw(background);
		player.Render(window, interpolation);
		debugText.Render(window, interpolation);
        window.display();
    }

	window.close();

    return 0;
}