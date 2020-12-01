
#include "IG2App.h"

int main(int argc, char *argv[])     
{
	IG2App app;
  try {
    app.initApp();
    app.getRoot()->startRendering();
  }
  catch (Ogre::Exception& e) {
    Ogre::LogManager::getSingleton().logMessage("\033[0;31m An exception has occured: " + e.getFullDescription() + "\033[0m \n ");
  }
  app.closeApp();
  return 0;
}