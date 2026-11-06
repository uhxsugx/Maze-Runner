#pragma once
#include <SFML/Graphics.hpp>
void pauseGame();
int handlePauseInput(sf::Keyboard::Key);
void initializePauseMenu();
void drawPauseMenu(sf::RenderWindow&);