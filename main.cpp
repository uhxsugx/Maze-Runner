// Build: g++ main.cpp player.cpp player2.cpp enemies.cpp map.cpp sounds.cpp menus.cpp -std=c++17 -O2 -o MazeRunner.exe -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
#include<iostream>
#include "player.h"
#include "sounds.h"
#include "menus.h"
#include "player2.h"
#include "enemies.h"
#include "map.h"
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
	initializeEnemies(width, length);
	initializeGun(2.0);
	
	Music music;
	backgroundMusic(music, 4);
	
	SoundBuffer gun_buffer;
    if(!gun_buffer.loadFromFile("data/sounds/gunshot.mp3"))
	return -1;
    Sound gun_sound(gun_buffer);

	
	
	bool break_flag = false;
	int players = 1;
	int health1 = 100;
	int health2 = 100;
	int player1X = 100;
	int player1Y = 100;
	int player2X = 250;
	int player2Y = 100;
	int bossHealth = 750;
	bool isdead = false;
	bool iswin = false;
	bool ispaused = false;
	bool qHeld = false;
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
				if(keyPressed->code == Keyboard::Key::Q)
				{
					if(!qHeld && break_flag && !ispaused && !isdead && !iswin)
						shootGun(player1X, player1Y);
					qHeld = true;
				}
				if(keyPressed-> code == Keyboard::Key::Enter)
					break_flag = true;
				

				if (keyPressed->code == Keyboard::Key::R && (isdead || iswin || ispaused))
				{
    				retry = 1;
				}
				else if(keyPressed->code == Keyboard::Key::Enter && (isdead || iswin))
				{
					retry = 0;
				}
		
				if(keyPressed -> code == Keyboard::Key::P)
				paused++;
				
			}
			if(const auto* keyReleased = event->getIf<Event::KeyReleased>())
			{
				if(keyReleased->code == Keyboard::Key::Q)
					qHeld = false;
			}
		}
		if(health1 <= 0 && health2 <= 0)
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
			initializeEnemies(width, length);
			initializeGun(20.0f);
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
			make_maze(Gamewin);
			//drawBossBar(Gamewin);
			//drawBoss(Gamewin);
			//drawEnemies(Gamewin);
			DrawHealthBar(Gamewin);
			drawPlayer(Gamewin);
			if(!ispaused)
			{
				movePlayer(width,length, player1X, player1Y);
				gunSound(gun_sound, players);
				int bossHits = moveBoss(Gamewin, player1X, player1Y, player2X, player2Y, players);
				int enemyHits = moveEnemies(player1X, player1Y, player2X, player2Y, players);
				moveGun(Gamewin);
				bossHealth = getBossHealth();
				
				if(bossHits == 1)
				health1 = takeDamage(10);
				if(bossHits == 2)
				health2 = takeDamagePlayer2(10);
				if(bossHits == 3)
				{
					health1 = takeDamage(10);
					health2 = takeDamagePlayer2(10);
				}

				if(enemyHits == 1)
				health1 = takeDamage(10);
				if(enemyHits == 2)
				health2 = takeDamagePlayer2(10);
				if(enemyHits == 3)
				{
					health2 = takeDamagePlayer2(10);
					health1 = takeDamage(10);
				}
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
	cout << width << " x " << length << endl;
}