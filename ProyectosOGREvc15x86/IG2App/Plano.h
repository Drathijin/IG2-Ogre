#pragma once
#include "EntidadIG.h"
#include <OgreRenderTarget.h>
#include <OgreRenderTargetListener.h>


class Plano : public EntidadIG
{
public:
    static int id;
    Plano(Nodo* parent, float width, float height, std::string string = "", std::string entName = "");
    ~Plano() {};
    virtual void receiveEvent(MessageType msj, EntidadIG* entidad);
protected:
    Ogre::Entity* mEnt = nullptr;
};
class Rio : public EntidadIG, public Ogre::RenderTargetListener
{
public:
    Rio(Nodo* parent, float width, float height, std::string string = "");
    ~Rio() {if(mpRef) delete mpRef; };

    virtual void receiveEvent(MessageType msj, EntidadIG* entidad);
    void setReflejo(Ogre::Camera* cam);
    Ogre::Camera* getCam() { return camRef; }


    virtual void preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);
    virtual void postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);
private:
    Ogre::MovablePlane* mpRef = nullptr;
    Ogre::Entity* mEnt = nullptr;
    Ogre::Camera* camRef = nullptr;
};