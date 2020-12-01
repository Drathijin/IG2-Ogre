#include "Plano.h"
#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include <OgreMovablePlane.h>
#include <OgreTextureManager.h>
#include <OgreTexture.h>
#include <OgreRenderTexture.h>
#include <OgreHardwarePixelBuffer.h>
#include <OgreSharedPtr.h>
#include <OgreTechnique.h>

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

Rio::Rio(Nodo* parent, float width, float height, std::string matName): EntidadIG(parent->createChildSceneNode())
{
	

	mEnt = mSM->createEntity(Ogre::SceneManager::PrefabType::PT_PLANE);

	if (matName != "")
		mEnt->setMaterialName(matName);
	mNode->attachObject(mEnt);

	mNode->pitch(Ogre::Radian(-Ogre::Math::HALF_PI));
	mNode->scale(width / 120, height / 120, 1);



	camRef = mSM->createCamera("RefCam");
	camRef->setNearClipDistance(1);
	camRef->setFarClipDistance(1000000000);
	camRef->setAutoAspectRatio(true);
	mpRef = new Ogre::MovablePlane(mNode->getLocalAxes().GetColumn(2), 1000);
	mNode->attachObject(mpRef);
	camRef->enableReflection(mpRef);
	camRef->enableCustomNearClipPlane(mpRef);

	// LBO_ADD / LBO_ALPHA_BLEND / LBO_REPLACE
}

void Rio::receiveEvent(MessageType msj, EntidadIG* entidad)
{
	if (msj == EntidadIG::MessageType::emptyRiver)
	{
		mEnt->setMaterialName("Plano/SinAgua");
	}
}

void Rio::setReflejo(Ogre::Camera* cam)
{
	Ogre::TexturePtr rttRef = Ogre::TextureManager::getSingleton().createManual(
		"rttReflejo", // name ejemplo -> (*)
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Ogre::TEX_TYPE_2D,
		(Ogre::Real)cam->getViewport()->getActualWidth(), // widht ejemplo
		(Ogre::Real)cam->getViewport()->getActualHeight(), // height ejemplo
		0, Ogre::PF_R8G8B8, Ogre::TU_RENDERTARGET);
	Ogre::RenderTexture* renderTexture =rttRef->getBuffer()->getRenderTarget();
	Ogre::Viewport* vpt = renderTexture->addViewport(camRef); // ocupando toda
	vpt->setClearEveryFrame(true); // la textura
	vpt->setBackgroundColour(Ogre::ColourValue::White);

	Ogre::TextureUnitState* tu = mEnt->getSubEntity(0)->getMaterial()->
		getTechnique(0)->getPass(0)->
		createTextureUnitState("rttReflejo"); // <- (*)
	tu->setColourOperation(Ogre::LBO_MODULATE); // black/white background?

	tu-> setProjectiveTexturing(true, camRef);
}