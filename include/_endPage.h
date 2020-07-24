#ifndef _ENDPAGE_H
#define _ENDPAGE_H

#include <_textureLoader.h>

class _endPage
{
    public:
        _endPage();
        virtual ~_endPage();
        void endPageInit(char*, char*);      //Load images to background
        void drawSquare(bool);  //to draw a quad for the background

        _textureLoader *epTexWin = new _textureLoader();   //creating pointer for texture loader
        _textureLoader *epTexLose = new _textureLoader();   //creating pointer for texture loader
};

#endif // _ENDPAGE_H
