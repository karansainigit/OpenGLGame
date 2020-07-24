#include "_sounds.h"

ISoundEngine* engine = createIrrKlangDevice();

sounds::sounds()
{
    //ctor

}

sounds::~sounds()
{
    //dtor
    engine->drop(); // delete engine
}
void sounds::playMusic(char* File)
{
      engine->play2D(File,true);

}

void sounds::playSound(char* File)
{
     engine->play2D(File,false,false);

}

void sounds::pauseSound(char* File)
{
    engine->play2D(File, true,false);
}

void sounds::stopAllSounds()
{

}


int sounds::initSounds()
{

     if (!engine)
	{
		cout<<"Could not startup engine\n";
		return 0; // error starting up the engine
	}
	return 1;
}


