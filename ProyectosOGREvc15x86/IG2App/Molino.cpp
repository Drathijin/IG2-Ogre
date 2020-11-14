#include "Molino.h"
#include "IG2App.h"


Molino::Molino(Ogre::SceneManager* sm, int n, Nodo* parent) :
	EntidadIG(parent->createChildSceneNode())
{
	mSM = sm;
	aspasParent = mNode->createChildSceneNode();
	helpers::createEntity(mSM, cilindroNode, "paredes", "Barrel.mesh", mNode, "Molino/Paredes")->scale({ 10.5,45,10.5 });
	cilindroNode->setPosition({ 0,0,0 });

	helpers::createEntity(mSM, esferaNode, "techo", "sphere.mesh", mNode, "Molino/Techo")->scale({ 0.25,0.25,0.25 });
	esferaNode->setPosition({ 0,130,0 });

	aspas = new AspasMolino(n, true, aspasParent, 10);

	aspasParent->translate({ 0,125,34 });
}

bool Molino::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	static bool botonPaTras = false;
	if (evt.keysym.sym == SDLK_h)
	{
		aspasParent->translate({ 0, 0, -34 }, Ogre::Node::TS_LOCAL);
		aspasParent->yaw(Ogre::Degree(10), Ogre::Node::TS_LOCAL);
		aspasParent->translate({ 0, 0, 34 }, Ogre::Node::TS_LOCAL);
	}
	else if (evt.keysym.sym == SDLK_c)
	{
		Ogre::Real z = botonPaTras ? 50 : -50;
		aspas->botoncicoNode->translate({ 0, 0, z });
		botonPaTras = !botonPaTras;
	}
	else if (evt.keysym.sym == SDLK_r)
	{
		spin = false;
		auto objs = esferaNode->getAttachedObjects();
		for (auto o : objs)
		{
			((Ogre::Entity*)o)->setMaterialName("Avion/Cuerpo");
		}
		sendEvent(EntidadIG::MessageType::emptyRiver, nullptr);
	}
	return true;
}

void Molino::frameRendered(const Ogre::FrameEvent& evt)
{
	if (spin)
		aspas->girarAspas(evt.timeSinceLastEvent);
}