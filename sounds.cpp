#include <SFML/Audio.hpp>
#include <iostream>

using namespace std;
using namespace sf;

void backgroundMusic(Music &music, int level)
{
    if(level == 1 || level == 0)
    {
        if(!music.openFromFile("data/music/Bellhart.mp3"))
        {
            cout << "Nah lol" << endl;
            return;
        }
    }

    if(level == 2)
    {
        if(!music.openFromFile("data/music/High-Halls.mp3"))
        {
            cout << "Nah lol" << endl;
            return;
        }
    }
    
    if(level == 3)
    {
        if(!music.openFromFile("data/music/Choral-Chambers.mp3"))
        {
            cout << "Nah lol" << endl;
            return;
        }
    }
    
    if(level == 4)
    {
        if(!music.openFromFile("data/music/Gestral-Party.mp3"))
        {   cout << "Nah lol" << endl;
            return;
        }
    }
    if(level == 5)
    {
        if(!music.openFromFile("data/music/Unitll-we-win.mp3"))
        {
            cout << "Nah lol" << endl;
            return;
        }
    }
    music.play();
}