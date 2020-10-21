#ifndef __IG2App_H__
#define __IG2App_H__

#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>

namespace helpers {
    Ogre::SceneNode* createEntity(Ogre::SceneManager* sm, Ogre::SceneNode*& node, std::string id, std::string mesh, Ogre::SceneNode* parent = nullptr);
}



class IG2App : public  OgreBites::IG2ApplicationContext, OgreBites::InputListener 
{
public:
  explicit IG2App() : IG2ApplicationContext("IG2App") { };  // new -> setup()  
  virtual ~IG2App() { };   // delete -> shutdown()  
 
protected:
  virtual void setup();
  virtual void shutdown();
  virtual void setupScene();
  Ogre::SceneNode* createEntity(Ogre::SceneNode*& node, std::string id, std::string mesh, Ogre::SceneNode* parent = nullptr)
  {
      return helpers::createEntity(mSM, node, id, mesh, parent);
  }
  virtual void startScene0(int option = 0); //Casco, espada y cara
  virtual void startScene1(int option = 0); //Dragón o Sinbad
  virtual void startScene2(int option = 0); //Reloj AKA agujitas

  virtual void startScene3(int option = 0);   //Molino
  virtual void startScene4(int option=0);   //Molino entero

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
  
  Ogre::SceneNode* aspas = nullptr;
  const int numAspas = 12; 
  std::vector<Ogre::SceneNode*> aspaContainer;
  std::vector<Ogre::SceneNode*> tableroNodes;
  std::vector<Ogre::SceneNode*> cilindroNodes;

  class Aspa;
  class AspasMolino  {
  public:
      AspasMolino(Ogre::SceneManager* sm, int n, bool flag, Ogre::SceneNode* parent=nullptr);
      int numAspas;
      Ogre::SceneNode* aspasNode=nullptr;
      Ogre::SceneManager* mSM;
      IG2App::Aspa** arrayAspas = nullptr;

  };
  class Aspa {
  public:
      Aspa(Ogre::SceneManager* sm, Ogre::SceneNode* parent = nullptr);
      Ogre::SceneManager* mSM = nullptr;
      Ogre::SceneNode* aspaNode = nullptr;
      Ogre::SceneNode* tableroNode = nullptr;
      Ogre::SceneNode* cilindroNode = nullptr;
      static int id;
      static void addID() { id++; };
  };

  friend class Molino;
  class Molino : OgreBites::InputListener {
  public:
      Molino(Ogre::SceneManager* sm, int n);
      Ogre::SceneManager* mSM = nullptr;
      Ogre::SceneNode* mNode = nullptr;
      Ogre::SceneNode* esferaNode = nullptr;
      Ogre::SceneNode* cilindroNode = nullptr;
      Ogre::SceneNode* botoncicoNode = nullptr;
      AspasMolino* aspas = nullptr;
      Ogre::SceneNode* aspasParent = nullptr;
  };
  AspasMolino* aspasMolino = nullptr;
  bool hayArray = false;
  Molino* molino = nullptr;
  
  Ogre::SceneNode* planets = nullptr;
  Ogre::SceneNode* tierraNode = nullptr;
  Ogre::SceneNode* lunaNode = nullptr;
  Ogre::SceneNode* solNode= nullptr;
};


#endif
