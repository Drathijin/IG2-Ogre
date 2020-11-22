#include "Simbad.h"
#include "IG2ApplicationContext.h"

#include <OgreEntity.h>
#include <OgreAnimation.h>
#include <OgreKeyFrame.h>


Simbad::Simbad(Nodo* parent, bool listener) : EntidadIG(parent->createChildSceneNode())
{
	ent = mSM->createEntity("Sinbad.mesh");

	mNode->attachObject(ent);
	right = true;
	sword = mSM->createEntity("Sword.mesh");
	ent->attachObjectToBone("Handle.R", sword);


	isInputListener = listener;
	//anadimos la animacion para que camine de un punto a otro
	float duration = 5.0f;
	float rot = 1;
	Ogre::Animation* animation = mSM->createAnimation("WalkingCycle", duration);
	Ogre::NodeAnimationTrack* track = animation->createNodeTrack(0);
	track->setAssociatedNode(mNode);
	Ogre::Real durPaso = duration / 2.0;
	Ogre::Vector3 keyframePos(0.0,0.0,0.0); Ogre::Vector3 src(0, 0, 1); // posición y orientación iniciales 
	Ogre::TransformKeyFrame* kf; // 4 keyFrames: origen(0), giro (0.1), centro (0.9), giro(1)
	Ogre::Vector3 scale(20);

	kf = track->createNodeKeyFrame(durPaso * 0); // Keyframe 0: origen
	keyframePos += Ogre::Vector3::UNIT_Y * 100;
	kf->setTranslate(keyframePos);
	kf->setRotation(src.getRotationTo(-Ogre::Vector3(-1, 0, 1)));
	kf->setScale(scale);

	kf = track->createNodeKeyFrame(durPaso * 0 + 0.1); // Keyframe 0.1: giro
	kf->setTranslate(keyframePos); // Origen
	kf->setRotation(src.getRotationTo(-Ogre::Vector3(1, 0, -1)));
	kf->setScale(scale);

	kf = track->createNodeKeyFrame(durPaso * 0.9); // Keyframe 0.9: centro
	keyframePos -= Ogre::Vector3::UNIT_X * 500;
	keyframePos += Ogre::Vector3::UNIT_Z * 300;
	kf->setTranslate(keyframePos); // Río
	kf->setRotation(src.getRotationTo(-Ogre::Vector3(1, 0, -1)));
	kf->setScale(scale);


	kf = track->createNodeKeyFrame(durPaso * 1); // Keyframe 1: giro
	kf->setTranslate(keyframePos); // Origen
	kf->setRotation(src.getRotationTo(-Ogre::Vector3(-1, 0, 1)));
	kf->setScale(scale);



	animationState = mSM->createAnimationState("WalkingCycle");
	animationState->setEnabled(true);
	animationState->setLoop(true);


	//buscamos las dos animaciones de caminado
	for (auto pair : ent->getAllAnimationStates()->getAnimationStates())
	{
		auto animationState = pair.second;
		if (pair.first == "RunTop" || pair.first == "RunBase" )
		{
			animationState->setEnabled(true);
			animationState->setLoop(true);
		}
	}


}

bool Simbad::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_r && isInputListener)
	{
		walking = !walking;
		//dancing = !dancing;
		for (auto pair : ent->getAllAnimationStates()->getAnimationStates())
		{
			auto animationState = pair.second;
			animationState->setEnabled(false);

			if(pair.first == "RunTop" || pair.first == "RunBase")
			{
				animationState->setEnabled(walking);
				animationState->setLoop(walking);
			}
			else if (pair.first == "IdleTop")
			{
				animationState->setEnabled(!walking);
				animationState->setLoop(!walking);
			}


		}
		if (!walking)
		{
			mNode->translate({ 0,-80,0 });
			mNode->pitch(Ogre::Degree(-90));
			animationState->setLoop(false);
			animationState->setEnabled(false);

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
void Simbad::frameRendered(const Ogre::FrameEvent& evt)
{
	for (auto pair : ent->getAllAnimationStates()->getAnimationStates())
	{
		auto animationState = pair.second;
		if (animationState->getEnabled())
			animationState->addTime(evt.timeSinceLastFrame);
	}
	
	if(walking)
		animationState->addTime(evt.timeSinceLastFrame);
};
