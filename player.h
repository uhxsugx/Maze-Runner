#pragma once

#include <SFML/Graphics.hpp>

void initializePlayer();
void drawPlayer(sf::RenderWindow& window);
void movePlayer(int windowWidth, int windowHeight);
void takeDamage(int damage);
void DrawHealthBar(sf::RenderWindow& w);
bool GameOver()