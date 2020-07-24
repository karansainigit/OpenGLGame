#ifndef _CREDITS_H
#define _CREDITS_H

#include <_textureLoader.h>

class _credits
{
    public:
        _credits();
        virtual ~_credits();

        void drawSquare();  //to draw a quad for the background
        void creditsPageInit(char* );   //Load images to background
        void cpscroll(bool, string, float);  //bool for Auto, string for direction, speed of the movement

        _textureLoader *cpTex = new _textureLoader();  //creating pointer for texture loader

        float xMax, yMax, xMin, yMin;  //for texture coordinates

    protected:

    private:
};

#endif // _CREDITS_H
