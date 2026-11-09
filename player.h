#pragma once

#include <SFML/Graphics.hpp>

void initializePlayer();
void drawPlayer(sf::RenderWindow& window);
void movePlayer(int windowWidth, int windowHeight, int &player1X, int &player1Y);
int takeDamage(int damage);
void DrawHealthBar(sf::RenderWindow& w);
// void initializebullet1(sf::RenderWindow &window);
// void shootGun1(sf::RenderWindow &w);
