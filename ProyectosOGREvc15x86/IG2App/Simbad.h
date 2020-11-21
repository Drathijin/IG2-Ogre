#pragma once
#include "EntidadIG.h"

class Simbad : public EntidadIG
{
public:
    Simbad(Nodo* parent, bool listener = false);
    ~Simbad() {};
    void inline setListener() { isInputListener = true; }
private:
    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
    virtual void frameRendered(const Ogre::FrameEvent& evt) override;

    Ogre::Entity* ent;
    Ogre::Entity* sword;
    bool walking = true;
    bool dancing = false;
    bool right = true;
    Ogre::AnimationState* animationState;

    bool isInputListener = false;
};
