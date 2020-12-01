#include "IG2App.h"

#include <OgreEntity.h>
#include <OgreAnimation.h>
#include <OgreKeyFrame.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <iostream>
#include "Plano.h"
#include "Simbad.h"
#include "Boya.h"


using namespace Ogre;
bool IG2App::hayArray = false;

Nodo* helpers::createEntity(Ogre::SceneManager* sm, Nodo*& Node, std::string id, std::string mesh, Nodo* parent, std::string material)
{
	Ogre::Entity* ent = sm->createEntity(mesh);
	if (material != "")
	{
		ent->setMaterialName(material);
	}
	Node = (!parent) ? sm->getRootSceneNode()->createChildSceneNode(id) : parent->createChildSceneNode(id);
	Node->attachObject(ent);
	return Node;
}

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt)
{
  if (evt.keysym.sym == SDLK_ESCAPE)
  {
    getRoot()->queueEndRendering();
  }
  else if(evt.keysym.sym == SDLK_r)
	  EntidadIG::sendEvent(EntidadIG::MessageType::emptyRiver, nullptr);
  


  return true;
}

void IG2App::shutdown()
{
  mShaderGenerator->removeSceneManager(mSM);  
  mSM->removeRenderQueueListener(mOverlaySystem);  
					
  mRoot->destroySceneManager(mSM);  

  delete mTrayMgr;  mTrayMgr = nullptr;
  delete mCamMgr; mCamMgr = nullptr;
  // do not forget to call the base 
  IG2ApplicationContext::shutdown();
}

void IG2App::setup(void)
{
  // do not forget to call the base first
  IG2ApplicationContext::setup();

  mSM = mRoot->createSceneManager();  

  // register our scene with the RTSS
  mShaderGenerator->addSceneManager(mSM);

  mSM->addRenderQueueListener(mOverlaySystem);

  mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", mWindow.render);  
  mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
  addInputListener(mTrayMgr);

  addInputListener(this);   
  setupScene();
}

void IG2App::setupScene(void)
{
  // create the camera
  Camera* cam = mSM->createCamera("Cam");
  cam->setNearClipDistance(1); 
  cam->setFarClipDistance(1000000000);
  cam->setAutoAspectRatio(true);
  //cam->setPolygonMode(Ogre::PM_WIREFRAME); 

  mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
  mCamNode->attachObject(cam);

  mCamNode->setPosition(0, 0, 1000);
  mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
  //mCamNode->setDirection(Ogre::Vector3(0, 0, -1));  


  // and tell it to render into the main window
  Viewport* vp = getRenderWindow()->addViewport(cam);
  vp->setBackgroundColour(Ogre::ColourValue(0.7, 0.8, 0.9));

  //------------------------------------------------------------------------

  

  // without light we would just get a black screen 

  Light* luz = mSM->createLight("Luz");
  luz->setType(Ogre::Light::LT_DIRECTIONAL);
  luz->setDiffuseColour(0.75, 0.75, 0.75);
  luz->setDirection({ 0,-1, -1 });
  

  mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
  //mLightNode = mCamNode->createChildSceneNode("nLuz");
  mLightNode->attachObject(luz);

  //mLightNode->setPosition(0, 0, 1000);

  //------------------------------------------------------------------------
 

  constexpr int scene = 5;
  int option = 0;
  switch (scene)
  {
  case 5:
		startScene5(option);
		break;
  default:
	  break;
  }

	auto p = Ogre::MeshManager::getSingleton().createPlane("plane80",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Plane(Vector3::UNIT_Y, 0),
		100, 100, 80, 80, true, 1, 1.0, 1.0, Vector3::UNIT_Z);
	
  //------------------------------------------------------------------------

  mCamMgr = new OgreBites::CameraMan(mCamNode);
  addInputListener(mCamMgr);
  mCamMgr->setStyle(OgreBites::CS_ORBIT);  
  
  //mCamMgr->setTarget(mSinbadNode);  
  //mCamMgr->setYawPitchDist(Radian(0), Degree(30), 100);
  
  auto node = mSM->getRootSceneNode()->createChildSceneNode();
  auto whateva = mSM->createEntity(p);
  
  //mSM->setSkyPlane(true, Plane(Vector3::UNIT_Z, -20), "IG2/space", 1, 1, true, 1.0, 10, 10);
  
  mSM->setSkyPlane(true, Plane(Vector3::UNIT_Z, -200), "IG2/space", 1, 1, true, 0.0, 10, 10);


  //------------------------------------------------------------------------
}
void IG2App::startScene5(int option)
{
	Nodo* parent = mSM->getRootSceneNode()->createChildSceneNode();
	base = new Rio(parent, 1200, 800, "IG2/Reflejo");
	this->mCamNode->attachObject(base->getCam());
	base->setReflejo((Ogre::Camera*)this->mCamNode->getAttachedObject("Cam"));

	Plano* baseMolino = new Plano(parent, 500, 500, "Plano/Molino");
	baseMolino->getNode()->translate({ 350,2,-150 });

	Avion* avion = new Avion(parent);
	avion->getNode()->scale(Vector3(0.3));
	avion->getNode()->translate({ 350 - 100, 200, -130 - 100 });
	addInputListener(avion);
	addInputListener(avion->left);
	addInputListener(avion->right);

	Molino* molino = new Molino(mSM, 12, parent);
	molino->getNode()->translate({ 350,142,-130 });
	addInputListener(molino);
	addInputListener(molino->aspas);

	Nodo* carita;
	helpers::createEntity(mSM, carita, "billboard", "sphere.mesh", parent, "Esfera/Cabeza");
	carita->translate(Vector3(400, 27, -100));
	carita->scale(Vector3(0.25));

	Simbad* simbad = new Simbad(parent, option == 0);
	simbad->getNode()->scale({ 20,20,20 });
	simbad->getNode()->translate({ -500,102,300 });
	addInputListener(simbad);
	
	if (option == 0)
	{
		Boya* boya = new Boya(parent);
		addInputListener(boya);
	}
}

