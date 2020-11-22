#pragma once
#include "Avion.h"
#include "IG2App.h"
#include <OgreBillboardSet.h>
#include <OgreBillboard.h>
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

	helpers::createEntity(mSM, botoncico, "botoncicoAvion", "Barrel.mesh", mNode, "Avion/Botoncico")->pitch(Ogre::Degree(90));
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


	/*Esto es el código del profe Ana*/
	//planeLight->setDiffuseColour(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
	//planeLight->setDirection(Ogre::Vector3(1, -1, 0));
	//planeLight->setSpotlightInnerAngle(Ogre::Degree(5.0f));
	//planeLight->setSpotlightOuterAngle(Ogre::Degree(45.0f));
	//planeLight->setSpotlightFalloff(0.0f);

	planeLight->setCastShadows(true);
	auto lightNode = mNode->createChildSceneNode();
	lightNode->attachObject(planeLight);
	lightNode->translate({ 0,-40,0 });

	auto ent = mSM->createEntity(Ogre::SceneManager::PrefabType::PT_PLANE);
	auto set = mSM->createBillboardSet(1);
	set->setBillboardOrigin(Ogre::BillboardOrigin::BBO_CENTER_RIGHT);
	set->setMaterialName("Avion/Alas");
	auto billboard = set->createBillboard(Ogre::Vector3(0,0,0));
	//set->setBillboardOrigin(BBO_CENTER);
	billboard->setDimensions(250, 100);
	
	cartel = mNode->createChildSceneNode();
	cartel->attachObject(set);
	cartel->translate({ -100, 0, 0});

	//creamos el sistema de particulas
	smoke = mSM->createParticleSystem("psSmoke", "IG2App/Explosion");
	smoke->setMaterialName("IG2App/Smoke");
	smoke->setEmitting(false);
	mNode->attachObject(smoke);

	mSM->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
}


bool Avion::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_r)
	{
		spin = false;
		
		//hacemos que el avion desaparezca
		mCuerpoNode->setVisible(false);
		malaINode->setVisible(false);
		malaDNode->setVisible(false);
		botoncico->setVisible(false);
		pilotoNode->setVisible(false);
		heliceNodeL->setVisible(false);
		heliceNodeR->setVisible(false);
		cartel->setVisible(false);
		
		planeLight->setVisible(false);

		//hacemos que aparezca el humo
		smoke->setEmitting(true);
	}
	return true;
}

void Avion::frameRendered(const Ogre::FrameEvent& evt)
{
	left->girarAspas(evt.timeSinceLastEvent);
	right->girarAspas(evt.timeSinceLastEvent);
	float delta = evt.timeSinceLastEvent;

	printf("Delta: %f \n", delta);
	
	constexpr float x = 200;
	constexpr float z = 200;
	if (spin)
	{
		mNode->translate({ x,-200,z }, Ogre::Node::TS_LOCAL);
		mNode->yaw(Ogre::Degree(30.0 * delta));
		mNode->translate({ -x,200,-z }, Ogre::Node::TS_LOCAL);
	}

}
