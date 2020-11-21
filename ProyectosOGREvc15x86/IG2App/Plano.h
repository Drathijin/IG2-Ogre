#pragma once
#include "EntidadIG.h"


class Plano : public EntidadIG
{
public:
    static int id;
    Plano(Nodo* parent, float width, float height, std::string string = "", std::string entName = "");
    ~Plano() {};
    virtual void receiveEvent(MessageType msj, EntidadIG* entidad);
private:
    Ogre::Entity* mEnt = nullptr;
};
