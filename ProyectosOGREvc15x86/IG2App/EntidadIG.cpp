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

void EntidadIG::sendEvent(MessageType msj, EntidadIG* entidad)
{
	for (EntidadIG* e : appListeners)
	{
		if (e)
		{
			e->receiveEvent(msj, nullptr);
		}
	}
}

bool EntidadIG::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	/*if (evt.keysym.sym == SDLK_k) {
	}*/
	return true;
}