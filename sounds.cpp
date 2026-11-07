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
            cout << "Nah lol1" << endl;
            return;
        }
    }

    if(level == 2)
    {
        if(!music.openFromFile("data/music/High-Halls.mp3"))
        {
            cout << "Nah lol2" << endl;
            return;
        }
    }
    
    if(level == 3)
    {
        if(!music.openFromFile("data/music/Choral-Chambers.mp3"))
        {
            cout << "Nah lol3" << endl;
            return;
        }
    }
    
    if(level == 4)
    {
        if(!music.openFromFile("data/music/Gestral-Party.mp3"))
        {   cout << "Nah lol4" << endl;
            return;
        }
    }
    if(level == 5)
    {
        if(!music.openFromFile("data/music/Devola&Popola.mp3"))
        {
            cout << "Nah lol5" << endl;
            return;
        }
    }
    music.setLooping(true);
    music.play();
}