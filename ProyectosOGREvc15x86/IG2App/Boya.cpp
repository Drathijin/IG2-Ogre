#include "Boya.h"
#include "IG2ApplicationContext.h"

#include <OgreEntity.h>
#include <OgreAnimation.h>
#include <OgreKeyFrame.h>

using namespace Ogre;


Boya::Boya(Nodo* parent)
	: EntidadIG(parent->createChildSceneNode())
{
	ent = mSM->createEntity("uv_sphere.mesh");
	ent->setMaterialName("IG2/ExplotaGLSL");


	float duration = 25.0f;
	float longDesplazamiento = 20.0f;
	Animation* animation = mSM->createAnimation("BoyaRotation", duration);
	NodeAnimationTrack* track = animation->createNodeTrack(0);
	track->setAssociatedNode(mNode);
	Real durPaso = duration / 5.0;
	Vector3 keyframePos(0.0); Vector3 src(0, 0, 1); // posición y orientación iniciales
	TransformKeyFrame* kf; // 5 keyFrames: origen(0), abajo, origen (2), arriba, origen(4)
	kf = track->createNodeKeyFrame(durPaso * 0); // Keyframe 0: origen


	kf = track->createNodeKeyFrame(durPaso * 1); // Keyframe 1: arriba
	keyframePos += Ogre::Vector3::UNIT_Y * longDesplazamiento * 2;
	kf->setTranslate(keyframePos); // Arriba
	kf->setRotation(src.getRotationTo(Vector3(-1, 0, 1))); // Yaw(-45)



	kf = track->createNodeKeyFrame(durPaso * 2); // Keyframe 2: arriba
	keyframePos -= Ogre::Vector3::UNIT_Y * longDesplazamiento * 2;
	kf->setTranslate(keyframePos); // Centro
	kf->setRotation(src.getRotationTo(Vector3(-1, 0, 1))); // Yaw(-45)



	kf = track->createNodeKeyFrame(durPaso * 3); // Keyframe 3: abajo
	keyframePos += Ogre::Vector3::NEGATIVE_UNIT_Y * longDesplazamiento;
	kf->setTranslate(keyframePos); // Abajo
	kf->setRotation(src.getRotationTo(Vector3(1, 0, 1))); // Yaw(45)



	kf = track->createNodeKeyFrame(durPaso * 4); // Keyframe 4: origen
	keyframePos -= Ogre::Vector3::NEGATIVE_UNIT_Y * longDesplazamiento;
	kf->setTranslate(keyframePos); // Centro
	kf->setRotation(src.getRotationTo(Vector3(-1, 0, 1))); // Yaw(45)


	mNode->attachObject(ent);

	animationState = mSM->createAnimationState("BoyaRotation");
	animationState->setEnabled(true);
	animationState->setLoop(true);
}
void Boya::frameRendered(const Ogre::FrameEvent& evt)
{
	animationState->addTime(evt.timeSinceLastFrame);
};
