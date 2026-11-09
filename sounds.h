// Traditional Include Guard
#ifndef MY_HEADER_H
#define MY_HEADER_H

// Header content here


#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

int backgroundMusic(sf::Music &music, int level);
void gunSound(sf::Sound &sound, int mode);

#endif // MY_HEADER_H
