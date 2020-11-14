#pragma once
#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include "EntidadIG.h";

//clase Aspa y AspasMolino

using Nodo = Ogre::SceneNode;


class Aspa : public EntidadIG {
public:
    Aspa(Ogre::SceneManager* sm, Nodo* parent = nullptr);
    static void inline addID() { id++; };

    Nodo* tableroNode = nullptr;
    Nodo* cilindroNode = nullptr;
    static int id;

};

class AspasMolino : public EntidadIG {
public:
    AspasMolino(int n, bool flag, Nodo* parent, float speed = 1);
    ~AspasMolino() { if (arrayAspas) delete[]arrayAspas; };
    void girarAspas(float delta = 1);

    int numAspas;
    static int count;
    Aspa** arrayAspas = nullptr;
    Nodo* botoncicoNode = nullptr;

private:
    bool savedInArray = false;
    float rSpeed = 1;
    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
};


