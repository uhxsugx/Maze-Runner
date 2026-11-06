#include<iostream>
#include "player.h"
#include<SFML/Graphics.hpp>
using namespace std;
using namespace sf;
int main()
{
	RenderWindow Gamewin(VideoMode::getDesktopMode(), "Pyramid Themed Maze Runner", Style::Default);
	int width = Gamewin.getSize().x;
	int length = Gamewin.getSize().y;
	initializePlayer();
	bool gamefinish = false;
	while (Gamewin.isOpen())
	{
		while (optional<Event> event = Gamewin.pollEvent())
		{
			if (event->is<Event::Closed>())
			{
				Gamewin.close();
			}
			if ((event->getIf<Event::KeyPressed>()) && (event->getIf<Event::KeyPressed>()->code == Keyboard::Key::Escape))
			{
				Gamewin.close();
			}
		}
		if (GameOver())
		{
			gamefinish = true;
		}

		if (!gamefinish)
		{
			movePlayer(width, length);
		}
		Gamewin.clear();
		DrawHealthBar(Gamewin);
		drawPlayer(Gamewin);
		if (gamefinish)
		{

		}
		Gamewin.display();
	
	
	
	
	
	}

	return 0;

}