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
	sf::RenderWindow window(sf::VideoMode(Engine::k_windowWidth, Engine::k_windowHeight), "Test");

	// Don't update more than 5 times per loop if falling behind on updating game state
    const int MAXFRAMESKIP = 5;
	
	// Vsync (FPS cap)
	//window.setFramerateLimit(60);
    
	Engine::UnitEntity player;
	sf::Texture bgtexture;
	bgtexture.loadFromFile("resources/lttp_map39.png", sf::IntRect(200, 200, Engine::k_windowWidth, Engine::k_windowHeight));
	sf::Sprite background;
	background.setTexture(bgtexture);
	background.setScale(2.0f, 2.0f);

	// How often we will update the game state
	const int TICKSPERSEC = 25;
	Engine::GameClock clock(TICKSPERSEC);
	clock.Start();

	// Debug text
	Engine::DebugTextEntity debugText(player);
	unsigned int frameCount = 0;
	auto fpsTimer = clock.Now();

	float interpolation;
	bool running = true;
	int loops = 0;

	// order detemrines render order
	std::vector<Engine::GameEntity*> entities;
	entities.push_back(&player);
	entities.push_back(&debugText);

    while (running)
    {
		frameCount++;

		loops = 0;
		while (running && clock.IsReady() && loops++ < MAXFRAMESKIP)
		{
			//LOGDEBUG << "Game Tick " << clock.GetGameTick();

			// event handling
			// updating
			running = HandleWindowEvents(window);
			for (Engine::GameEntity* e : entities)
			{
				e->Update();
			}

			clock.Advance();
		}
		
		interpolation = clock.GetInterpolation();
		//LOGDEBUG << "Interp is: " << interpolation;
		
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
		for (Engine::GameEntity* e : entities)
		{
			e->Render(window, interpolation);
		}
        window.display();
    }

	window.close();

    return 0;
}