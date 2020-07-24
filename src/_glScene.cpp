#include "_glScene.h"
#include <_inputs.h>
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
#include <_sounds.h>

//pointers of classes
_inputs *kBMs = new _inputs();
_parallax *plxSky = new _parallax();
_parallax *plxFloor = new _parallax();
_level *lvl = new _level();
_player *ply = new _player();
_landingPage *lp = new _landingPage();
_landingPage *lpstars = new _landingPage();
_intro * intro = new _intro();
_gameMenu * mp = new _gameMenu();
_helpPage * hp = new _helpPage();
_pause * pause = new _pause();
_credits * cp = new _credits();
_credits * cpname = new _credits();
_endPage *ep = new _endPage();

sounds *snds = new sounds();

_glScene::_glScene()
{
    //ctor
}

_glScene::~_glScene()
{
    //dtor
}
GLint _glScene::initGL()
{
    glClearColor(1.0f, 0.5f, 0.0f, 1.0f);   //background color R, G, B, Alpha
    glClearDepth(1.0f);                     //Depth Clearance
    glShadeModel(GL_SMOOTH);                //to make graphics nicer
    glDisable(GL_DEPTH_TEST);               //disabling Depth Test
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    plxSky->parallaxInit("images/background.png");  //load parallax image of sky
    plxFloor->parallaxInit("images/floor.png");  //load parallax image of floor
    lvl->initLevel(
        "images/platform.png",
        "images/item.png",
        "images/lives.png",
        "images/score.png",
        "images/enemy0.png",
        "images/enemy1.png",
        "images/enemy2.png");  //load level images
    lp->landingPageInit("images/landingpage.png");  //load image of game landing page
    lpstars->landingPageInit("images/stars.png");  //load image of stars to be scrolled on landing page
    intro->introPageInit("images/introduction.png");     //load image of introduction page
    mp->menuPageInit("images/gamemenu.png");  //load image of game menu screen
    hp->helpPageInit("images/help.png");  //load image of help page
    cp->creditsPageInit("images/credits.png");  //load image of credits page
    cpname->creditsPageInit("images/creditsname.png");  //load image of credits name to be scrolled on credits page
    pause->initPause("images/pause.png");  //load image of pause page
    ply->initPlayer("images/player.png");  //loading player sprite sheet
    ep->endPageInit("images/endpagewin.png", "images/endpagelose.png");  //load image of help page

    snds->initSounds();     //initializing sound
    snds->playMusic("sounds/music.mp3");        //game music
    return true;
}

GLint _glScene::drawScene()
{
    //get time step as difference between current and previous clocks
    clock_t currentTime = clock();
    static clock_t previousTime = currentTime;
    float timeStep = (currentTime - previousTime) * 0.001;
    previousTime = currentTime;

    if (kBMs->flag == 0)  //landing page
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//Clear Screen And Depth Buffer
        glLoadIdentity();
        glPushMatrix();
        lp->drawSquare();       //draw background for landing page
        lpstars->drawSquare();  //draw stars on landing page
        lpstars->lpscroll(true, "up", 0.0005);  //scrolling stars on landing page
        glPopMatrix();
    }

    if (kBMs->flag == 1)  //game menu
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//Clear Screen And Depth Buffer
        glLoadIdentity();
        glPushMatrix();
        mp->drawSquare();       //draw background for game menu screen
        glPopMatrix();
    }

    if (kBMs->flag == 2)  //help page
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//Clear Screen And Depth Buffer
        glLoadIdentity();
        glPushMatrix();
        hp->drawSquare();       //draw background for help page
        glPopMatrix();
    }

    if (kBMs->flag == 3)  //game
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//Clear Screen And Depth Buffer
        glLoadIdentity();

        //draw sky
        glPushMatrix();
        plxSky->xMin = 0 + ply->posX / 10;
        plxSky->xMax = 1 + ply->posX / 10;
        plxSky->drawSquare();       //draw sky background for game
        glPopMatrix();

        //draw level
        glPushMatrix();
        glTranslated(-ply->posX, 0, 0);
        if(ply->state == _player::alive)
            lvl->update(timeStep);
        lvl->draw();       //draw level for game
        glPopMatrix();

        //update player
        if(ply->state == _player::alive)
        {
            ply->update(lvl, snds, timeStep);

            //game won
            if(ply->state == _player::completed && lvl->number == 3)
            {
                kBMs->flag = 6;
                lvl->number = 1;
                lvl->restart();
                ply->restart(true, true);
            }

            //game lost
            if(ply->lives < 0)
            {
                kBMs->flag = 7;
                lvl->number = 1;
                lvl->restart();
                ply->restart(true, true);
            }
        }

        //draw player
        glPushMatrix();
        glTranslated(-ply->posX, 0, 0);
        ply->draw();
        glPopMatrix();

        //draw floor
        glPushMatrix();
        plxFloor->xMin = 0 + ply->posX / 4;
        plxFloor->xMax = 1 + ply->posX / 4;
        plxFloor->drawSquare();
        glPopMatrix();

        //draw game info
        ostringstream stream;
        stream << "Level " << lvl->number;
        lvl->drawText(0.0, 0.85, stream.str(), 0.1, 0.2, 0.3);
        lvl->drawLives(ply->lives);
        lvl->drawScore();

        //draw game message
        if(ply->state == _player::dead)
            lvl->drawMessage("You lose a life!", "Press 'Space' to continue");
        if(ply->state == _player::completed)
            lvl->drawMessage("Level completed!", "Press 'Space' for next level");
    }

    if (kBMs->flag == 4)  //pause page
    {
        //draw background for pause page
        pause->drawSquare();
    }

    if (kBMs->flag == 5)  //credits page
    {
        //draw background for credits page
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//Clear Screen And Depth Buffer
        glLoadIdentity();
        glPushMatrix();
        cp->drawSquare();

        //draw background for credits name
        glScalef(0.8, 0.8, 1.0);  //unscaling for credits name
        cpname->drawSquare();
        cpname->cpscroll(true, "down", 0.0005);  //scrolling credits name
        glPopMatrix();
    }

    if (kBMs->flag == 6 || kBMs->flag == 7)  //end page for winning or losing
    {
        //draw background for end page
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//Clear Screen And Depth Buffer
        glLoadIdentity();
        glPushMatrix();
        bool win = kBMs->flag == 6;
        ep->drawSquare(win);
        glPopMatrix();
    }

    if (kBMs->flag == 8)  //intro page
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//Clear Screen And Depth Buffer
        glLoadIdentity();
        glPushMatrix();
        intro->drawSquare();       //draw background for intro page
        glPopMatrix();
    }
}

GLvoid _glScene::reSizeScene(GLsizei width, GLsizei height)  //to resize window
{
    //update viewport
    glViewport(0, 0, width, height);

    //set parallel projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2, 2, -1, 1, -1000, 1000);

    //set identity modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int _glScene::winMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    //click position
    int x = (short)LOWORD(lParam);
    int y = (short)HIWORD(lParam);

    switch(uMsg)
    {
        case WM_KEYDOWN:
            kBMs->wParam = wParam;
            kBMs->keyPressed(pause);        //handling key inputs on game pause page
            kBMs->keyPressed(lvl, ply);     //handling player movement
            kBMs->keyPressed(lp);           //handling key inputs on landing page
            kBMs->keyPressed(intro);        //handling key inputs on introduction page
            kBMs->keyPressed(mp, lvl, ply); //handling key inputs on game menu page
            kBMs->keyPressed(hp);           //handling key inputs on help page
            kBMs->keyPressed(cp);           //handling key inputs on credits page
            kBMs->keyPressed(ep);           //handling key inputs on end page
            break;

        case WM_LBUTTONDOWN:
            kBMs->wParam = wParam;
            kBMs->mouseEventDown(mp, lvl, ply, x, y); //handling left mouse click on game menu page
            kBMs->mouseEventDown(pause, x, y);        //handling left mouse click on pause page
            kBMs->mouseEventDown(ep, x, y);           //handling left mouse click on end page
            kBMs->mouseEventDown(lp);                 //handling left mouse click on landing page
            break;
        case WM_RBUTTONDOWN:
            kBMs->wParam = wParam;
            kBMs->mouseEventDown(lp);       //handling right mouse click on landing page
            break;
        case WM_MBUTTONDOWN:
            kBMs->wParam = wParam;
            break;
    }
}
