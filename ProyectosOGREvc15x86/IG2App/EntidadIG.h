#pragma once
#include <OGRE/OgreSubEntity.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreSceneNode.h>

class Obj : public OgreBites::InputListener
{
public:
	Obj(Ogre::SceneNode* node) : mNode(node) { mSM = mNode->getCreator(); };
	~Obj(){}
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	virtual void frameRendered(const Ogre::FrameEvent& evt);
protected:
	Ogre::SceneNode* mNode;
	Ogre::SceneManager* mSM;
};

class EntidadIG :public OgreBites::InputListener{
public:
	EntidadIG(Ogre::SceneNode* node) :  OgreBites::InputListener()
	{
		mSM = node->getCreator();
		mNode = node;
		addListener(this);
	}
	~EntidadIG();
	enum class MessageType
	{
		update = 0
	};
	static std::vector<EntidadIG*> appListeners;
	static void addListener(EntidadIG* entidad) { appListeners.push_back(entidad); };
	void sendEvent(MessageType msj, EntidadIG* entidad);
	virtual void receiveEvent(MessageType msj, EntidadIG* entidad) {};
	virtual Ogre::SceneNode* getNode() { return mNode; };
protected:
	Ogre::SceneNode* mNode;
	Ogre::SceneManager* mSM;
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
};