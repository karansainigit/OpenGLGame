#include "_player.h"

_player::_player()
{
    //ctor

    //player size
    sizeX = 0.4;
    sizeY = 0.3;

    //frames of sprite sheet
    xframes=5;
    yframes=4;

    //current frame
    xframe = 0;
    yframe = 3;

    restart(true, true);
}

_player::~_player()
{
    //dtor
}

void _player::initPlayer(char *fileName)
{
    playerTex->loadTexture(fileName);   //load image by filename
}

void _player::restart(bool resetLives, bool resetPosition)      //re spawning player after death
{
    if(resetLives)
        lives = 5;      //initial lives

    //initialize speeds
    runSpeed = 1;
    jumpSpeed = 0;

    //use right direction by default
    facingRight = true;

    //initial position
    if(resetPosition)
        posX = 0;
    posY = 1;

    //initial rotation angle
    angle = 0.0;

    state = alive;
}

void _player::update(_level* lvl, sounds* snds, float timeStep)     //player movements
{
    //move left
    if(GetAsyncKeyState(VK_LEFT))
    {
        facingRight = false;
        posX -= runSpeed * timeStep;

        //limit left position
        if(posX < lvl->getPlatformX(-2))
            posX = lvl->getPlatformX(-2);
    }

    //move right
    if(GetAsyncKeyState(VK_RIGHT))
    {
        facingRight = true;
        posX += runSpeed * timeStep;

        //limit right position
        if(posX > lvl->getPlatformX(11))
            posX = lvl->getPlatformX(11);
    }

    //jump
    if(GetAsyncKeyState(VK_UP) && jumpSpeed == 0)
    {
        jumpSpeed = 1.2;
        snds->playSound("sounds/jump.wav");
    }

    //update jump speed due to gravity
    float gravity = -2.0;
    jumpSpeed += gravity * timeStep;
    posY += jumpSpeed * timeStep;

    //collide with platforms
    if(jumpSpeed < 0 && lvl->collidePlatforms(posX, posY))
    {
        //stop jumping
        jumpSpeed = 0;
    }

    //collide with items
    if(lvl->collideItems(snds, posX, posY))
    {
        //if collected 80% items
        if(lvl->score == lvl->numItems * 80 / 100)
        {
            //level completed
            state = completed;
        }
    }

    //collide with enemies
    if(lvl->collideEnemies(snds, posX, posY))
    {
        //death from enemy
        lives--;
        state = dead;
    }

    //rotate when jumping
    angle = atan(jumpSpeed) * 20;
    if(!facingRight) angle = -angle;
}

void _player::draw()
{
    //frame animation
    xframe = clock() / 150 % 8;
    if(xframe >= 5) xframe = 8 - xframe;

    //sprite sheet coordinates
    float xMin = (xframe * 153.0 +   0) / 750;
    float xMax = (xframe * 153.0 + 138) / 750;
    float yMin = (yframe * 139.0 +   0) / 516;
    float yMax = (yframe * 139.0 +  97) / 516;

    //change left/right direction
    if(facingRight)
        std::swap(xMin, xMax);

    //set player position and angle
    glPushMatrix();
    glTranslatef(posX, posY, 0);
    glRotatef(angle, 0.0, 0.0, 1.0);

    //draw player as quad
    playerTex->TextureBinder();
    glBegin(GL_QUADS);
    glTexCoord2f(xMin, yMax);
    glVertex2f(-sizeX/2, 0);
    glTexCoord2f(xMax, yMax);
    glVertex2f(sizeX/2, 0);
    glTexCoord2f(xMax, yMin);
    glVertex2f(sizeX/2, sizeY);
    glTexCoord2f(xMin, yMin);
    glVertex2f(-sizeX/2, sizeY);
    glEnd();
    glPopMatrix();
}
