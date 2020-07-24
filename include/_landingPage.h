#ifndef _LANDINGPAGE_H
#define _LANDINGPAGE_H

#include <_textureLoader.h>

class _landingPage
{
    public:
        _landingPage();
        virtual ~_landingPage();

        void drawSquare();  //to draw a quad for the background
        void landingPageInit(char* );   //Load images to background
        void lpscroll(bool, string, float); //bool for Auto, string for direction, speed of the movement

        _textureLoader *lpTex = new _textureLoader();   //creating pointer for texture loader

        float xMax, yMax, xMin, yMin;   //for texture coordinates

    protected:

    private:
};

#endif // _LANDINGPAGE_H
