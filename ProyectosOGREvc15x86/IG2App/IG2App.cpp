#include "IG2App.h"

#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>

using namespace Ogre;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt)
{
  if (evt.keysym.sym == SDLK_ESCAPE)
  {
    getRoot()->queueEndRendering();
  }
  else if (evt.keysym.sym == SDLK_g)
  {
	  mParent->roll(Ogre::Degree(18));

	  mNeedles[0]->roll(Ogre::Degree(180));
	  mNeedles[1]->roll(Ogre::Degree(90));
	  mNeedles[2]->roll(Ogre::Degree(33.75));
	  
  }
  else if (evt.keysym.sym == SDLK_h)
  {
	  mParent->roll(Ogre::Degree(18));

  }
  //else if (evt.keysym.sym == SDLK_???)
  
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
 
  mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
  //mLightNode = mCamNode->createChildSceneNode("nLuz");
  mLightNode->attachObject(luz);

  mLightNode->setDirection(Ogre::Vector3(-1, 0, 0));  //vec3.normalise();
  //mLightNode->setPosition(0, 0, 1000);
 
  //------------------------------------------------------------------------

  // finally something to render

  //Ogre::Entity* ent = mSM->createEntity("DamagedHelmet.mesh");
  //Ogre::Entity* ent = mSM->createEntity("Sword.mesh");
  //Ogre::Entity* ent = mSM->createEntity("facial.mesh");
  /*Ogre::Entity* ent = mSM->createEntity("RomanBathLower.mesh");
  Ogre::Entity* upper = mSM->createEntity("RomanBathUpper.mesh");
  Ogre::Entity* sinbad = mSM->createEntity("Sinbad.mesh");

  mLower = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
  mLower->attachObject(ent);
  mUpper = mSM->getRootSceneNode()->createChildSceneNode("upper");
  mUpper->attachObject(upper);
  mSinbad = mSM->getRootSceneNode()->createChildSceneNode("sinbad");
  mSinbad->attachObject(sinbad);*/

  //mSinbadNode->setPosition(400, 100, -300);
  /*mLower->setScale(1,1,1);
  mUpper->setScale(1,1,1);
  mSinbad->setScale(20, 20, 20);*/

  //mSinbad->setPosition(0, 20,0);
  //mSinbadNode->yaw(Ogre::Degree(-45));
  //mSinbadNode->showBoundingBox(true);
  //mSinbadNode->setVisible(false);

  auto createEntity = [&] (Ogre::SceneNode* &node, std::string id, std::string mesh, Vector3 scale = Vector3(1), Ogre::SceneNode* parent = nullptr)
  {
	  Ogre::Entity* ent = mSM->createEntity(mesh);
	  node = (!parent) ? mSM->getRootSceneNode()->createChildSceneNode(id) : parent->createChildSceneNode(id);
	  node->attachObject(ent);
	  node->setScale(scale);
  };

 /* createEntity(mLower, "lower", "RomanBathLower.mesh");
  createEntity(mUpper, "upper", "RomanBathUpper.mesh");
  createEntity(mSinbad, "sinbad", "Sinbad.mesh", Vector3(20));*/
  //mSinbad->setPosition(0, 20,0);
  
  const float inc = 360 / 12;
  const int rad = 1000;
  mParent = mSM->getRootSceneNode()->createChildSceneNode();
  for (int i = 0; i < 12; i++)
  {
	  float radians = Ogre::Math::DegreesToRadians(i * inc);
	  createEntity(mHours[i], "sphere" + std::to_string(i), "sphere.mesh", Vector3(1), mParent); 
	  mHours[i]->setPosition(Ogre::Math::Cos(radians) * rad, Ogre::Math::Sin(radians) * rad, 0);
  }
  /*for (int i = 0; i < 6; i++)
  {
	  mSM->getSceneNode("sphere" + std::to_string(2*i))->setScale(Vector3(0.5));
  }*/
  for (int i = 0; i < 3; i++)
  {
	  createEntity(mNeedles[i], "needle" + std::to_string(i), "column.mesh", Vector3(2.5 / (i + 1), 2.5 / (i + 1), 1));

	  
	  mNeedles[i]->roll(Ogre::Degree(-90 * i));
  }

  //------------------------------------------------------------------------

  mCamMgr = new OgreBites::CameraMan(mCamNode);
  addInputListener(mCamMgr);
  mCamMgr->setStyle(OgreBites::CS_ORBIT);  
  
  //mCamMgr->setTarget(mSinbadNode);  
  //mCamMgr->setYawPitchDist(Radian(0), Degree(30), 100);

  //------------------------------------------------------------------------

}

