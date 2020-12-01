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
#include <OgreTextureUnitState.h>


#include <OgreEntity.h>
#include <OgreAnimation.h>
#include <OgreKeyFrame.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <iostream>
using namespace Ogre;

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
	mpRef = new Ogre::MovablePlane(Vector3::UNIT_Y, 0);
	mNode->attachObject(mpRef);

	auto p = Ogre::MeshManager::getSingleton().createPlane("plane200",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		*mpRef,
		width*2, height*2, 200, 200, true, 1, 1.0, 1.0, Vector3::UNIT_Z);

	mEnt = mSM->createEntity(p);

	if (matName != "")
		mEnt->setMaterialName(matName);
	mNode->attachObject(mEnt);

	//mNode->pitch(Ogre::Radian(-Ogre::Math::HALF_PI));

	//mNode->scale(width / 120, height / 120, 1);




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
	Ogre::SceneNode* quieroMorir = cam->getParentSceneNode()->createChildSceneNode();
	camRef = mSM->createCamera("RefCam");
	camRef->setNearClipDistance(1);
	camRef->setFarClipDistance(1000000000);
	camRef->setAutoAspectRatio(true);

	quieroMorir->setPosition(0, -500, 1000);
	quieroMorir->lookAt({ 0,0,0 }, Ogre::Node::TS_WORLD);

	quieroMorir->attachObject(camRef);
	camRef->enableReflection(mpRef);
	camRef->enableCustomNearClipPlane(mpRef);

	camRef->setAspectRatio(
		(Ogre::Real)cam->getViewport()->getActualWidth()/ // widht ejemplo
		(Ogre::Real)cam->getViewport()->getActualHeight());

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
		createTextureUnitState("rttReflejo"); //<- (*) 
	tu->setTextureAddressingMode(Ogre::TextureUnitState::TAM_CLAMP); // black/white background?

	tu-> setProjectiveTexturing(true, camRef);

	renderTexture->addListener(dynamic_cast<Ogre::RenderTargetListener*>(this));
}

void Rio::preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt)
{
	mEnt->setVisible(false);
}

void Rio::postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt)
{
	mEnt->setVisible(true);
}
