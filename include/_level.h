#ifndef _LEVEL_H
#define _LEVEL_H

#include <iostream>
#include <sstream>
#include <string>
#include <time.h>
#include <GL/gl.h>
#include <windows.h>
#include <GL/glut.h>
#include <SOIL.h>
#include <_textureLoader.h>
#include <_sounds.h>
using namespace std;

struct _platform
{
    float posX, posY;       //position of platforms
};

struct _item
{
    float posX, posY;       //item position
    bool visible;           //visibility of item
};

struct _enemy
{
    float posX, posY;       //enemy position
    int type;               //enemy types
    bool visible;           //enemy visibility
};

class _level
{
    public:
        _level();
        virtual ~_level();

        void initLevel(char*, char*, char*, char*, char*, char*, char*);        //initializing level with all the images required for level
        void restart();         //for random number of platforms, item and enemies
        void update(float);     //updating enemies speed
        void drawText(float, float, string, float, float, float);       //drawing text
        void drawMessage(string, string);       //drawing message on screen
        void drawLives(int);        //drawing number of lives for player
        void drawScore();           //drawing score of player
        void draw();        //drawing level layout
        float getPlatformX(float);      //get x position of platform
        float getPlatformY(float);      //get y position of platform
        bool collidePlatforms(float&, float&);      //linear collision with platform
        bool collideItems(sounds*, float, float);   //linear collision with items
        bool collideEnemies(sounds*, float, float); //linear collision with enemies

        //creating pointer for texture loader
        _textureLoader *platformTex = new _textureLoader();
        _textureLoader *itemTex = new _textureLoader();
        _textureLoader *livesTex = new _textureLoader();
        _textureLoader *scoreTex = new _textureLoader();
        _textureLoader *enemy0Tex = new _textureLoader();
        _textureLoader *enemy1Tex = new _textureLoader();
        _textureLoader *enemy2Tex = new _textureLoader();

        int number;                 //level number
        int numPlatforms;           //number of platforms
        int numItems, score;        //total and collected number of items
        int numEnemies;             //total number of enemies
        float platformW, platformH; //platform size
        float itemW, itemH;         //item size
        float enemyW, enemyH;       //enemy size
        _platform *platforms;       //array of platforms
        _item *items;               //array of items
        _enemy *enemies;            //array of enemies
};

#endif // _LEVEL_H
