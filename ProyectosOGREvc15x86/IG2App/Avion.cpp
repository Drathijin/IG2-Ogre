#pragma once
#include "Avion.h"
#include "IG2App.h"

Avion::Avion(Nodo* parent) :
	EntidadIG(parent->createChildSceneNode())
{
	helpers::createEntity(mSM, mCuerpoNode, "AvionCuerpo", "sphere.mesh", mNode, "Avion/Cuerpo");

	float scale = 2.5;
	float offset = 200;

	helpers::createEntity(mSM, malaINode, "AvionAlaI", "cube.mesh", mNode, "Avion/Alas");
	malaINode->scale({ scale,0.1,1 });
	malaINode->translate({ offset,0,0 });
	heliceNodeL = mNode->createChildSceneNode();
	left = new AspasMolino(5, 1, heliceNodeL, 2000);
	heliceNodeL->translate({ offset,0,50 });


	helpers::createEntity(mSM, malaDNode, "AvionAlaD", "cube.mesh", mNode, "Avion/Alas");
	malaDNode->scale({ scale,0.1,1 });
	malaDNode->translate({ -offset,0,0 });
	heliceNodeR = mNode->createChildSceneNode();
	right = new AspasMolino(5, 1, heliceNodeR, 2000);
	heliceNodeR->translate({ -offset,0,50 });

	helpers::createEntity(mSM, botoncico, "boton879879754321xD", "Barrel.mesh", mNode, "Avion/Botoncico")->pitch(Ogre::Degree(90));
	botoncico->translate({ 0,0,100 });
	botoncico->scale({ 10,2,10 });

	helpers::createEntity(mSM, pilotoNode, "piloto", "ninja.mesh", mNode, "Avion/Piloto");
	pilotoNode->translate({ 0,-30,-15 });
	pilotoNode->yaw(Ogre::Degree(180));

	planeLight = mSM->createLight("planeLight");
	planeLight->setType(Ogre::Light::LT_SPOTLIGHT);
	planeLight->setDiffuseColour(0.75, 0.75, 0.75);
	planeLight->setDirection({ 1,-1,0 });
	planeLight->setSpotlightOuterAngle(Ogre::Degree(90));


	//planeLight->setDiffuseColour(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
	//planeLight->setDirection(Ogre::Vector3(1, -1, 0));
	//planeLight->setSpotlightInnerAngle(Ogre::Degree(5.0f));
	//planeLight->setSpotlightOuterAngle(Ogre::Degree(45.0f));
	//planeLight->setSpotlightFalloff(0.0f);

	planeLight->setCastShadows(true);
	auto lightNode = mNode->createChildSceneNode();
	lightNode->attachObject(planeLight);
	lightNode->translate({ 0,-40,0 });

	mSM->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
}


bool Avion::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_r)
	{
		spin = false;
		planeLight->setVisible(false);
	}
	return true;
}

void Avion::frameRendered(const Ogre::FrameEvent& evt)
{
	left->girarAspas(evt.timeSinceLastEvent);
	right->girarAspas(evt.timeSinceLastEvent);
	float delta = evt.timeSinceLastEvent;

	float x = 200;
	float z = 200;
	if (spin)
	{
		mNode->translate({ x,-200,z }, Ogre::Node::TS_LOCAL);
		mNode->yaw(Ogre::Degree(20 * delta));
		mNode->translate({ -x,200,-z }, Ogre::Node::TS_LOCAL);
	}

}
