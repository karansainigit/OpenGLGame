#ifndef _HELPPAGE_H
#define _HELPPAGE_H

#include <_textureLoader.h>

class _helpPage
{
    public:
        _helpPage();
        virtual ~_helpPage();

        void drawSquare();  //to draw a quad for the background
        void helpPageInit(char* );      //Load images to background

        _textureLoader *hpTex = new _textureLoader();   //creating pointer for texture loader
};

#endif // _HELPPAGE_H
