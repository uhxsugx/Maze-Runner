#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

int make_maze(sf::RenderWindow &window, int level);
bool mazeCollision(float x, float y, float width, float height);
bool mazeCompleted(float x, float y, float width, float height);
void makebossroom(sf::RenderWindow &window);
void selectRandomMaze();
