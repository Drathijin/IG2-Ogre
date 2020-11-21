#pragma once
#include "EntidadIG.h"

class Boya : public EntidadIG
{
public:
    Boya(Nodo* parent);
    ~Boya() {};
private:
    virtual void frameRendered(const Ogre::FrameEvent& evt) override;

    Ogre::Entity* ent;
    Ogre::AnimationState* animationState;
};
