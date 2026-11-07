// Build: g++ main.cpp player.cpp player2.cpp sounds.cpp menus.cpp -std=c++17 -O2 -o MazeRunner.exe -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
#include<iostream>
#include "player.h"
#include "sounds.h"
#include "menus.h"
#include "player2.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;
int main()
{
	VideoMode res = VideoMode::getDesktopMode();
    RenderWindow Gamewin(res, "The Maze Runner", State:: Fullscreen);
	int width = Gamewin.getSize().x;
	int length = Gamewin.getSize().y;
	initializePlayer();
	initializePlayer2();
	
	Music music;
	backgroundMusic(music, 5);
	
	bool break_flag = false;
	int players = 1;
	int health1 = 100;
	int health2 = 100;
	bool isdead = false;
	int retry = 2;
	int paused = 0;
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
					health1 = takeDamage(10);
				}

				if(keyPressed->code == Keyboard::Key::I)
				{
					health2 = takeDamagePlayer2(20);
				}
				if(keyPressed-> code == Keyboard::Key::Enter)
					break_flag = true;
				

				if(!(keyPressed ->code == Keyboard::Key::R) && isdead)
				{
					retry = 0;
				}
				if((keyPressed ->code == Keyboard::Key::R) && isdead)
				{
					retry = 1;
				}
				if(keyPressed -> code == Keyboard::Key::P)
				paused++;
				if((keyPressed ->code == Keyboard::Key::R) && isdead)
				{
					retry = 1;
				}
			}
		}
		if(health1 <= 0 || health2 <= 0)
		isdead = true;

		Gamewin.clear();
		if(!break_flag && isdead == false)
			showMainMenu(Gamewin, width, length, players);

		else if (break_flag && isdead == false)
		{
			DrawHealthBar(Gamewin);
			if(paused%2 == 0)
			movePlayer(width,length);
			drawPlayer(Gamewin);

			if(players == 2)
			{
				drawPlayer2(Gamewin);
				if(paused%2 == 0)
				movePlayer2(width, length);
				DrawHealthBarPlayer2(Gamewin);
			}

		}

		
		else if(isdead)
		{
			showGameOverScreen(Gamewin, width, length);
			if(retry == 0)
				break;
			else if(retry == 1)
			{	
				initializePlayer();
				initializePlayer2();
				health1 = 100;
				health2 = 100;
				retry = 2;
				isdead = false;
				//if you want to start at main menu then make break_flag = false;
				// this is because the ainmenu nly opens if break_flag = false;
				// if it is true then the game will automatically start
				//break_flag = false;
				continue;
			}
		}

		if(paused%2 != 0 && break_flag && !isdead)
		{	
			pauseMenu(Gamewin, width, length);
		}
		
		

		Gamewin.display();
	}
}