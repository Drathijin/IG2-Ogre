#include "Plano.h"
#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>

int Plano::id = 0;
Plano::Plano(Nodo* parent, float width, float height, std::string matName, std::string entName) :EntidadIG(parent->createChildSceneNode())
{
	mEnt = (entName == "") ? mSM->createEntity(Ogre::SceneManager::PrefabType::PT_PLANE) : mSM->createEntity(entName, Ogre::SceneManager::PrefabType::PT_PLANE);

	if (matName != "")
		mEnt->setMaterialName(matName);
	mNode->attachObject(mEnt);
	
	mNode->pitch(Ogre::Radian(-Ogre::Math::HALF_PI));
	mNode->scale(width/120, height/120, 1);
	Plano::id++;
}
void Plano::receiveEvent(MessageType msj, EntidadIG* entidad)
{
	if (msj == EntidadIG::MessageType::emptyRiver && mEnt->getName() == "River")
	{
		mEnt->setMaterialName("Plano/SinAgua");
	}
}