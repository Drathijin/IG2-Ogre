#include "EntidadIG.h"
std::vector<EntidadIG*> EntidadIG::appListeners = std::vector<EntidadIG*>(0, nullptr);

bool Obj::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_k) {
	}
	return true;
}

void Obj::frameRendered(const Ogre::FrameEvent& evt)
{
}

EntidadIG::~EntidadIG()
{
}



bool EntidadIG::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	/*if (evt.keysym.sym == SDLK_k) {
	}*/
	return true;
}

