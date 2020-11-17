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
  /// Escena de la primera práctica, que puede mostrar, dependiendo de la opcion:
  /// </summary>
  /// <param name="option"> Un casco (option = 0), una espada (option = 1) o una cabeza (option = 2)</param>
  virtual void startScene0(int option = 0); 
  /// <summary>
  /// Ejercicio en el que se situaba una entidad dentro de una sauna. La entidad puede ser:
  /// </summary>
  /// <param name="option"> un dragon (option = 0) o Sinbad (option = 1)</param>
  virtual void startScene1(int option = 0);
  /// <summary>
  /// Escena en la que se muestra un reloj formado por esferas y tres agujas, que giran.
  /// Es parte de la practica 1.2 (ejercicios 12-13), pero esta fuera de la escena 4
  /// porque se empezo a implementar como parte de un ejercicio anterior.
  /// </summary>
  /// <param name="op"> No se utiliza, solo se muestra esta escena</param>
  virtual void startScene2(int option = 0); 
  /// <summary>
  /// Practica 1.1 
  /// </summary>
  /// <param name="option">
  /// Ejercicio 1 (option = 1), 
  /// ejercicio 2 (option = 2), 
  /// ejercicios 3-4 (option = 3),
  /// ejercicios 5-8 (option = 4)</param>
  virtual void startScene3(int option = 0); 
  /// <summary>
  /// Practica 1.2
  /// </summary>
  /// <param name="option">
  /// Ejercicios 9-11 (option = 0),
  /// ejercicios 14-15 (option = 1),
  /// ejercicios 16-17 (option =2)
  /// </param>
  virtual void startScene4(int option = 0);
  /// <summary>
  /// Prácticas 1.3 (23), 1.4 (26-31) y 1.5 (32-38)
  /// </summary>
  /// <param name="option">No se utiliza este parametro, porque todo se ha ido construyendo sobre la misma escena</param>
  virtual void startScene5(int option = 0);

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

  
  AspasMolino* aspasMolino = nullptr;
  Molino* molino = nullptr;
  
  Nodo* planets = nullptr;
  Nodo* tierraNode = nullptr;
  Nodo* lunaNode = nullptr;
  Nodo* solNode= nullptr;
  Avion* avion = nullptr;

  //clases que no hemos sacado a otros archivos porque tampoco estorban demasiado

  class Plano : public EntidadIG
  {
  public:
      static int id;
      Plano(Nodo* parent, float width, float height, std::string string = "", std::string entName = "");
      ~Plano() {};
      virtual void receiveEvent(MessageType msj, EntidadIG* entidad);
  private:
      Ogre::Entity* mEnt = nullptr;
  };


  class Simbad : public EntidadIG
  {
  public:
      Simbad(Nodo* parent, bool listener = false);
      ~Simbad() {};
      void inline setListener() { isInputListener = true; }
  private:
      virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
      virtual void frameRendered(const Ogre::FrameEvent& evt) override;

      Ogre::Entity* ent;
      Ogre::Entity* sword;
      bool walking = true;
      bool dancing = false;
      bool right = true;
      Ogre::AnimationState* animationState;

      bool isInputListener = false;
  };

  class Boya : public EntidadIG
  {
  public:
      Boya(Nodo* parent);
      ~Boya() {};
  private:
      virtual void frameRendered(const Ogre::FrameEvent& evt) override;

      Ogre::Entity* ent;
      Ogre::AnimationState* animationState;
  };


  friend class Molino;
};


#endif
