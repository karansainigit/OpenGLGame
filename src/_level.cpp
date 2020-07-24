#include <math.h>
#include "_level.h"

//_textureLoader *bTex = new _textureLoader();

_level::_level()
{
    //ctor

    //object sizes
    platformW = 0.8;
    platformH = 0.08;
    itemW = 0.1;
    itemH = 0.1;
    enemyW = 0.3;
    enemyH = 0.3;

    //create level objects
    platforms = new _platform[5 * 10];
    items = new _item[5 * 10 * 3];
    enemies = new _enemy[5 * 30];

    //start at 1st level
    number = 1;

    restart();
}

_level::~_level()
{
    //dtor
    delete[] platforms;
    delete[] items;
    delete[] enemies;
}

void _level::initLevel(char* fileName1, char* fileName2, char* fileName3, char* fileName4, char* fileName5, char* fileName6, char* fileName7)
{
    platformTex->loadTexture(fileName1);  //load image by filename
    itemTex->loadTexture(fileName2);  //load image by filename
    livesTex->loadTexture(fileName3);  //load image by filename
    scoreTex->loadTexture(fileName4);  //load image by filename
    enemy0Tex->loadTexture(fileName5);  //load image by filename
    enemy1Tex->loadTexture(fileName6);  //load image by filename
    enemy2Tex->loadTexture(fileName7);  //load image by filename
}

void _level::restart()
{
    //create random platforms with items on 2D grid
    srand(1 + number);
    numPlatforms = 0;
    numItems = 0;
    score = 0;
    for(int y = 0; y < 4; y++)
    for(int x = 0; x < 10; x++)
    {
        //create optional platform at this position
        if(rand() % 2 == 0)
        {
            //platform position
            platforms[numPlatforms].posX = getPlatformX(x);
            platforms[numPlatforms].posY = getPlatformY(y);
            numPlatforms++;

            //create optional item at this position
            //(more items at higher levels)
            if(rand() % (4 - number) == 0)
            {
                //3 items per platform
                for(int i = -1; i <= 1; i++)
                {
                    //item position
                    items[numItems].posX = getPlatformX(x + i * 0.25);
                    items[numItems].posY = getPlatformY(y) + platformH * 0.5 + itemH * 0.5;
                    items[numItems].visible = true;
                    numItems++;
                }
            }
        }
    }

    //create random enemies on 2D grid
    srand(4 + number);
    numEnemies = 0;
    for(int y = -1; y < 4; y++)
    for(int x = -10; x < 20; x++)
    {
        //create optional enemy at this position
        //(more enemies at higher levels)
        if(rand() % (6 - number) == 0)
        {
            //enemy position
            enemies[numEnemies].posX = getPlatformX(x);
            enemies[numEnemies].posY = getPlatformY(y) + platformH * 0.5 + enemyH * 0.35;
            enemies[numEnemies].visible = true;

            //random enemy type (walking dragons at floor positions)
            enemies[numEnemies].type = rand() % 2;
            if(y == -1) enemies[numEnemies].type = 2;
            numEnemies++;
        }
    }
}

void _level::update(float timeStep)
{
    //update enemies
    for(int i = 0; i < numEnemies; i++)
    {
        //ignore hidden enemies
        if(!enemies[i].visible) continue;

        //update enemy position
        //(faster enemies at higher levels)
        float speed = number * 0.2;
        enemies[i].posX -= speed * timeStep;

        //wrap around
        if(enemies[i].posX < getPlatformX(-10))
            enemies[i].posX += getPlatformX(20) - getPlatformX(-10);
    }
}

void _level::drawText(float x, float y, string text, float r, float g, float b)
{
    //calculate text width
    float width = 0;
    for(size_t i = 0; i < text.size(); i++)
        width += glutStrokeWidth(GLUT_STROKE_ROMAN, text[i]);

    //use lines
    glColor3f(r, g, b);
    glLineWidth(5);
    glEnable(GL_LINE_SMOOTH);
    glDisable(GL_TEXTURE_2D);

    //draw characters
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(0.001, 0.001, 0.001);
    glTranslatef(-width / 2, 0, 0);
    for(size_t i = 0; i < text.size(); i++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glColor3f(1, 1, 1);
}

void _level::drawMessage(string text1, string text2)
{
    //draw message in 2 lines
    drawText(0.0, -0.75, text1, 1, 1, 1);
    drawText(0.0, -0.90, text2, 1, 1, 1);
}

void _level::drawLives(int lives)
{
    //draw lives background
    livesTex->TextureBinder();  //binding the texture
    float x0 = -2.0, x1 = -1.7;
    float y0 = +0.7, y1 = +1.0;
    glBegin(GL_QUADS);
    glTexCoord2f(0, 1);
    glVertex2f(x0, y0);
    glTexCoord2f(1, 1);
    glVertex2f(x1, y0);
    glTexCoord2f(1, 0);
    glVertex2f(x1, y1);
    glTexCoord2f(0, 0);
    glVertex2f(x0, y1);
    glEnd();

    //draw lives text
    ostringstream stream;
    stream << lives;
    drawText(-1.6, 0.75, stream.str(), 1, 0, 0);
}

void _level::drawScore()
{
    //draw score background
    scoreTex->TextureBinder();  //binding the texture
    float x0 = 1.7, x1 = 2.0;
    float y0 = 0.7, y1 = 1.0;
    glBegin(GL_QUADS);
    glTexCoord2f(0, 1);
    glVertex2f(x0, y0);
    glTexCoord2f(1, 1);
    glVertex2f(x1, y0);
    glTexCoord2f(1, 0);
    glVertex2f(x1, y1);
    glTexCoord2f(0, 0);
    glVertex2f(x0, y1);
    glEnd();

    //draw score text
    ostringstream stream;
    stream << score << "/" << numItems * 80 / 100;
    drawText(+1.5, 0.75, stream.str(), 1, 1, 0);
}

void _level::draw()
{
    glColor3f(1.0,1.0,1.0);

    float xMin = 0, yMin = 0, xMax = 1, yMax = 1;

    //draw platforms
    platformTex->TextureBinder();  //binding the texture
    for(int i = 0; i < numPlatforms; i++)
    {
        //draw platform as rectangle
        glPushMatrix();
        glTranslated(platforms[i].posX, platforms[i].posY, 0);
        glBegin(GL_QUADS);
        glTexCoord2f(xMin, yMax);
        glVertex2f(-platformW/2, -platformH/2);
        glTexCoord2f(xMax, yMax);
        glVertex2f(platformW/2, -platformH/2);
        glTexCoord2f(xMax, yMin);
        glVertex2f(platformW/2, platformH/2);
        glTexCoord2f(xMin, yMin);
        glVertex2f(-platformW/2, platformH/2);
        glEnd();
        glPopMatrix();
    }

    //draw items
    itemTex->TextureBinder();  //binding the texture
    for(int i = 0; i < numItems; i++)
    {
        //ignore hidden items
        if(!items[i].visible) continue;

        //draw item as rectangle
        glPushMatrix();
        glTranslated(items[i].posX, items[i].posY, 0);
        glBegin(GL_QUADS);
        glTexCoord2f(xMin, yMax);
        glVertex2f(-itemW/2, -itemH/2);
        glTexCoord2f(xMax, yMax);
        glVertex2f(itemW/2, -itemH/2);
        glTexCoord2f(xMax, yMin);
        glVertex2f(itemW/2, itemH/2);
        glTexCoord2f(xMin, yMin);
        glVertex2f(-itemW/2, itemH/2);
        glEnd();
        glPopMatrix();
    }

    //draw enemies
    for(int i = 0; i < numEnemies; i++)
    {
        //ignore hidden enemies
        if(!enemies[i].visible) continue;

        //select enemy texture
        if(enemies[i].type == 0) enemy0Tex->TextureBinder();  //binding the texture
        if(enemies[i].type == 1) enemy1Tex->TextureBinder();  //binding the texture
        if(enemies[i].type == 2) enemy2Tex->TextureBinder();  //binding the texture

        //sprite sheet coordinates
        if(enemies[i].type == 0)
        {
            //1st bird animation
            int xframe = clock() / 150 % 5;
            int yframe = 4;
            xMin = (xframe * +184.0 +  30) / 920;
            xMax = (xframe * +184.0 + 154) / 920;
            yMin = (yframe * -184.0 + 860) / 920;
            yMax = (yframe * -184.0 + 736) / 920;
        }
        if(enemies[i].type == 1)
        {
            //2nd bird animation
            int xframe = clock() / 150 % 5;
            int yframe = 3;
            xMin = (xframe * +156.5 +   0) / 749;
            xMax = (xframe * +156.5 + 130) / 749;
            yMin = (yframe * -205.0 + 876) / 924;
            yMax = (yframe * -205.0 + 746) / 924;
        }
        if(enemies[i].type == 2)
        {
            //dragon animation
            int xframe = clock() / 150 % 5;
            int yframe = 2;
            xMin = (xframe * +192.0 +   0) / 576;
            xMax = (xframe * +192.0 + 180) / 576;
            yMin = (yframe * -192.0 + 784) / 768;
            yMax = (yframe * -192.0 + 604) / 768;
        }

        //draw enemy as rectangle
        glPushMatrix();
        glTranslated(enemies[i].posX, enemies[i].posY, 0);
        glBegin(GL_QUADS);
        glTexCoord2f(xMin, yMin);
        glVertex2f(-enemyW/2, -enemyH/2);
        glTexCoord2f(xMax, yMin);
        glVertex2f(enemyW/2, -enemyH/2);
        glTexCoord2f(xMax, yMax);
        glVertex2f(enemyW/2, enemyH/2);
        glTexCoord2f(xMin, yMax);
        glVertex2f(-enemyW/2, enemyH/2);
        glEnd();
        glPopMatrix();
    }
}

float _level::getPlatformX(float index)
{
    //horizontal platform position
    return (index + 1) * platformW;
}

float _level::getPlatformY(float index)
{
    //vertical platform position
    return index * platformH * 3.5 - 0.5;
}

bool _level::collidePlatforms(float& x, float& y)
{
    //collide with platforms
    for(int i = 0; i < numPlatforms; i++)
    {
        //compare coordinates
        if(fabs(x - platforms[i].posX) < platformW * 0.51)
        if(fabs(y - platforms[i].posY) < platformH * 0.50)
        {
            //align with platform
            y = platforms[i].posY + platformH * 0.5;
            return true;
        }
    }

    //collide with ground
    float groundY = getPlatformY(-1);
    if(y < groundY)
    {
        //align with ground
        y = groundY;
        return true;
    }

    //nothing collided
    return false;
}

bool _level::collideItems(sounds* snds, float x, float y)
{
    //collide with items
    for(int i = 0; i < numItems; i++)
    {
        //ignore hidden items
        if(!items[i].visible) continue;

        //compare coordinates
        if(fabs(x - items[i].posX) < itemW * 2)
        if(fabs(y - items[i].posY) < itemH)
        {
            //hide collided item
            items[i].visible = false;
            score++;
            snds->playSound("sounds/item.wav");
            return true;
        }
    }

    //nothing collided
    return false;
}

bool _level::collideEnemies(sounds* snds, float x, float y)
{
    //collide with enemies
    for(int i = 0; i < numEnemies; i++)
    {
        //ignore hidden enemies
        if(!enemies[i].visible) continue;

        //compare coordinates
        if(fabs(x - enemies[i].posX) < enemyW * 0.5)
        if(fabs(y - enemies[i].posY + enemyH * 0.2) < enemyH * 0.3)
        {
            snds->playSound("sounds/death.wav");
            return true;
        }
    }

    //nothing collided
    return false;
}
