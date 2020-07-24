#ifndef _PLAYER_H
#define _PLAYER_H
#include <math.h>
#include <time.h>
#include <_level.h>

#include <GL/gl.h>
#include <_textureLoader.h>
#include <_sounds.h>

class _player
{
    public:
        _player();
        virtual ~_player();

        void initPlayer(char*);     //player initialization with filename
        void restart(bool, bool);   //re spawning player after death
        void update(_level*, sounds*, float);   //player movements
        void draw();                //draw player using sprite sheet

        _textureLoader *playerTex = new _textureLoader();   //creating pointer for texture loader
        float posX, posY;          //player position
        float sizeX, sizeY;        //player size
        float angle;               //player rotation angle
        float runSpeed, jumpSpeed; //player speed
        bool facingRight;          //player left/right direction
        int lives;                 //number of lives left
        int xframes, yframes;      //frames in sprite sheet
        int xframe, yframe;        //current frame in sprite sheet
        enum {alive, dead, completed} state; //player state
};

#endif // _PLAYER_H
