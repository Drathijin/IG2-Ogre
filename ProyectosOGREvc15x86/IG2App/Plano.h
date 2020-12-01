#pragma once
#include "EntidadIG.h"


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
class Rio : public EntidadIG
{
public:
    Rio(Nodo* parent, float width, float height, std::string string = "");
    ~Rio() {if(mpRef) delete mpRef; };

    virtual void receiveEvent(MessageType msj, EntidadIG* entidad);
    void setReflejo(Ogre::Camera* cam);
    Ogre::Camera* getCam() { return camRef; }
private:
    Ogre::MovablePlane* mpRef = nullptr;
    Ogre::Entity* mEnt = nullptr;
    Ogre::Camera* camRef = nullptr;
};