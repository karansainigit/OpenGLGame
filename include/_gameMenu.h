#ifndef _GAMEMENU_H
#define _GAMEMENU_H

#include <_textureLoader.h>

class _gameMenu
{
    public:
        _gameMenu();
        virtual ~_gameMenu();

        void drawSquare();  //to draw a quad for the background
        void menuPageInit(char*);  //Load images to background

        _textureLoader *mpTex = new _textureLoader();  //creating pointer for texture loader

    protected:

    private:
};

#endif // _GAMEMENU_H
