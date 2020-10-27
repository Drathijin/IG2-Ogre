#ifndef __IG2App_H__
#define __IG2App_H__

#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>

using Nodo = Ogre::SceneNode;
namespace helpers {
    Nodo* createEntity(Ogre::SceneManager* sm, Nodo*& Node, std::string id, std::string mesh, Nodo* parent = nullptr);
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
  Nodo* createEntity(Nodo*& Node, std::string id, std::string mesh, Nodo* parent = nullptr)
  {
      return helpers::createEntity(mSM, Node, id, mesh, parent);
  }
  virtual void startScene0(int option = 0); //Casco, espada y cara
  virtual void startScene1(int option = 0); //Dragón o Sinbad
  virtual void startScene2(int option = 0); //Reloj AKA agujitas

  virtual void startScene3(int option = 0);   //Molino
  virtual void startScene4(int option=0);   //Molino entero

  virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener
  bool flag = false;
  Ogre::SceneManager* mSM = nullptr;
  OgreBites::TrayManager* mTrayMgr = nullptr;    
  Nodo* mLightNode = nullptr;
  Nodo* mCamNode = nullptr;
  Nodo* mLower = nullptr;
  Nodo* mSinbad = nullptr;
  Nodo* mUpper = nullptr;
  Nodo* mSpheresParent = nullptr;
  Nodo* mTotalParent = nullptr;
  OgreBites::CameraMan* mCamMgr = nullptr;
  Nodo* mHours[12];
  Nodo* mNeedles[3];
    


  Nodo* aspaNode = nullptr;
  Nodo* tableroNode = nullptr;
  Nodo* cilindroNode = nullptr;
  
  Nodo* aspas = nullptr;
  const int numAspas = 12; 
  std::vector<Nodo*> aspaContainer;
  std::vector<Nodo*> tableroNodes;
  std::vector<Nodo*> cilindroNodes;

  class Aspa;
  class AspasMolino  {
  public:
      AspasMolino(Ogre::SceneManager* sm, int n, bool flag, Nodo* parent=nullptr);
      int numAspas;
      Nodo* aspasNode=nullptr;
      Ogre::SceneManager* mSM;
      IG2App::Aspa** arrayAspas = nullptr;
       static int count;
       Nodo* botoncicoNode = nullptr;
  };
  class Aspa {
  public:
      Aspa(Ogre::SceneManager* sm, Nodo* parent = nullptr);
      Ogre::SceneManager* mSM = nullptr;
      Nodo* aspaNode = nullptr;
      Nodo* tableroNode = nullptr;
      Nodo* cilindroNode = nullptr;
      static int id;
      static void addID() { id++; };
  };

  friend class Molino;
  class Molino : OgreBites::InputListener {
  public:
      Molino(Ogre::SceneManager* sm, int n, Nodo* parent);
      Ogre::SceneManager* mSM = nullptr;
      Nodo* mNode = nullptr;
      Nodo* esferaNode = nullptr;
      Nodo* cilindroNode = nullptr;
      AspasMolino* aspas = nullptr;
      Nodo* aspasParent = nullptr;
  };
  AspasMolino* aspasMolino = nullptr;
  bool hayArray = false;
  Molino* molino = nullptr;
  
  Nodo* planets = nullptr;
  Nodo* tierraNode = nullptr;
  Nodo* lunaNode = nullptr;
  Nodo* solNode= nullptr;

  class Avion
  {

  public:
      Avion(Ogre::SceneManager* sm, Nodo* parent, IG2App* app);
      void rotateHelices(float dg);
  private:
      Ogre::SceneManager* mSM = nullptr;
      Nodo* mNode = nullptr;
      Nodo* mCuerpoNode = nullptr;
      Nodo* malaINode = nullptr;
      Nodo* malaDNode = nullptr;
      Nodo* botoncico = nullptr;
      Nodo* pilotoNode = nullptr;
      Nodo* heliceNodeL = nullptr;
      Nodo* heliceNodeR = nullptr;
  };
  Avion* avion = nullptr;
};


#endif
