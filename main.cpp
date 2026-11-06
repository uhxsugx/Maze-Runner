// Build: g++ main.cpp player.cpp sounds.cpp -std=c++17 -O2 -o MazeRunner.exe -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
#include<iostream>
#include "player.h"
#include "sounds.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

int main()
{
	VideoMode res = VideoMode::getDesktopMode();
    RenderWindow Gamewin(res, "Maze Runner", State:: Fullscreen);
	int width = Gamewin.getSize().x;
	int length = Gamewin.getSize().y;
	initializePlayer();
	Music music;
	backgroundMusic(music, 1);
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
			if (const auto* keyPressed = event->getIf<Event::KeyPressed>())
			{
				if (keyPressed->code == Keyboard::Key::H)
				{
					takeDamage(10);
				}
			}
			Gamewin.clear();
			DrawHealthBar(Gamewin);
			movePlayer(width,length);
			drawPlayer(Gamewin);
			Gamewin.display();
		
		}
	}

}