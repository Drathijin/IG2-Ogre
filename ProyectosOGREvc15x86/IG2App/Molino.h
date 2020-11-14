#pragma once
#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include "EntidadIG.h";
#include "Aspas.h"

using Nodo = Ogre::SceneNode;


class Molino : public EntidadIG {
public:
    Molino(Ogre::SceneManager* sm, int n, Nodo* parent);

    Nodo* esferaNode = nullptr;
    Nodo* cilindroNode = nullptr;
    Nodo* aspasParent = nullptr;
    AspasMolino* aspas = nullptr;

private:

    bool spin = true;

    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
    virtual void frameRendered(const Ogre::FrameEvent& evt);

};