#ifndef _PAUSE_H
#define _PAUSE_H

#include <_textureLoader.h>

class _pause
{
    public:
        _pause();
        virtual ~_pause();

        void drawSquare();     //to draw a quad for the background
        void initPause(char*); //load image to background

        _textureLoader *pauseTex = new _textureLoader();        //creating pointer for texture loader
};

#endif // _PAUSE_H
