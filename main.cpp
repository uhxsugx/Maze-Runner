// Build: g++ main.cpp player.cpp player2.cpp sounds.cpp menus.cpp -std=c++17 -O2 -o MazeRunner.exe -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
#include<iostream>
#include "player.h"
#include "sounds.h"
#include "menus.h"
#include "player2.h"
#include "enemies.h"
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
	initializeBoss(width, length);
	
	Music music;
	//backgroundMusic(music, 1);
	
	SoundBuffer gun_buffer;
    if(!gun_buffer.loadFromFile("data/sounds/gunshot.mp3"))
	return -1;
    Sound gun_sound(gun_buffer);

	
	
	bool break_flag = false;
	int players = 1;
	int health1 = 100;
	int health2 = 100;
	int player1X;
	int player1Y;
	int player2X;
	int player2Y;
	int bossHealth = 100;
	bool isdead = false;
	bool iswin = false;
	bool ispaused = false;
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
				if(keyPressed->code == Keyboard::Key::J)
				{
					bossHealth = bossDamage(100);
				}
				if(keyPressed-> code == Keyboard::Key::Enter)
					break_flag = true;
				

				if (keyPressed->code == Keyboard::Key::R && (isdead || iswin || ispaused))
				{
    				retry = 1;
				}
				else if(keyPressed->code != Keyboard::Key::R && (isdead || iswin))
				{
					retry = 0;
				}
		
				if(keyPressed -> code == Keyboard::Key::P)
				paused++;
				
			}
		}
		if(health1 <= 0 || health2 <= 0)
		isdead = true;

		if(bossHealth <= 0)
		iswin = true;

		if(paused %2 == 0)
		ispaused = false;

		else 
		ispaused = true;

		if(retry == 1)
		{	
			initializePlayer();
			initializePlayer2();
			initializeBoss(width, length);
			health1 = 100;
			health2 = 100;
			bossHealth = 300;
			retry = 2;
			isdead = false;
			iswin = false;
			ispaused = false;
			paused = 0;
			//if you want to start at main menu then make break_flag = false;
			// this is because the ainmenu nly opens if break_flag = false;
			// if it is true then the game will automatically start
			//break_flag = false;
			continue;
		}
		else if(retry == 0)
		break;

		Gamewin.clear();
		if(!break_flag && isdead == false && iswin == false)
			showMainMenu(Gamewin, players);

		else if(ispaused && break_flag && !isdead && iswin == false)
		{	
			pauseMenu(Gamewin);
		}
		else if (break_flag && isdead == false && iswin == false)
		{
			drawBossBar(Gamewin);
			drawBoss(Gamewin);
			DrawHealthBar(Gamewin);
			drawPlayer(Gamewin);
			if(!ispaused)
			{
				movePlayer(width,length, player1X, player1Y);
				gunSound(gun_sound, players);
				int ishit = moveBoss(Gamewin, player1X, player1Y, player2X, player2Y, players);
				//cout << "|" << player1X << ", " << player1Y << endl;
				if(ishit == 1)
				health1 = takeDamage(10);

				else if (ishit == 2)
				health2 = takeDamagePlayer2(10);

			}

			if(players == 2)
			{
				drawPlayer2(Gamewin);
				DrawHealthBarPlayer2(Gamewin);
				if(!ispaused)
				{
					movePlayer2(width, length, player2X, player2Y);
				}
				
			}

		}

		

		else if(isdead && iswin == false)
		{
			showGameOverScreen(Gamewin);
		}

		

		else if(iswin == true && !isdead)
		{
			winScreen(Gamewin);
		}

		
		

		Gamewin.display();
	}
}