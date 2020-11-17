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
	aspas->roll(Ogre::Degree(1));
	for (int i = 0; i < numAspas; i++) 
		cilindroNodes[i]->roll(Ogre::Degree(-1));
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
  else if(evt.keysym.sym == SDLK_r)
	  EntidadIG::sendEvent(EntidadIG::MessageType::emptyRiver, nullptr);

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

  //mLightNode->setPosition(0, 0, 1000);
 
  //------------------------------------------------------------------------
 

  constexpr int scene = 5;
  int option = 0;
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
  case 5:
	  startScene5(option);
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

void IG2App::startScene2(int option) {

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
};

void IG2App::startScene5(int option)
{
	Nodo* parent = mSM->getRootSceneNode()->createChildSceneNode();
	Plano* base = new Plano(parent, 1200, 800, "Plano/Agua", "River");

	Plano* baseSimbad = new Plano(base->getNode(), 200, 200, "Plano/Sinbad");
	baseSimbad->getNode()->translate({ 100 - 600,2,300 });

	Plano* baseMolino = new Plano(parent, 500, 500, "Plano/Molino");
	baseMolino->getNode()->translate({ 600 - 250,2,-150 });

	Avion* plane = new Avion(parent);
	plane->getNode()->scale(Vector3(0.3));
	plane->getNode()->translate({ 350 - 100, 200, -130 - 100 });
	addInputListener(plane);
	addInputListener(plane->left);
	addInputListener(plane->right);

	Molino* molino = new Molino(mSM, 12, baseMolino->getNode());
	molino->getNode()->translate({ 0,140,20 });
	addInputListener(molino);
	addInputListener(molino->aspas);

	Nodo* carita;
	helpers::createEntity(mSM, carita, "billboard", "sphere.mesh", parent, "Esfera/Cabeza");
	carita->translate(Vector3(400, 27, -100));
	carita->scale(Vector3(0.25));

	Simbad* simbad = new Simbad(baseSimbad->getNode(), option == 0);
	simbad->getNode()->scale({ 20,20,20 });
	simbad->getNode()->translate({ 0,100,0 });
	addInputListener(simbad);
	
	if (option == 0)
	{
		Boya* boya = new Boya(parent);
		addInputListener(boya);
	}
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

void IG2App::Plano::receiveEvent(MessageType msj, EntidadIG* entidad)
{
	if (msj == EntidadIG::MessageType::emptyRiver && mEnt->getName()== "River")
	{
		mEnt->setMaterialName("Plano/SinAgua");
	}
}

IG2App::Simbad::Simbad(Nodo* parent, bool listener) : EntidadIG(parent->createChildSceneNode())
{
	ent = mSM->createEntity("Sinbad.mesh");
	isInputListener = listener;
	if (!isInputListener)
	{
		//anadimos la animacion para que camine de un punto a otro
		float duration = 5.0f;
		float rot = 1;
		Animation* animation = mSM->createAnimation("WalkingCycle", duration);
		NodeAnimationTrack* track = animation->createNodeTrack(0);
		track->setAssociatedNode(mNode);
		Real durPaso = duration / 2.0;
		Vector3 keyframePos(0.0); Vector3 src(0, 0, 1); // posición y orientación iniciales 
		TransformKeyFrame* kf; // 4 keyFrames: origen(0), giro (0.1), centro (0.9), giro(1)
		Vector3 scale(20);

		kf = track->createNodeKeyFrame(durPaso * 0); // Keyframe 0: origen
		keyframePos += Ogre::Vector3::UNIT_Y * 100;
		kf->setTranslate(keyframePos);
		kf->setRotation(src.getRotationTo(Vector3(-1, 0, 1))); 
		kf->setScale(scale);

		kf = track->createNodeKeyFrame(durPaso * 0 + 0.1); // Keyframe 0.1: giro
		kf->setTranslate(keyframePos); // Origen
		kf->setRotation(src.getRotationTo(Vector3(1, 0, -1))); 
		kf->setScale(scale);

		kf = track->createNodeKeyFrame(durPaso * 0.9); // Keyframe 0.9: centro
		keyframePos += Ogre::Vector3::UNIT_X * 500;
		keyframePos -= Ogre::Vector3::UNIT_Z * 300;
		kf->setTranslate(keyframePos); // Río
		kf->setRotation(src.getRotationTo(Vector3(1, 0, -1))); 
		kf->setScale(scale);


		kf = track->createNodeKeyFrame(durPaso * 1); // Keyframe 1: giro
		kf->setTranslate(keyframePos); // Origen
		kf->setRotation(src.getRotationTo(Vector3(-1, 0, 1))); 
		kf->setScale(scale);



		animationState = mSM->createAnimationState("WalkingCycle");
		animationState->setEnabled(true);
		animationState->setLoop(true);

	}
	
	//buscamos las dos animaciones de caminado
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

bool IG2App::Simbad::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_c && isInputListener)
	{
		walking = !walking;
		dancing = !dancing;
		for (auto pair : ent->getAllAnimationStates()->getAnimationStates())
		{
			auto animationState = pair.second;
			animationState->setEnabled(false);
			if (walking && (pair.first == "RunTop" || pair.first == "RunBase"))
			{
				animationState->setEnabled(true);
				animationState->setLoop(true);
			}
			else if (dancing && pair.first == "Dance")
			{
				animationState->setEnabled(true);
				animationState->setLoop(true);
			}
		}
	}
	else if (evt.keysym.sym == SDLK_e && isInputListener)
	{
		ent->detachObjectFromBone(sword);
		right = !right;
		std::string bone = (right) ? "Handle.R" : "Handle.L";
		ent->attachObjectToBone(bone, sword);
	}
	return false;
}
void IG2App::Simbad::frameRendered(const Ogre::FrameEvent& evt)
{
	for (auto pair : ent->getAllAnimationStates()->getAnimationStates())
	{
		auto animationState = pair.second;
		if (animationState->getEnabled())
			animationState->addTime(evt.timeSinceLastFrame);
	}
	if(!isInputListener)
		animationState->addTime(evt.timeSinceLastFrame);
};

IG2App::Boya::Boya(Nodo* parent)
	: EntidadIG(parent->createChildSceneNode())
{
	ent = mSM->createEntity("Barrel.mesh");
	ent->setMaterialName("Avion/Alas");


	float duration = 25.0f;
	float longDesplazamiento = 20.0f;
	Animation* animation = mSM->createAnimation("BoyaRotation", duration);
	NodeAnimationTrack* track = animation->createNodeTrack(0);
	track->setAssociatedNode(mNode);
	Real durPaso = duration / 5.0;
	Vector3 keyframePos(0.0); Vector3 src(0, 0, 1); // posición y orientación iniciales
	TransformKeyFrame* kf; // 5 keyFrames: origen(0), abajo, origen (2), arriba, origen(4)
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


	
	kf = track->createNodeKeyFrame(durPaso * 4); // Keyframe 4: origen
	keyframePos -= Ogre::Vector3::NEGATIVE_UNIT_Y * longDesplazamiento;
	kf->setTranslate(keyframePos); // Centro
	kf->setRotation(src.getRotationTo(Vector3(-1, 0, 1))); // Yaw(45)
	kf->setScale(Vector3(20)); 


	mNode->attachObject(ent);

	animationState = mSM->createAnimationState("BoyaRotation");
	animationState->setEnabled(true);
	animationState->setLoop(true);
}
void IG2App::Boya::frameRendered(const Ogre::FrameEvent& evt)
{
	animationState->addTime(evt.timeSinceLastFrame);
};
