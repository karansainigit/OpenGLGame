#ifndef _INPUTS_H
#define _INPUTS_H

#include <windows.h>
#include <_parallax.h>
#include <_level.h>
#include <_player.h>
#include <_landingPage.h>
#include <_intro.h>
#include <_gameMenu.h>
#include <_helpPage.h>
#include <_pause.h>
#include <_credits.h>
#include <_endPage.h>

class _inputs
{
    public:
        _inputs();
        virtual ~_inputs();

        void keyPressed(_level *, _player *);              //player handling
        void keyPressed(_landingPage *);                   //input handling for landing page
        void keyPressed(_intro *);                         //input handling for introduction page
        void keyPressed(_gameMenu *, _level *, _player *); //input handling for game menu page
        void keyPressed(_helpPage *);                      //input handling for help page
        void keyPressed(_pause *);                         //input handling for game pause page
        void keyPressed(_credits *);                       //input handling for credits page
        void keyPressed(_endPage* ep);                     //input handling for end page

        void mouseEventDown(_landingPage *);                             //handling mouse clicks for landing page
        void mouseEventDown(_gameMenu *, _level *, _player *, int, int); //handling mouse clicks for game menu page
        void mouseEventDown(_pause *, int, int);                         //handling mouse clicks for pause page
        void mouseEventDown(_endPage *, int, int);                       //handling mouse clicks for end page

        WPARAM wParam;  //Windows message parameter
        int flag;       //flag used for each screen
        int returnFlag; //screen for going back
};

#endif // _INPUTS_H
