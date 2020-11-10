#ifndef __IG2App_H__
#define __IG2App_H__

#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include "EntidadIG.h";

using Nodo = Ogre::SceneNode;
namespace helpers {
    Nodo* createEntity(Ogre::SceneManager* sm, Nodo*& Node, std::string id, std::string mesh, Nodo* parent = nullptr, std::string material = "");
}



class IG2App : public  OgreBites::IG2ApplicationContext, OgreBites::InputListener 
{

public:
  explicit IG2App() : IG2ApplicationContext("IG2App") { };  // new -> setup()  
  virtual ~IG2App() { };   // delete -> shutdown()  
  static bool hayArray;
  static void setArray(bool b) { hayArray = b; };
protected:
  virtual void setup();
  virtual void shutdown();
  virtual void setupScene();
  Nodo* createEntity(Nodo*& Node, std::string id, std::string mesh, Nodo* parent = nullptr, std::string material = "")
  {
      return helpers::createEntity(mSM, Node, id, mesh, parent, material);
  }
  virtual void startScene0(int option = 0); //Casco, espada y cara
  virtual void startScene1(int option = 0); //Dragón o Sinbad
  virtual void startScene2(int option = 0); //Reloj AKA agujitas

  virtual void startScene3(int option = 0);   //Molino
  virtual void startScene4(int option = 0);   //Molino entero

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
  class AspasMolino : public EntidadIG {
  public:
      AspasMolino(int n, bool flag, Nodo* parent, float speed=1);
      ~AspasMolino() { if (arrayAspas) delete[]arrayAspas;};
      int numAspas;
      IG2App::Aspa** arrayAspas = nullptr;
      static int count;
      Nodo* botoncicoNode = nullptr;
      void girarAspas(float delta=1);
  private:
      bool savedInArray = false;
      float rSpeed=1;
      virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
  };
  class Aspa : public EntidadIG {
  public:
      Aspa(Ogre::SceneManager* sm, Nodo* parent = nullptr);
      Nodo* tableroNode = nullptr;
      Nodo* cilindroNode = nullptr;
      static int id;
      static void addID() { id++; };
  };

  friend class Molino;
  class Molino : public EntidadIG {
  public:
      Molino(Ogre::SceneManager* sm, int n, Nodo* parent);
      Nodo* esferaNode = nullptr;
      Nodo* cilindroNode = nullptr;
      AspasMolino* aspas = nullptr;
      Nodo* aspasParent = nullptr;

  private:

      bool spin = true;


      virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
      virtual void frameRendered(const Ogre::FrameEvent& evt) 
      {
          if (spin)
              aspas->girarAspas(evt.timeSinceLastEvent);
      }
  };
  AspasMolino* aspasMolino = nullptr;
  Molino* molino = nullptr;
  
  Nodo* planets = nullptr;
  Nodo* tierraNode = nullptr;
  Nodo* lunaNode = nullptr;
  Nodo* solNode= nullptr;

  class Avion : public EntidadIG
  {

  public:
      Avion(Nodo* parent);
      AspasMolino* left;
      AspasMolino* right;
  private:
      bool spin = true;


      Nodo* mCuerpoNode = nullptr;
      Nodo* malaINode = nullptr;
      Nodo* malaDNode = nullptr;
      Nodo* botoncico = nullptr;
      Nodo* pilotoNode = nullptr;
      Nodo* heliceNodeL = nullptr;
      Nodo* heliceNodeR = nullptr;  
      Ogre::Light* planeLight = nullptr;

      virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

      virtual void frameRendered(const Ogre::FrameEvent& evt) 
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
  };
  Avion* avion = nullptr;

  class Plano : public EntidadIG
  {
  public:
      static int id;
      Plano(Nodo* parent, float width, float height, std::string string="", std::string entName= "");
      ~Plano() {};
      virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
      virtual void receiveEvent(MessageType msj, EntidadIG* entidad);
  private:
      Ogre::Entity* mEnt = nullptr;
  };

  class Simbad : public EntidadIG
  {
  public:
      Simbad(Nodo* parent);
      ~Simbad() {};
      
  };
};


#endif
