#pragma once
#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include <OgreParticleSystem.h>
#include "EntidadIG.h";
#include "Aspas.h"

using Nodo = Ogre::SceneNode;

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
    Nodo* cartel = nullptr;
    Ogre::ParticleSystem* smoke = nullptr;
    Ogre::ParticleSystem* trail = nullptr;

    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

    virtual void frameRendered(const Ogre::FrameEvent& evt);
};
