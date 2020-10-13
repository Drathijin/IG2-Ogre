#ifndef __IG2App_H__
#define __IG2App_H__

#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>


class IG2App : public  OgreBites::IG2ApplicationContext, OgreBites::InputListener 
{
public:
  explicit IG2App() : IG2ApplicationContext("IG2App") { };  // new -> setup()  
  virtual ~IG2App() { };   // delete -> shutdown()  
 
protected:
  virtual void setup();
  virtual void shutdown();
  virtual void setupScene();
  virtual void createEntity(Ogre::SceneNode*& node, std::string id, std::string mesh, Ogre::Vector3 scale = Ogre::Vector3(1), Ogre::SceneNode* parent = nullptr);

  virtual void startScene0(int option = 0); //Casco, espada y cara
  virtual void startScene1(int option = 0); //Dragón o Sinbad
  virtual void startScene2(int option = 0); //Reloj AKA agujitas

  virtual void startScene3(int option=0);   //Molino

  virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener
      
  Ogre::SceneManager* mSM = nullptr;
  OgreBites::TrayManager* mTrayMgr = nullptr;    
  Ogre::SceneNode* mLightNode = nullptr;
  Ogre::SceneNode* mCamNode = nullptr;
  Ogre::SceneNode* mLower = nullptr;
  Ogre::SceneNode* mSinbad = nullptr;
  Ogre::SceneNode* mUpper = nullptr;
  Ogre::SceneNode* mSpheresParent = nullptr;
  Ogre::SceneNode* mTotalParent = nullptr;
  OgreBites::CameraMan* mCamMgr = nullptr;
  Ogre::SceneNode* mHours[12];
  Ogre::SceneNode* mNeedles[3];
    
  Ogre::SceneNode* aspaNode = nullptr;
  Ogre::SceneNode* tableroNode = nullptr;
  Ogre::SceneNode* cilindroNode = nullptr;
  int apano = 0;
};

#endif
