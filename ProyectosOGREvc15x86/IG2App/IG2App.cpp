#include "IG2App.h"

#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <iostream>

using namespace Ogre;

Ogre::SceneNode* helpers::createEntity(Ogre::SceneManager* sm, Ogre::SceneNode*& node, std::string id, std::string mesh, Ogre::SceneNode* parent)
{
	Ogre::Entity* ent = sm->createEntity(mesh);
	node = (!parent) ? sm->getRootSceneNode()->createChildSceneNode(id) : parent->createChildSceneNode(id);
	node->attachObject(ent);
	return node;
}

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt)
{
  if (evt.keysym.sym == SDLK_ESCAPE)
  {
    getRoot()->queueEndRendering();
  }
  else if (evt.keysym.sym == SDLK_g)
  {
	  //mTotalParent->roll(Ogre::Degree(-1));
	  if (aspas)
	  {
		  aspas->roll(Ogre::Degree(1));
		  for (int i = 0; i < numAspas; i++)
			  cilindroNodes[i]->roll(Ogre::Degree(-1));
	  }
	  else if(molino)
	  {
		  molino->aspas->aspasNode->roll(Ogre::Degree(1));
		  for (int i = 0; i < molino->aspas->numAspas; i++)
			mSM->getSceneNode("adorno_"+std::to_string(i))->roll(Ogre::Degree(-1));
		  molino->botoncicoNode->yaw(Ogre::Degree(1));
	  }
	  else if (aspasMolino && !hayArray)
	  {
		  aspasMolino->aspasNode->roll(Ogre::Degree(1));
		  for (int i = 0; i < numAspas; i++)
			mSM->getSceneNode("adorno_"+std::to_string(i))->roll(Ogre::Degree(-1));
	  }
	  else if(aspasMolino && hayArray){
		  aspasMolino->aspasNode->roll(Ogre::Degree(1));
		  for (int i = 0; i < numAspas; i++)
			  aspasMolino->arrayAspas[i]->cilindroNode->roll(Ogre::Degree(-1));
	  }
  }
  else if (evt.keysym.sym == SDLK_h)
  {
	  if(molino)
	  {
		  molino->aspasParent->yaw(Ogre::Degree(10), Ogre::Node::TS_PARENT);
	  }
	  else if (mSpheresParent)
	  {
		  mNeedles[2]->roll(Ogre::Degree(-5));
	  }
  }
  else if (evt.keysym.sym == SDLK_p)
  {
	  if(aspaNode)
		  aspaNode->roll(Ogre::Degree(18));
  }
  else if (evt.keysym.sym == SDLK_j)
  {
	  if (planets)
	  {
		  tierraNode->translate({ 250,0,0 }, Ogre::Node::TS_LOCAL);
		  tierraNode->yaw(Ogre::Degree(-5));
		  tierraNode->translate({ -250,0,0 }, Ogre::Node::TS_LOCAL);

		  lunaNode->translate({ 150,0,0 }, Ogre::Node::TS_LOCAL);
		  lunaNode->yaw(Ogre::Degree(100));
		  lunaNode->translate({ -150,0,0 }, Ogre::Node::TS_LOCAL);
	  }
  }
  else if (evt.keysym.sym == SDLK_c)
  {
	if(molino)
	{
		  molino->botoncicoNode->translate(Vector3(0, 0, -50));
	}
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

  //mLightNode->setPosition(0, 0, 1000);
 
  //------------------------------------------------------------------------
  /*
	La escena 3 es la practica 1.1
		-Opción 0 es un aspa sola
		-Opción 1 son las aspas hechas a mano
		-Opción 2 son las aspas con un nivel de abstración
		-Opción 3 son las aspas en el array Aspas**
  */
  constexpr int scene = 4;
  constexpr int option = 1;
  
  //std::cin >> option;
  switch (scene)
  {
  case 0:
		startScene0(option);
		break;
  case 1:
		startScene1(option);
		break;
  case 2:
		startScene2(option);
		break;
  case 3:
		startScene3(option);
		break;
  case 4:
		startScene4(option);
		break;
  default:
	  break;
  }

 

  //------------------------------------------------------------------------

  mCamMgr = new OgreBites::CameraMan(mCamNode);
  addInputListener(mCamMgr);
  mCamMgr->setStyle(OgreBites::CS_ORBIT);  
  
  //mCamMgr->setTarget(mSinbadNode);  
  //mCamMgr->setYawPitchDist(Radian(0), Degree(30), 100);

  //------------------------------------------------------------------------

}



void IG2App::startScene0(int option) {
	std::string mesh;
	switch (option)
	{
	case 0:
		mesh = "DamagedHelmet.mesh";
		mCamNode->setPosition(0, 0, 100);
		break;

	case 1:
		mesh = "Sword.mesh";
		mCamNode->setPosition(0, 0, 25);
		mLightNode->setDirection(Ogre::Vector3(-1, 0, 0));  //vec3.normalise();
		break;

	case 2:
		mLightNode->setDirection(Ogre::Vector3(0, 1, 0));  //vec3.normalise();
		mCamNode->setPosition(0, 200, 100);
		mesh = "facial.mesh";
		break;
	default:
		break;
	}
	Ogre::Entity* ent = mSM->createEntity(mesh);
	mSinbad = mSM->getRootSceneNode()->createChildSceneNode("sinbad");
	mSinbad->setPosition(0, 0, 0);
	mSinbad->attachObject(ent);

};
void IG2App::startScene1(int option) {
	createEntity(mLower, "lower", "RomanBathLower.mesh");
	createEntity(mUpper, "upper", "RomanBathUpper.mesh");
	if (option == 0)
	{
		createEntity(mSinbad, "dragon", "dragon.mesh")->scale(Vector3(0.75));
		mSinbad->setPosition(0, 75, 0);
		mSinbad->yaw(Ogre::Degree(180));
	}
	else if (option == 1)
	{

		createEntity(mSinbad, "sinbad", "Sinbad.mesh")->scale(Vector3(20));
		mSinbad->setPosition(0, 20, 0);
	}

};
void IG2App::startScene2(int op) {

	const float inc = 360 / 12;
	const int rad = 1000;

	//creamos un padre para todas las entidades
	mTotalParent = mSM->getRootSceneNode()->createChildSceneNode();
	//creamos un padre para las esferas de las horas, y lo hacemos hijo del padre total
	mSpheresParent = mTotalParent->createChildSceneNode("spheresParent");


	for (int i = 0; i < 12; i++)
	{
		float radians = Ogre::Math::DegreesToRadians(i * inc);
		createEntity(mHours[i], "sphere" + std::to_string(i), "sphere.mesh", mSpheresParent);
		mHours[i]->setPosition(Ogre::Math::Cos(radians) * rad, Ogre::Math::Sin(radians) * rad, 0);
	}
	for (int i = 0; i < 3; i++)
	{
		createEntity(mNeedles[i], "needle" + std::to_string(i), "column.mesh",mTotalParent)->scale(Vector3(2.5 / (i + 1), 2.5 / (i + 1), 1));
		mNeedles[i]->roll(Ogre::Degree(-90 * i));
	}
	mNeedles[2]->roll(Ogre::Degree(-45), Ogre::Node::TS_LOCAL);
	
	mCamNode->setPosition(0, 0, 10000);
}
void IG2App::startScene3(int option)
{
	if (option == 0)
	{
		aspaNode = mSM->getRootSceneNode()->createChildSceneNode();
		createEntity(cilindroNode, "adorno", "column.mesh", aspaNode)->scale(Vector3(4, 1, 4));
		createEntity(tableroNode, "tablero", "cube.mesh", aspaNode)->scale(Vector3(5, 30, 1));

		cilindroNode->setPosition(-110, 1400, 10);
		cilindroNode->roll(Ogre::Degree(-90));
	}
	else if (option == 1)
	{
		float angle = 360 / numAspas;

		aspaContainer.reserve(numAspas);
		tableroNodes.reserve(numAspas);
		cilindroNodes.reserve(numAspas);
		aspas = mSM->getRootSceneNode()->createChildSceneNode("padreDeAspas");
		int scale = 1;
		for (int i = 0; i < numAspas; i++)
		{
			aspaContainer[i] = aspas->createChildSceneNode("aspa_" + std::to_string(i));
			createEntity(tableroNodes[i], "tablero_" +std::to_string(i), "cube.mesh", aspaContainer[i])->scale(Vector3(.1, 1, .1));
			createEntity(cilindroNodes[i], "adorno_"+std::to_string(i), "Barrel.mesh", aspaContainer[i]);
			cilindroNodes[i]->setPosition(0, -100, 10);
			tableroNodes[i]->setPosition(0, -60, 0);
			cilindroNodes[i]->roll(Ogre::Degree(-angle * i));
			aspaContainer[i]->roll(Ogre::Degree(angle * i));
		}
	}
	else if (option == 2)
	{
		hayArray = false;
		aspasMolino = new AspasMolino(mSM, numAspas, hayArray);
	}
	else if (option == 3)
	{
		hayArray = true;
		aspasMolino = new AspasMolino(mSM, numAspas, hayArray);
	}

};

void IG2App::startScene4(int option)
{
	if (option == 0)
	{
		molino = new Molino(mSM, 12);
	}
	else if (option == 1)
	{
		planets = mSM->getRootSceneNode()->createChildSceneNode();
		helpers::createEntity(mSM, solNode, "sol", "sphere.mesh", planets)->setScale({ 1,1,1 });

		helpers::createEntity(mSM, tierraNode, "tierra", "sphere.mesh", planets)->translate({-250,0,0});
		tierraNode->setScale({ 0.5,0.5,0.5 });
		
		helpers::createEntity(mSM, lunaNode, "luna", "sphere.mesh", tierraNode)->setPosition({-150,0,0});
		lunaNode->setScale({ 0.1,0.1,0.1 });
		
	}

};

int IG2App::Aspa::id = 0;
IG2App::Aspa::Aspa(Ogre::SceneManager* sm, Ogre::SceneNode* parent)
{
	mSM = sm;
	if (parent)
	{
		aspaNode = parent->createChildSceneNode("aspa_" + std::to_string(Aspa::id));
	}
	else
	{
		aspaNode = mSM->getRootSceneNode()->createChildSceneNode("aspa_" + std::to_string(Aspa::id));
	}
	
	tableroNode = aspaNode->createChildSceneNode("tablero_" + std::to_string(Aspa::id));
	Ogre::Entity* ent = mSM->createEntity("cube.mesh");
	tableroNode->attachObject(ent);
	tableroNode->setScale(Vector3(.1, 1,.1));
	tableroNode->setPosition(0, -60, 0);
	cilindroNode = aspaNode->createChildSceneNode("adorno_" + std::to_string(Aspa::id));
	ent = mSM->createEntity("Barrel.mesh");
	cilindroNode->attachObject(ent);
	cilindroNode->setPosition(0, -100, 5);
	addID();
}

IG2App::AspasMolino::AspasMolino(Ogre::SceneManager* sm,int n, bool saveInArray, Ogre::SceneNode* parent) 
{
	mSM = sm;
	numAspas = n;
	aspasNode = (!parent) ? 
		sm->getRootSceneNode()->createChildSceneNode("aspasMolino") : parent->createChildSceneNode("aspasMolino");
	
	//Para el enunciado 4 5 6
	if (!saveInArray) 
	{
		for (int i = 0; i < numAspas; i++)
		{
			Aspa a = Aspa(mSM, aspasNode);
			a.aspaNode->roll(Angle(i * (360 / numAspas)));
			a.cilindroNode->roll(Angle(-i * (360 / numAspas)));
		}
	}
	//Para el enunciado 7 8 
	else 
	{
		arrayAspas = new IG2App::Aspa * [numAspas];
		for (int i = 0; i < numAspas; i++)
		{
			arrayAspas[i] = new Aspa(mSM, aspasNode);
			arrayAspas[i]->aspaNode->roll(Angle(i * (360 / numAspas)));
			arrayAspas[i]->cilindroNode->roll(Angle(-i * (360 / numAspas)));
		}
	}
}


IG2App::Molino::Molino(Ogre::SceneManager* sm, int n)
{
	mSM = sm;
	mNode = mSM->getRootSceneNode()->createChildSceneNode();
	aspasParent = mNode->createChildSceneNode();
	helpers::createEntity(mSM, cilindroNode, "paredes", "Barrel.mesh", mNode)->scale({10.5,45,10.5});
	cilindroNode->setPosition({0,0,0});

	helpers::createEntity(mSM, botoncicoNode, "boton", "Barrel.mesh", aspasParent)->pitch(Ogre::Degree(90));
	botoncicoNode->scale({ 5, 1.5, 5});
	botoncicoNode->setPosition({ 0, 125, 40 });

	helpers::createEntity(mSM, esferaNode, "techo", "sphere.mesh")->scale(Vector3(0.28));
	esferaNode->setPosition({0,130,0});
	
	
	aspas = new AspasMolino(sm, n, true, aspasParent);
	aspas->aspasNode->setPosition(0, 125, 34);
}
