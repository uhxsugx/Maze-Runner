#pragma once

#include <SFML/Graphics.hpp>

void initializeBoss(int width, int length);
void drawBoss(sf::RenderWindow &window);
void drawBossBar(sf::RenderWindow &window);
int bossDamage(int damage);
int moveBoss(sf::RenderWindow &window, int player1X, int player1Y, int player2X, int player2Y, int mode);