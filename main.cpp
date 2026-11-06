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
			Gamewin.clear();
			DrawHealthBar(Gamewin);
			movePlayer(width,length);
			drawPlayer(Gamewin);
			Gamewin.display();
		
		}
	}

}