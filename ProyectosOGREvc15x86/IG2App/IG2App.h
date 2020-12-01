#ifndef __IG2App_H__
#define __IG2App_H__

#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include "EntidadIG.h";
#include "Aspas.h"
#include "Avion.h"
#include "Plano.h"
#include "Molino.h"

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

  /// <summary>
  /// Prácticas 1.3 (23), 1.4 (26-31) y 1.5 (32-38)
  /// </summary>
  /// <param name="option">No se utiliza este parametro, porque todo se ha ido construyendo sobre la misma escena</param>
  virtual void startScene5(int option = 0);

  virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener
  bool flag = false;
  Ogre::SceneManager* mSM = nullptr;
  OgreBites::TrayManager* mTrayMgr = nullptr;    
  OgreBites::CameraMan* mCamMgr = nullptr;

  Nodo* mLightNode = nullptr;
  Nodo* mCamNode = nullptr;
  Rio* base;

//  Avion* avion = nullptr;

  //clases que no hemos sacado a otros archivos porque tampoco estorban demasiado




  



  friend class Molino;
};


#endif
