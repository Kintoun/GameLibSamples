#include <sstream>
#include <SFML/Graphics.hpp>
#include "player.h"

void PollEvents(sf::RenderWindow &window)
{
	sf::Event Event;
	while(window.PollEvent(Event))
	{
		if(Event.Type == sf::Event::Closed)
			window.Close();
	}
}

void Update(float dt, Player &player)
{
	player.Update(dt);
}

void Draw(sf::RenderWindow &window, float interpolation, Player &player)
{
	window.Clear(sf::Color(42, 42, 42));

	player.Draw(window, interpolation);

	window.Display();
}

int main()
{
	sf::RenderWindow Window = sf::RenderWindow(sf::VideoMode(480, 272, 32), "Rendering", sf::Style::Close | sf::Style::Titlebar);

	sf::Texture playertexture;
	if(!playertexture.LoadFromFile("dude.png"))
		return EXIT_FAILURE;

	Player player = Player(playertexture, 240.f, 136.f, 10000.f, 10000.f);

	const sf::Uint32 TIMESTEP = 40;
	const sf::Uint32 MAX_FRAMESKIP = 5;
	sf::Clock clock;
	sf::Uint32 nexttick = clock.GetElapsedTime(); // nextupdate
	sf::Uint32 framecount = 0;

	while(Window.IsOpened())
	{
		int frameskips = 0;
		while(clock.GetElapsedTime() > nexttick && frameskips < MAX_FRAMESKIP)
		{
			PollEvents(Window);
			Update(float(TIMESTEP) / 1000.f, player);

			++frameskips;
			nexttick += TIMESTEP;
		}

		const float interpolation = float(clock.GetElapsedTime() + TIMESTEP - nexttick) / float(TIMESTEP);

		sf::Uint32 starttime = clock.GetElapsedTime();

		Draw(Window, interpolation, player);

		sf::Uint32 frametime = clock.GetElapsedTime() - starttime;

		// Cap the framerate at 125 fps
		if(frametime < 8)
		{
			sf::Sleep(8 - frametime);
		}

		float framerate = 1000.f / float(clock.GetElapsedTime() - starttime);

		std::stringstream ss;
		ss<<"Rendering ("<<(1000.f / float(clock.GetElapsedTime() - starttime))<<" fps)";
		Window.SetTitle(ss.str());

		// Reset the clock once in a while, as sf::Uint32 overflows after 49,7 days or something
		if(clock.GetElapsedTime() > 2000)
		{
			clock.Reset();
			nexttick = clock.GetElapsedTime();
			framecount = 0;
		}
	}

	return EXIT_SUCCESS;
}