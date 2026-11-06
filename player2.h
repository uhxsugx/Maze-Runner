
#pragma once
#include <SFML/Graphics.hpp>

extern int player2X, player2Y, player2Health, player2Speed;

void initializePlayer2();
void drawPlayer2(sf::RenderWindow& window);
void movePlayer2(int windowWidth, int windowHeight);
void takeDamagePlayer2(int damage);
void DrawHealthBarPlayer2(sf::RenderWindow& window);
