#include "IG2App.h"

#include <OgreEntity.h>
#include <OgreAnimation.h>
#include <OgreKeyFrame.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <iostream>

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
  else if(evt.keysym.sym == SDLK_g && aspas)
  {
  
	 // if (aspas) 
	 // {
	aspas->roll(Ogre::Degree(1));
	for (int i = 0; i < numAspas; i++) 
		cilindroNodes[i]->roll(Ogre::Degree(-1));
	 // }
  }
  else if (evt.keysym.sym == SDLK_h)
  {
	  //if(molino)
	  //{
		 // molino->aspasParent->yaw(Ogre::Degree(10), Ogre::Node::TS_PARENT);
	  //}
	  if (mSpheresParent)
	  {
		  mNeedles[2]->roll(Ogre::Degree(-5));
	  }
  }
  else if (evt.keysym.sym == SDLK_p && aspaNode)
  {
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
 // else if (evt.keysym.sym == SDLK_c)
 // {
	//if(molino)
	//{
	//	  molino->aspas->botoncicoNode->translate(Vector3(0, 0, -50));
	//}
 // }

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
  luz->setDirection({ 0,-1, -1 });
  

  mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
  //mLightNode = mCamNode->createChildSceneNode("nLuz");
  mLightNode->attachObject(luz);

  //Ogre::MaterialManager::getSingleton().create("Avion/Cuerpo", "Practica1.material", false);
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
  int option = 3;
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
		setArray(false);
		aspasMolino = new AspasMolino(numAspas, hayArray,mSM->getRootSceneNode()->createChildSceneNode());
		addInputListener(aspasMolino);
	}
	else if (option == 3)
	{
		setArray(true);
		aspasMolino = new AspasMolino(numAspas, hayArray, mSM->getRootSceneNode()->createChildSceneNode());
		addInputListener(aspasMolino);
	}
};
void IG2App::startScene4(int option)
{	
	if (option == 0)
	{
		molino = new Molino(mSM, 12, mSM->getRootSceneNode()->createChildSceneNode());
		addInputListener(molino);
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
	else if (option == 2)
	{
		avion = new Avion(mSM->getRootSceneNode()->createChildSceneNode());
		addInputListener(avion);
	}
	else if (option == 3)
	{
		Nodo* parent = mSM->getRootSceneNode()->createChildSceneNode();
		Plano * base = new Plano(parent, 1200,800, "Plano/Agua", "River");

		Plano * baseSimbad = new Plano(base->getNode(),200,200, "Plano/Sinbad");
		baseSimbad->getNode()->translate({ 100-600,2,300 });

		Plano * baseMolino = new Plano(parent,500,500, "Plano/Molino");
		baseMolino->getNode()->translate({ 600-250,2,-150 });

		Avion* plane = new Avion(parent);
		plane->getNode()->scale(Vector3(0.3));
		plane->getNode()->translate({ 350 - 100, 200, -130 - 100 });
		addInputListener(plane);
		addInputListener(plane->left);
		addInputListener(plane->right);
		
		Molino* molino = new Molino(mSM, 12, baseMolino->getNode());
		molino->getNode()->translate({0,140,20});
		addInputListener(molino);
		addInputListener(molino->aspas);

		//Nodo* sinbad = nullptr;
		//createEntity(sinbad, "sinbad", "Sinbad.mesh", baseSimbad->getNode())->scale(Vector3(20));
		Nodo* carita;
		helpers::createEntity(mSM, carita, "billboard", "sphere.mesh", parent, "Esfera/Cabeza");
		carita->translate(Vector3(400, 27, -100));
		carita->scale(Vector3(0.25));

		//sinbad->translate({ 0,100,0 });
		Simbad* simbad = new Simbad(baseSimbad->getNode());
		simbad->getNode()->scale({ 20,20,20 });
		simbad->getNode()->translate({0,100,0});
		addInputListener(simbad);

		Boya* boya = new Boya(parent);
		addInputListener(boya);
		//mSM->getLight("Luz")->setVisible(false);
	}
};



int IG2App::Aspa::id = 0;
IG2App::Aspa::Aspa(Ogre::SceneManager* sm, Nodo* parent) : 
	EntidadIG(parent->createChildSceneNode())
{	
	tableroNode = mNode->createChildSceneNode("tablero_" + std::to_string(Aspa::id));
	Ogre::Entity* ent = mSM->createEntity("cube.mesh");
	ent->setMaterialName("Aspas/Tabla");
	tableroNode->attachObject(ent);
	tableroNode->setScale(Vector3(.1, 1,.1));
	tableroNode->setPosition(0, -60, 0);
	cilindroNode = mNode->createChildSceneNode("adorno_" + std::to_string(Aspa::id));
	ent = mSM->createEntity("Barrel.mesh");
	ent->setMaterialName("Aspas/Adorno");
	cilindroNode->attachObject(ent);
	cilindroNode->setPosition(0, -100, 5);
	addID();}
int IG2App::AspasMolino::count = 0;
IG2App::AspasMolino::AspasMolino(int n, bool flag, Nodo* parent, float speed) 
	: EntidadIG(parent->createChildSceneNode()), rSpeed(speed)
{
	numAspas = n;
	savedInArray = flag;
	std::string name = "aspasMolino" + AspasMolino::count;
	//Para el enunciado 4 5 6
	if (!savedInArray)
	{
		for (int i = 0; i < numAspas; i++)
		{
			Aspa a = Aspa(mSM, mNode);
			a.getNode()->roll(Angle(i * (360 / numAspas)));
			a.cilindroNode->roll(Angle(-i * (360 / numAspas)));
		}
	}
	//Para el enunciado 7 8 
	else 
	{
		arrayAspas = new IG2App::Aspa * [numAspas];
		for (int i = 0; i < numAspas; i++)
		{
			arrayAspas[i] = new Aspa(mSM, mNode);
			arrayAspas[i]->getNode()->roll(Angle(i * (360 / numAspas)));
			arrayAspas[i]->cilindroNode->roll(Angle(-i * (360 / numAspas)));
		}
	}
	helpers::createEntity(mSM, botoncicoNode, "boton"+AspasMolino::count, "Barrel.mesh", parent, "Aspas/Botoncico")->pitch(Ogre::Degree(90));
	botoncicoNode->scale({ 5, 1.5, 5 });
	botoncicoNode->setPosition({ 0, 0, 10 });//ok
	AspasMolino::count++;	
}


IG2App::Molino::Molino(Ogre::SceneManager* sm, int n, Nodo* parent) :
	EntidadIG(parent->createChildSceneNode())
{
	mSM = sm;
	aspasParent = mNode->createChildSceneNode();
	helpers::createEntity(mSM, cilindroNode, "paredes", "Barrel.mesh", mNode, "Molino/Paredes")->scale({10.5,45,10.5});
	cilindroNode->setPosition({0,0,0});

	helpers::createEntity(mSM, esferaNode, "techo", "sphere.mesh", mNode, "Molino/Techo")->scale(Vector3(0.26));
	esferaNode->setPosition({0,130,0});
	
	aspas = new AspasMolino(n, true, aspasParent, 10);
	
	aspasParent->translate({ 0,125,34 }); 
}
bool IG2App::Molino::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	static bool botonPaTras = false;
	if(evt.keysym.sym == SDLK_h)
	{
		aspasParent->translate({ 0, 0, -34 }, Ogre::Node::TS_LOCAL);
		aspasParent->yaw(Ogre::Degree(10), Ogre::Node::TS_LOCAL);
		aspasParent->translate({ 0, 0, 34 }, Ogre::Node::TS_LOCAL);
	}
	else if (evt.keysym.sym == SDLK_c)
	{
		aspas->botoncicoNode->translate(Vector3(0, 0, botonPaTras ? 50 : -50));
		botonPaTras = !botonPaTras;
	}
	else if (evt.keysym.sym == SDLK_r)
	{
		spin = false;
		auto objs = esferaNode->getAttachedObjects();
		for (auto o : objs)
		{
			((Ogre::Entity*)o)->setMaterialName("Avion/Cuerpo");
		}
		sendEvent(EntidadIG::MessageType::emptyRiver, nullptr);
	}
	return true;
}
bool IG2App::AspasMolino::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_g)
	{
		girarAspas();
	}
	else if (evt.keysym.sym == SDLK_r)
	{
		if (savedInArray)
		{
			for (int i = 0; i < numAspas; i++)
				arrayAspas[i]->cilindroNode->setVisible(false);
		}
		else
		{
			for (int i = 0; i < numAspas; i++)
				mSM->getSceneNode("adorno_" + std::to_string(i))->setVisible(false);
		}
	}
	return 1;
}
void IG2App::AspasMolino::girarAspas(float delta)
{
	mNode->roll(Ogre::Degree(rSpeed*delta));

	if (savedInArray)
	{
		for (int i = 0; i < numAspas; i++)
			arrayAspas[i]->cilindroNode->roll(Ogre::Degree(-rSpeed * delta), Ogre::Node::TS_PARENT);
	}
	else
	{
		for (int i = 0; i < numAspas; i++)
			mSM->getSceneNode("adorno_" + std::to_string(i))->roll(Ogre::Degree(-rSpeed * delta));
	}
}
IG2App::Avion::Avion(Nodo* parent) : 
	EntidadIG(parent->createChildSceneNode())
{
	helpers::createEntity(mSM, mCuerpoNode, "AvionCuerpo", "sphere.mesh", mNode, "Avion/Cuerpo");


	float scale = 2.5;
	float offset = 200;

	helpers::createEntity(mSM, malaINode, "AvionAlaI", "cube.mesh", mNode, "Avion/Alas");
	malaINode->scale({ scale,0.1,1 });
	malaINode->translate({ offset,0,0 });
	heliceNodeL = mNode->createChildSceneNode();
	left = new AspasMolino(5, 1, heliceNodeL, 2000);
	heliceNodeL->translate({ offset,0,50 });


	helpers::createEntity(mSM, malaDNode, "AvionAlaD", "cube.mesh", mNode, "Avion/Alas");
	malaDNode->scale({ scale,0.1,1 });
	malaDNode->translate({ -offset,0,0 });
	heliceNodeR = mNode->createChildSceneNode();
	right=new AspasMolino(5, 1, heliceNodeR, 2000);
	heliceNodeR->translate({ -offset,0,50 });

	helpers::createEntity(mSM, botoncico, "boton879879754321xD", "Barrel.mesh", mNode, "Avion/Botoncico")->pitch(Ogre::Degree(90));
	botoncico->translate({ 0,0,100 });
	botoncico->scale({10,2,10 });

	helpers::createEntity(mSM, pilotoNode, "piloto", "ninja.mesh", mNode, "Avion/Piloto");
	pilotoNode->translate({ 0,-30,-15 }); 
	pilotoNode->yaw(Ogre::Degree(180));

	planeLight = mSM->createLight("planeLight");
	planeLight->setType(Ogre::Light::LT_SPOTLIGHT);
	planeLight->setDiffuseColour(0.75, 0.75, 0.75);
	planeLight->setDirection({1,-1,0});
	planeLight->setSpotlightOuterAngle(Ogre::Degree(90));


	//planeLight->setDiffuseColour(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
	//planeLight->setDirection(Ogre::Vector3(1, -1, 0));
	//planeLight->setSpotlightInnerAngle(Ogre::Degree(5.0f));
	//planeLight->setSpotlightOuterAngle(Ogre::Degree(45.0f));
	//planeLight->setSpotlightFalloff(0.0f);

	planeLight->setCastShadows(true);
	auto lightNode = mNode->createChildSceneNode();
	lightNode->attachObject(planeLight);
	lightNode->translate({ 0,-40,0 }); 

	mSM->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
}
bool IG2App::Avion::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_r)
	{
		spin = false;
		planeLight->setVisible(false);
	}
	return true;
}
int IG2App::Plano::id = 0;
IG2App::Plano::Plano(Nodo* parent, float width, float height, std::string matName, std::string entName ) :EntidadIG(parent->createChildSceneNode())
{
	auto p = MeshManager::getSingleton().createPlane("plane"+std::to_string(Plano::id),
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Plane(Vector3::UNIT_Y, 0),
		width, height, 100, 80, true, 1, 1.0, 1.0, Vector3::UNIT_Z);
	mEnt = (entName == "") ? mSM->createEntity(p) : mSM->createEntity(entName, p);
	
	if (matName != "")
		mEnt->setMaterialName(matName);
	mNode->attachObject(mEnt);

	IG2App::Plano::id++;
}

bool IG2App::Plano::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	return false;
}

void IG2App::Plano::receiveEvent(MessageType msj, EntidadIG* entidad)
{
	if (msj == EntidadIG::MessageType::emptyRiver && mEnt->getName()== "River")
	{
		mEnt->setMaterialName("Plano/SinAgua");
	}
}

IG2App::Simbad::Simbad(Nodo* parent) : EntidadIG(parent->createChildSceneNode())
{
	ent = mSM->createEntity("Sinbad.mesh");
	//animationState =/* mSM->createAnimationState("Dance");*/
	//ent->getAnimationState("RunTop");
	//ent->getAnimationState("RunBase");
	for (auto pair : ent->getAllAnimationStates()->getAnimationStates())
	{
		auto animationState = pair.second;
		if (pair.first == "RunTop" || pair.first == "RunBase")
		{
			animationState->setEnabled(true);
			animationState->setLoop(true);
		}
	}



	mNode->attachObject(ent);
	right = true;
	sword = mSM->createEntity("Sword.mesh");
	ent->attachObjectToBone("Handle.R", sword);
}

IG2App::Boya::Boya(Nodo* parent)
	: EntidadIG(parent->createChildSceneNode())
{
	ent = mSM->createEntity("Barrel.mesh");
	ent->setMaterialName("Avion/Alas");


	float duration = 25.0f;
	float longDesplazamiento = 20.0f;
	Animation* animation = mSM->createAnimation("animVV", duration);
	NodeAnimationTrack* track = animation->createNodeTrack(0);
	track->setAssociatedNode(mNode);
	//Vector3 keyframePos(-10., 0., 100.);
	Real durPaso = duration / 5.0;
	Vector3 keyframePos(0.0); Vector3 src(0, 0, 1); // posición y orientación iniciales
	TransformKeyFrame* kf; // 4 keyFrames: origen(0), abajo, arriba, origen(3)
	kf = track->createNodeKeyFrame(durPaso * 0); // Keyframe 0: origen
	kf->setScale(Vector3(20));


	kf = track->createNodeKeyFrame(durPaso * 1); // Keyframe 1: arriba
	keyframePos += Ogre::Vector3::UNIT_Y * longDesplazamiento * 2;
	kf->setTranslate(keyframePos); // Arriba
	kf->setRotation(src.getRotationTo(Vector3(-1, 0, 1))); // Yaw(-45)
	kf->setScale(Vector3(20));



	kf = track->createNodeKeyFrame(durPaso * 2); // Keyframe 2: arriba
	keyframePos -= Ogre::Vector3::UNIT_Y * longDesplazamiento * 2;
	kf->setTranslate(keyframePos); // Centro
	kf->setRotation(src.getRotationTo(Vector3(-1, 0, 1))); // Yaw(-45)
	kf->setScale(Vector3(20));



	kf = track->createNodeKeyFrame(durPaso * 3); // Keyframe 3: abajo
	keyframePos += Ogre::Vector3::NEGATIVE_UNIT_Y * longDesplazamiento;
	kf->setTranslate(keyframePos); // Abajo
	kf->setRotation(src.getRotationTo(Vector3(1, 0, 1))); // Yaw(45)
	kf->setScale(Vector3(20)); 


	
	kf = track->createNodeKeyFrame(durPaso * 4); // Keyframe 3: origen
	keyframePos -= Ogre::Vector3::NEGATIVE_UNIT_Y * longDesplazamiento;
	kf->setTranslate(keyframePos); // Abajo
	kf->setRotation(src.getRotationTo(Vector3(1, 0, 1))); // Yaw(45)
	kf->setScale(Vector3(20)); 


	mNode->attachObject(ent);

	animationState = mSM->createAnimationState("animVV");
	animationState->setEnabled(true);
	animationState->setLoop(true);
};
