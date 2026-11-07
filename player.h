#pragma once

#include <SFML/Graphics.hpp>

void initializePlayer();
void drawPlayer(sf::RenderWindow& window);
void movePlayer(int windowWidth, int windowHeight);
int takeDamage(int damage);
void DrawHealthBar(sf::RenderWindow& w);
