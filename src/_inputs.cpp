#include "_inputs.h"

#include <windows.h>
#include <math.h>

_inputs::_inputs()
{
    //ctor
    flag = 0;       //initializing flag to 0 for landing page to be displayed first
    returnFlag = 0;
}

_inputs::~_inputs()
{
    //dtor
}

void _inputs::keyPressed(_level *lvl, _player* ply)
{
    switch(wParam)
    {
        case VK_SPACE:   //continue after message
            if (flag == 3 && ply->state == _player::dead)
            {
                //respawn player after death
                ply->restart(false, false);
            }
            else if (flag == 3 && ply->state == _player::completed)
            {
                //go to next level
                lvl->number++;
                lvl->restart();
                ply->restart(false, true);
            }
            break;
        case 'H':
            if (flag == 3)
            {
                //show game help
                flag = 2;
                returnFlag = 3;
            }
            break;
    }
}

void _inputs::keyPressed(_landingPage* lp)
{
    switch(wParam)
    {
        case VK_RETURN:     //Enter to continue to game menu from landing page
            if (flag == 0)
            {flag = 8;}
            break;

        case VK_ESCAPE:     //Escape to exit from landing page
            if (flag == 0)
            {exit(0);}
            break;
    }

}

void _inputs::keyPressed(_intro* intro)
{
    switch(wParam)
    {
        case VK_SPACE:     //Space to continue to game menu from introduction page
            if (flag == 8)
            {flag = 1;}
            break;
    }
}


void _inputs::keyPressed(_gameMenu* mp, _level *lvl, _player* ply)
{
    switch(wParam)
    {
        case 'N': //start new game
            if (flag == 1)
            {
                flag = 3;
                lvl->number = 1;
                lvl->restart();
                ply->restart(true, true);
            }
            break;
        case 'R': //resume game
            if (flag == 1)
            {flag = 3;}
            break;
        case 'H': //help
            if (flag == 1)
            {
                flag = 2;
                returnFlag = 1;
            }
            break;
        case 'C': //credits
            if (flag == 1)
            {flag = 5;}
            break;
        case 'E': //exit
            if (flag == 1)
            {exit(0);}
            break;
    }
}

void _inputs::keyPressed(_helpPage* hp)
{
    switch(wParam)
    {
        case VK_ESCAPE:     //Escape key to return from help page
            if (flag == 2)
            {
                flag = returnFlag;
            }
            break;
    }

}

void _inputs::keyPressed(_credits* cp)
{
    switch(wParam)
    {
        case VK_ESCAPE:     //Escape key to return to game menu from credits page
            if (flag == 5)
            {flag = 1;}
            break;
    }
}


void _inputs::keyPressed(_pause* pause)
{
    switch(wParam)
    {
        case 'R': //resume game
            if (flag == 4)
            {flag = 3;}
            break;
        case 'H': //help
            if (flag == 4)
            {
                flag = 2;
                returnFlag = 3;
            }
            break;
        case 'M':     //return to main menu from pause page
            if (flag == 4)
            {flag = 1;}
            break;
        case VK_ESCAPE:     //Escape key to pause the game and escape again to continue
            if (flag == 4)
            {flag = 3;}
            else if (flag == 3)
            {flag = 4;}
            break;
    }

}

void _inputs::keyPressed(_endPage* ep)
{
    switch(wParam)
    {
        case 'M': //return to main menu from end page
            if (flag == 6 || flag == 7)
            {flag = 1;}
            break;
        case 'E': //exit
            if (flag == 6 || flag == 7)
            {exit(0);}
            break;
    }
}

void _inputs::mouseEventDown(_landingPage* lp)
{
    switch(wParam)
    {
        case MK_LBUTTON:    //left mouse click to continue to game menu from landing page
            if (flag == 0)
            {flag = 8;}
            break;
        case MK_RBUTTON:    //right mouse click to continue to game menu from landing page
            if (flag == 0)
            {flag = 8;}
            break;
    }
}

void _inputs::mouseEventDown(_gameMenu* mp, _level *lvl, _player* ply, int x, int y)
{
    if(flag != 1 || wParam != MK_LBUTTON)
        return;

    //get window size
    GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	float width = viewport[2];
	float height = viewport[3];

	//convert window coordinates to pixel coordinates in gamemenu.png
	x = x * 1000 / width;
	y = y * 500 / height;

	//transform mouse clicks to key presses
	wParam = 0;
    if(abs(x - 500) < 80 && abs(y - 186) < 10)
        wParam = 'N';
    if(abs(x - 500) < 100 && abs(y - 244) < 10)
        wParam = 'R';
    if(abs(x - 500) < 50 && abs(y - 301) < 10)
        wParam = 'H';
    if(abs(x - 500) < 70 && abs(y - 358) < 10)
        wParam = 'C';
    if(abs(x - 500) < 50 && abs(y - 416) < 10)
        wParam = 'E';

    //reuse key commands
    if(wParam)
        keyPressed(mp, lvl, ply);
}

void _inputs::mouseEventDown(_pause* pause, int x, int y)
{
    if(flag != 4 || wParam != MK_LBUTTON)
        return;

    //get window size
    GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	float width = viewport[2];
	float height = viewport[3];

	//convert window coordinates to pixel coordinates in pause.png
	x = x * 1024 / width;
	y = y * 512 / height;

	//transform mouse clicks to key presses
	wParam = 0;
    if(abs(x - 500) < 85 && abs(y - 234) < 10)
        wParam = 'R';
    if(abs(x - 500) < 65 && abs(y - 305) < 10)
        wParam = 'H';
    if(abs(x - 500) < 110 && abs(y - 378) < 10)
        wParam = 'M';

    //reuse key commands
    if(wParam)
        keyPressed(pause);
}

void _inputs::mouseEventDown(_endPage* ep, int x, int y)
{
    if(flag != 6 && flag != 7 || wParam != MK_LBUTTON)
        return;

    //get window size
    GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	float width = viewport[2];
	float height = viewport[3];

	//convert window coordinates to pixel coordinates in endpagewin.png and endpagelose.png
	x = x * 1024 / width;
	y = y * 512 / height;

	//transform mouse clicks to key presses
	wParam = 0;
    if(abs(x - 500) < 110 && abs(y - 276) < 10)
        wParam = 'M';
    if(abs(x - 500) < 60 && abs(y - 348) < 10)
        wParam = 'E';

    //reuse key commands
    if(wParam)
        keyPressed(ep);
}
