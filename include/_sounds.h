#ifndef SOUNDS_H
#define SOUNDS_H

#include <SNDS/irrKlang.h>

#include <stdlib.h>
#include <iostream>

//#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll
using namespace irrklang;


using namespace std;

class sounds
{
    public:
        sounds();
        virtual ~sounds();
        void playMusic(char *);     //playing game music
        void playSound(char *);     //playing game sounds
        void pauseSound(char *);    //to pause sounds
        void stopAllSounds();       //to stop all sounds
        int initSounds();           //initializing sound

    protected:

    private:
};



#endif // SOUNDS_H
