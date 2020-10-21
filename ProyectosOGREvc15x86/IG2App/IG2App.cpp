#include "IG2App.h"

#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <iostream>

using namespace Ogre;

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
	  mSpheresParent->roll(Ogre::Degree(18));

  }
  else if (evt.keysym.sym == SDLK_p)
  {
	  aspaNode->roll(Ogre::Degree(18));
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

  int scene = 1;
  int option = 1;
  
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

void IG2App::createEntity(Ogre::SceneNode*& node, std::string id, std::string mesh, Ogre::Vector3 scale, Ogre::SceneNode* parent)
{
	Ogre::Entity* ent = mSM->createEntity(mesh);
	node = (!parent) ? mSM->getRootSceneNode()->createChildSceneNode(id) : parent->createChildSceneNode(id);
	node->attachObject(ent);
	node->scale(scale);
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
		createEntity(mSinbad, "dragon", "dragon.mesh", Vector3(0.75));
		mSinbad->setPosition(0, 75, 0);
		mSinbad->yaw(Ogre::Degree(180));
	}
	else if (option == 1)
	{

		createEntity(mSinbad, "sinbad", "Sinbad.mesh", Vector3(20));
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
		createEntity(mHours[i], "sphere" + std::to_string(i), "sphere.mesh", Vector3(1), mSpheresParent);
		mHours[i]->setPosition(Ogre::Math::Cos(radians) * rad, Ogre::Math::Sin(radians) * rad, 0);
	}
	for (int i = 0; i < 3; i++)
	{
		createEntity(mNeedles[i], "needle" + std::to_string(i), "column.mesh", Vector3(2.5 / (i + 1), 2.5 / (i + 1), 1), mTotalParent);
		mNeedles[i]->roll(Ogre::Degree(-90 * i));
	}
	mNeedles[2]->roll(Ogre::Degree(-45));
	
	mCamNode->setPosition(0, 0, 10000);
}
void IG2App::startScene3(int option)
{
	if (option == 0)
	{
		aspaNode = mSM->getRootSceneNode()->createChildSceneNode();
		createEntity(cilindroNode, "adorno", "column.mesh", Vector3(4, 1, 4), aspaNode);
		createEntity(tableroNode, "tablero", "cube.mesh", Vector3(5, 30, 1), aspaNode);

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
			createEntity(tableroNodes[i], "tablero_" + std::to_string(i), "cube.mesh", Vector3(.1, 1, .1), aspaContainer[i]);
			createEntity(cilindroNodes[i], "adorno_" + std::to_string(i), "column.mesh", Vector3(0.05, 0.05, 0.05), aspaContainer[i]);

			cilindroNodes[i]->setPosition(0, -100, 30);
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
	}
	else if (option == 1)
	{
	}
	else if (option == 2)
	{
	}
	else if (option == 3)
	{
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
	ent = mSM->createEntity("column.mesh");
	cilindroNode->attachObject(ent);
	cilindroNode->setScale(Vector3(0.05));
	cilindroNode->setPosition(Vector3(0, 0, 30));
	cilindroNode->setPosition(0, -100, 30);
	addID();
}

IG2App::AspasMolino::AspasMolino(Ogre::SceneManager* sm,int n, bool flag)
{
	mSM = sm;
	numAspas = n;
	aspasNode = sm->getRootSceneNode()->createChildSceneNode("aspasMolino");
	if (!flag) 
	{
		for (int i = 0; i < numAspas; i++)
		{
			Aspa a = Aspa(mSM, aspasNode);
			a.aspaNode->roll(Angle(i * (360 / numAspas)));
			a.cilindroNode->roll(Angle(-i * (360 / numAspas)));
		}
	}
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
	createEntity(cilindroNode, "paredes", "column.mesh", Vector3(1), mNode);
	createEntity(esferaNode, "techo", "sphere.mesh");

	//no se si poner true o false porque no se para que era el flag ¬¬
	//aspasMolino = AspasMolino(sm, n, true);
}
